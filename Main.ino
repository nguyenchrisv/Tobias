// Adafruit_DotStarMatrix example for single DotStar LED matrix.
// Scrolls 'Adafruit' across the matrix.

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_DotStarMatrix.h>
#include <Adafruit_DotStar.h>
#include <Fonts/TomThumb.h>

#define DATAPIN    0
#define CLOCKPIN   2

#define SHIFTDELAY 100
#define BRIGHTNESS 20

// MATRIX DECLARATION:
// Parameter 1 = width of DotStar matrix
// Parameter 2 = height of matrix
// Parameter 3 = pin number (most are valid)
// Parameter 4 = matrix layout flags, add together as needed:
//   DS_MATRIX_TOP, DS_MATRIX_BOTTOM, DS_MATRIX_LEFT, DS_MATRIX_RIGHT:
//     Position of the FIRST LED in the matrix; pick two, e.g.
//     DS_MATRIX_TOP + DS_MATRIX_LEFT for the top-left corner.
//   DS_MATRIX_ROWS, DS_MATRIX_COLUMNS: LEDs are arranged in horizontal
//     rows or in vertical columns, respectively; pick one or the other.
//   DS_MATRIX_PROGRESSIVE, DS_MATRIX_ZIGZAG: all rows/columns proceed
//     in the same order, or alternate lines reverse direction; pick one.
//   See example below for these values in action.
// Parameter 5 = pixel type:
//   DOTSTAR_BRG  Pixels are wired for BRG bitstream (most DotStar items)
//   DOTSTAR_GBR  Pixels are wired for GBR bitstream (some older DotStars)
//   DOTSTAR_BGR  Pixels are wired for BGR bitstream (APA102-2020 DotStars)

Adafruit_DotStarMatrix matrix = Adafruit_DotStarMatrix(
                                  8, 8, DATAPIN, CLOCKPIN,
                                  DS_MATRIX_BOTTOM     + DS_MATRIX_LEFT +
                                  DS_MATRIX_ROWS + DS_MATRIX_PROGRESSIVE,
                                  DOTSTAR_BGR);




int x    = matrix.width();

int pass = 0;
const int buttonPin = 4;
int flag = 0;

// Variables will change:
int buttonPushCounter = 0;  // counter for the number of button presses
int buttonState = 0;        // current state of the button
int lastButtonState = 0;    // previous state of the button

#define EVER (;;);

//cat face 
int catArray [] = {3,4,10,13,17,22,24,31,32,34,37,39,40,47,48,49,50,51,52,53,54,55,56,57,62,63};

//2x2 square
int twoArray [] = {27,28,35,36};

//4X4
int fourArray [] = {18,19,20,21,26,29,34,37,42,43,44,45};

//6x6 square
int sixArray [] = {9,10,11,12,13,14,17,14,22,25,30,33,38,41,46,49,50,51,52,53,54};

//8X8 square
int eightArray [] = {0,1,2,3,4,5,6,7,8,15,16,23,24,31,32,39,40,47,48,55,56,57,58,59,60,61,62,63};

void setup() {
  Serial.begin(115200);
  matrix.begin();
  matrix.show(); // Initialize all pixels to 'off'

  pinMode(buttonPin, INPUT);
}


void loop() {

  matrix.setBrightness(20 );
  matrix.fillScreen(0);
  matrix.setCursor(x, 0);

  // read the pushbutton input pin:
  buttonState = digitalRead(buttonPin);

  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      // if the current state is HIGH then the button went from off to on:
      if (buttonPushCounter < 1 ){
        buttonPushCounter++;

      }else {
        buttonPushCounter = 0;

      }
      Serial.println("on");
      Serial.print("number of button pushes: ");
      Serial.println(buttonPushCounter);
    } else {
      // if the current state is LOW then the button went from on to off:
      Serial.println("off");
    }
    // Delay a little bit to avoid bouncing
    //delay(50);
  }
  // save the current state as the last state, for next time through the loop
  lastButtonState = buttonState;


  // turns on the LED every four button pushes by checking the modulo of the
  // button push counter. the modulo function gives you the remainder of the
  // division of two numbers:
  if (buttonPushCounter == 0) {
      for (int pixel : catArray){
        matrix.setPixelColor(pixel,255,0,0);        
      }

      matrix.show();
      delay(300);

      for (int pixel : catArray){
        matrix.setPixelColor(pixel,0,0,0);        
      }

      matrix.show();
      delay(300);
  } else {
      for (int pixel : twoArray){
        matrix.setPixelColor(pixel,255,0,0);
      }
      matrix.show();
      delay(50);
      
      for (int pixel : fourArray){
        matrix.setPixelColor(pixel,255,0,0);
      }
      matrix.show();
      delay(20);
      
      for (int pixel : sixArray){
        matrix.setPixelColor(pixel,255,0,0);
      }
      matrix.show();
      delay(10);
      
      for (int pixel : twoArray){
        matrix.setPixelColor(pixel,255,200,0);
      }
      
      matrix.setBrightness(20);
      matrix.show();
      
      delay(200);
      
      for (int pixel : twoArray){
        matrix.setPixelColor(pixel,0,0,0);
      }

      matrix.show();


  }


  
  //delay(100);
}


