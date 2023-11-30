#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_DotStarMatrix.h>
#include <Adafruit_DotStar.h>
#include <Fonts/TomThumb.h>

#define DATAPIN    0
#define CLOCKPIN   2
#define BRIGHTNESS 20
#define SHIFTDELAY 100
#define buttonPin 4

#define countof(a) (sizeof(a) / sizeof(a[0]))
#define EVER (;;)

// Variables will change:
int buttonPushCounter = 0;  // counter for the number of button presses
int buttonState = 0;        // current state of the button
int lastButtonState = 0;    // previous state of the button


Adafruit_DotStarMatrix matrix = Adafruit_DotStarMatrix(
    8, 8, DATAPIN, CLOCKPIN,
    DS_MATRIX_BOTTOM + DS_MATRIX_LEFT +
    DS_MATRIX_ROWS + DS_MATRIX_PROGRESSIVE,
    DOTSTAR_BGR);

struct sequences {
  int pixels[27];
  uint8_t r;
  uint8_t g;
  uint8_t b;
  int delay;
  bool zero;
};

// Define sequences
struct sequences cat[] = {
  {{3,4,10,13,17,22,24,31,32,34,37,39,40,47,48,49,50,51,52,53,54,55,56,57,62,63}, 255, 0, 0, 300, false},
  {{3,4,10,13,17,22,24,31,32,34,37,39,40,47,48,49,50,51,52,53,54,55,56,57,62,63}, 255, 200, 0, 300, false},
  {{3,4,10,13,17,22,24,31,32,34,37,39,40,47,48,49,50,51,52,53,54,55,56,57,62,63}, 0, 0, 0, 300, false}
};

struct sequences box[] = {
  {{27,28,35,36}, 255, 0, 0, 50, false},
  {{18,19,20,21,26,29,34,37,42,43,44,45}, 255, 0, 0, 20, false},
  {{9,10,11,12,13,14,17,14,22,25,30,33,38,41,46,49,50,51,52,53,54}, 255, 0, 0, 10, false},
  {{27,28,35,36}, 255, 200, 0, 200, false},
  {{27,28,35,36}, 0, 0, 0, 300, false}
};

void displaySequence(struct sequences sequence[], size_t sequenceSize) {
  for (size_t i = 0; i < sequenceSize; ++i) {
    for (int pixel : sequence[i].pixels) {
      matrix.setPixelColor(pixel, sequence[i].r, sequence[i].g, sequence[i].b);
    }

    if (sequence[i].zero == false) {
      matrix.setPixelColor(0, 0, 0, 0);
    }

    matrix.show();
    delay(sequence[i].delay);
  }
}

int (*returnRowPixels(int pixel))[8] {
  int startPixel = ((pixel / 8) * 8);;
  int endPixel = ((pixel + 8 - (pixel % 8)) - 1);
	
  static int rowArray[8];
  int i;
 for (i = 0 ;i < 8; i++) {
    if(i == 0){
      rowArray[i] = startPixel;
    }else{
      rowArray[i] = startPixel + i;
    }
  }
	return &rowArray;
}

int (*returnColumnPixels(int pixel))[8] {
  
  int bottomPixel; 
  for (int i = 0; i < 8; i++){
    if(pixel >= 8){
      pixel = pixel - 8;
      bottomPixel = pixel;
    }else{
      bottomPixel = pixel;
    }

  }
  static int columnArray[8];
  int topPixel = bottomPixel + 56;
 
 for (int i = 0; i < 8; i++){
    if(i == 0){
      columnArray[i] = bottomPixel;
    }else{
      columnArray[i] = bottomPixel + (i*8);
    }
  }
   
return &columnArray;

 }

  


void setup() {
  Serial.begin(115200);
  matrix.begin();
  matrix.show(); // Initialize all pixels to 'off'
  pinMode(buttonPin, INPUT);
}

void loop() {
  matrix.setBrightness(BRIGHTNESS);
  matrix.fillScreen(0);
  matrix.setCursor(matrix.width(), 0);

  int buttonState = digitalRead(buttonPin);

  if (buttonState != lastButtonState) {
    if (buttonState == HIGH) {
      buttonPushCounter = (buttonPushCounter < 3) ? (buttonPushCounter + 1) : 0;
      Serial.println("on");
      Serial.print("number of button pushes: ");
      Serial.println(buttonPushCounter);
    }
    lastButtonState = buttonState;
  }

  if (buttonPushCounter == 0) {
    displaySequence(cat, countof(cat));
  } else if(buttonPushCounter == 1 ) {
    displaySequence(box, countof(box));
  } else if(buttonPushCounter == 2 ) {
int randomNumber = std::rand() % 66 - 1;

int (*arrr)[8] = returnColumnPixels(randomNumber);
 
 for (int pixel : *arrr ) {
      if (pixel <= randomNumber){
        matrix.setPixelColor(pixel, 255, 0, 0);
        matrix.show();
        delay(80);
      }

    }
    
  }else {

int randomNumber = std::rand() % 66 - 1;

int (*arrr)[8] = returnRowPixels(randomNumber);


  for (int pixel : *arrr ) {
      if (pixel >= randomNumber){
        matrix.setPixelColor(pixel, 255, 0, 0);
        matrix.show();
        delay(80);
      }

    }


  }
}
