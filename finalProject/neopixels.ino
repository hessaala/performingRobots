// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        A5 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 130 // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels

void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
}

void loop() {
  //pixels.clear(); // Set all pixel colors to 'off'
  
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
 // pixels.setPixelColor(35, pixels.Color(0, 0, 150));
  pixels.setPixelColor(43, pixels.Color(0, 0, 150));
  pixels.setPixelColor(59, pixels.Color(0, 0, 150));
  pixels.setPixelColor(70, pixels.Color(0, 0, 150));
   pixels.setPixelColor(86, pixels.Color(0, 0, 150));
 // pixels.setPixelColor(94, pixels.Color(0, 0, 150));
  pixels.show();
  
  //tears;
  for (int i=3; i<14; i++){
    tears(2,i,150);
    pixels.show();
    delay(100);
  }
  for (int i=3; i<14; i++){
    tears(2,i,0);
    pixels.show();
    delay(100);
  }
}
  //tears;
//  for(int i=23; i>12; i--) { // For each pixel...
//    pixels.setPixelColor(i, pixels.Color(0, 0, 150));
//    pixels.show();   // Send the updated pixel colors to the hardware.
//    delay(75);
//    // Pause before next pass through loop
//  }
//  for(int i=28; i<39; i++) { // For each pixel...
//    pixels.setPixelColor(i, pixels.Color(0, 0, 150));
//    pixels.show();   // Send the updated pixel colors to the hardware.
//    delay(75); // Pause before next pass through loop
//  }
// for(int i=101; i>91; i--) { // For each pixel...
//    pixels.setPixelColor(i, pixels.Color(0, 0, 150));
//    pixels.show();   // Send the updated pixel colors to the hardware.
//    delay(75);
//    // Pause before next pass through loop
//  }
//  for(int i=106; i<117; i++) { // For each pixel...
//    pixels.setPixelColor(i, pixels.Color(0, 0, 150));
//    pixels.show();   // Send the updated pixel colors to the hardware.
//    delay(75); // Pause before next pass through loop
//  }
//  for(int i=23; i>12; i--) { // For each pixel...
//    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
//    pixels.show();   // Send the updated pixel colors to the hardware.
//    delay(75);
//    // Pause before next pass through loop
//  }
//  for(int i=28; i<39; i++) { // For each pixel...
//    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
//    pixels.show();   // Send the updated pixel colors to the hardware.
//    delay(75); // Pause before next pass through loop
//  }
//  for(int i=101; i>91; i--) { // For each pixel...
//    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
//    pixels.show();   // Send the updated pixel colors to the hardware.
//    delay(75);
//    // Pause before next pass through loop
//  }
//  for(int i=106; i<117; i++) { // For each pixel...
//    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
//    pixels.show();   // Send the updated pixel colors to the hardware.
//    delay(75); // Pause before next pass through loop
//  }
//}
void tears(int x,int y,int Blue){
    pixels.setPixelColor(13*x-y, pixels.Color(0, 0, Blue));
    pixels.setPixelColor(13*x+(y-1), pixels.Color(0, 0, Blue));
    pixels.setPixelColor(13*(x+6)-y, pixels.Color(0, 0, Blue));
    pixels.setPixelColor(13*(x+6)+(y-1), pixels.Color(0, 0, Blue));
  }
