const int CEPIN = 9;
const int CSNPIN = 10;

// In summary,
// nRF 24L01 pin    Arduino pin   name
//          1                     GND
//          2                     3.3V
//          3             9       CE
//          4             10      CSN
//          5             13      SCLK
//          6             11      MOSI/COPI
//          7             12      MISO/CIPO

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(CEPIN, CSNPIN);  // CE, CSN

#include <printf.h>  // for debugging

// See note in rf24Handshaking about address selection
//

// Channel and address allocation:
// Oliver and Hessa:  Channel 50, addr = 0x7C
const byte addr = 0x7C; // change as per the above assignment
const int RF24_CHANNEL_NUMBER = 50; // change as per the above assignment

// Do not make changes here
const byte xmtrAddress[] = { addr, addr, 0xC7, 0xE6, 0xCC };
const byte rcvrAddress[] = { addr, addr, 0xC7, 0xE6, 0x66 };

const int RF24_POWER_LEVEL = RF24_PA_LOW;

// global variables
uint8_t pipeNum;
unsigned int totalTransmitFailures = 0;

struct DataStruct {
  uint8_t selectorBits;
};
DataStruct data;

void setupRF24Common() {

  // RF24 setup
  if (!radio.begin()) {
    Serial.println("radio  initialization failed");
    while (1)
      ;
  } else {
    Serial.println("radio successfully initialized");
  }

  radio.setDataRate(RF24_250KBPS);
  radio.setChannel(RF24_CHANNEL_NUMBER);
  radio.setPALevel(RF24_POWER_LEVEL);
}

void rf24SendData() {

  // The write() function will block
  // until the message is successfully acknowledged by the receiver
  // or the timeout/retransmit maxima are reached.
  int retval = radio.write(&data, sizeof(data));

  Serial.print("Sending data = ");
  Serial.print(data.selectorBits);
  Serial.print(" ... ");
  if (retval) {
    Serial.println("success");

  } else {
    totalTransmitFailures++;
    Serial.print("failure, total failures = ");
    Serial.println(totalTransmitFailures);
  }
}

// Receiver Code
// Additional libraries for receiver
#include <Adafruit_VS1053.h>
#include <SD.h>
#include <Servo.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
// Additional pin usage for receiver
// Adafruit music maker shield
#define SHIELD_RESET -1  // VS1053 reset pin (unused!)
#define SHIELD_CS 7      // VS1053 chip select pin (output)
#define SHIELD_DCS 6     // VS1053 Data/command select pin (output)
#define CARDCS 4         // Card chip select pin
// DREQ should be an Int pin, see http://arduino.cc/en/Reference/attachInterrupt
#define DREQ 3  // VS1053 Data request, ideally an Interrupt pin
Adafruit_VS1053_FilePlayer musicPlayer = Adafruit_VS1053_FilePlayer(SHIELD_RESET, SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);
// Servo motors
const int SERVO0PIN = A1;
const int SERVO1PIN = A2;
const int SERVO2PIN = A3;
const int SERVO3PIN = A4;
// Neopixel
#define NEOPIXELPIN A5
#define NUMPIXELS 160  // change to fit
Adafruit_NeoPixel pixels(NUMPIXELS, NEOPIXELPIN, NEO_GRB + NEO_KHZ800);
Servo servo0;  // change names to describe what's moving
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
// change as per your robot
const int SERVO0NEUTRALPOSITION = 45;
const int SERVO1NEUTRALPOSITION = 90;
const int SERVO2NEUTRALPOSITION = 0;
const int SERVO3NEUTRALPOSITION = 180;
const int SERVO4NEUTRALPOSITION = 180;

void setup() {
  Serial.begin(9600);
  printf_begin();
  // Set up all the attached hardware
  //setupMusicMakerShield();
  setupServoMotors();
  setupNeoPixels();
  setupRF24();
  // Brief flash to show we're done with setup()
  flashNeoPixels();
}
void setupRF24() {
  setupRF24Common();
  // Set us as a receiver
  radio.openWritingPipe(rcvrAddress);
  radio.openReadingPipe(1, xmtrAddress);
  radio.printPrettyDetails();
  Serial.println("I am a receiver");
}
//void setupMusicMakerShield() {
//  if (!musicPlayer.begin()) {  // initialise the music player
//    Serial.println(F("Couldn't find VS1053, do you have the right pins defined?"));
//    while (1)
//      ;
//  }
//  Serial.println(F("VS1053 found"));
//  if (!SD.begin(CARDCS)) {
//    Serial.println(F("SD card failed or not present"));
//    while (1)
//      ;  // don't do anything more
//  }
//  // Set volume for left, right channels. lower numbers == louder volume!
//  musicPlayer.setVolume(20, 20);
//  // Timer interrupts are not suggested, better to use DREQ interrupt!
//  //musicPlayer.useInterrupt(VS1053_FILEPLAYER_TIMER0_INT); // timer int
//  // If DREQ is on an interrupt pin (on uno, #2 or #3) we can do background
//  // audio playing
//  musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);  // DREQ int
//}

void setupServoMotors() {
  servo0.attach(SERVO0PIN);
  servo1.attach(SERVO1PIN);
  servo2.attach(SERVO2PIN);
  servo3.attach(SERVO3PIN);
  servo0.write(SERVO0NEUTRALPOSITION);
  servo1.write(SERVO1NEUTRALPOSITION);
  servo2.write(SERVO2NEUTRALPOSITION);
  servo3.write(SERVO3NEUTRALPOSITION);
}

void setupNeoPixels() {
  pixels.begin();
  pixels.clear();
  pixels.show();
}
void flashNeoPixels() {
  // all on
  for (int i = 0; i < NUMPIXELS; i++) {  // For each pixel...
    pixels.setPixelColor(i, pixels.Color(0, 100, 0));
  }
  pixels.show();
  delay(500);
  
  // all off
  pixels.clear();
  pixels.show();
}
void loop() {
  // If there is data, read it,
  // and do the needfull
  // Become a receiver
  radio.startListening();
  if (radio.available(&pipeNum)) {
    radio.read(&data, sizeof(data));
    Serial.print("message received Data = ");
    Serial.println(data.selectorBits);
    switch (data.selectorBits) {
      case 0b00000000:
        break;
      case 0b00000001:
        // Don't play if it's already playing
        if (musicPlayer.stopped()) {
          // Non-blocking
          Serial.println(F("Playing track 001"));
          musicPlayer.startPlayingFile("/track001.mp3");
        } else {
          Serial.println(F("Playing in progress, ignoring"));
        }
        break;
      case 0b00000010:
        // Don't play if it's already playing
        if (musicPlayer.stopped()) {
          // Non-blocking
          Serial.println(F("Playing track 002"));
          musicPlayer.startPlayingFile("/track002.mp3");
        } else {
          Serial.println(F("Playing in progress, ignoring"));
        }
        break;
      case 0b00000011:
  //eyes;
  pixels.setPixelColor(0, pixels.Color(0, 0, 150));
  pixels.setPixelColor(1, pixels.Color(0, 0, 150));
  pixels.setPixelColor(24, pixels.Color(0, 0, 150));
  pixels.setPixelColor(25, pixels.Color(0, 0, 150));
  pixels.setPixelColor(26, pixels.Color(0, 0, 150));
  pixels.setPixelColor(27, pixels.Color(0, 0, 150));
  pixels.setPixelColor(50, pixels.Color(0, 0, 150));
  //pixels.setPixelColor(40, pixels.Color(0, 0, 150));
  pixels.setPixelColor(51, pixels.Color(0, 0, 150));
  pixels.setPixelColor(78, pixels.Color(0, 0, 150));
  pixels.setPixelColor(79, pixels.Color(0, 0, 150));
  pixels.setPixelColor(102, pixels.Color(0, 0, 150));
  pixels.setPixelColor(103, pixels.Color(0, 0, 150));
  pixels.setPixelColor(104, pixels.Color(0, 0, 150));
  pixels.setPixelColor(105, pixels.Color(0, 0, 150));
   pixels.setPixelColor(128, pixels.Color(0, 0, 150));
  pixels.setPixelColor(129, pixels.Color(0, 0, 150));
  //mouth;
  pixels.setPixelColor(35, pixels.Color(0, 0, 150));
  pixels.setPixelColor(43, pixels.Color(0, 0, 150));
  pixels.setPixelColor(59, pixels.Color(0, 0, 150));
  pixels.setPixelColor(70, pixels.Color(0, 0, 150));
   pixels.setPixelColor(86, pixels.Color(0, 0, 150));
  pixels.setPixelColor(94, pixels.Color(0, 0, 150));
  pixels.show();
        break;
      case 0b00000100:
        servo0.write(30);
        servo1.write(30);
        servo2.write(30);
        servo3.write(30);
        break;
      case 0b00000101:
        break;
      case 0b00000110:
        break;
      case 0b00000111:
        break;
      case 0b00001000:
        break;
      case 0b00001001:
        break;
      case 0b00001010:
        break;
      case 0b00001011:
        break;
      case 0b00001100:
        break;
      case 0b00001101:
        break;
      case 0b00001110:
        break;
      case 0b00001111:
        break;
      default:
        Serial.println("Invalid option");
    }
  }
}  // end of loop()
// end of receiver code
