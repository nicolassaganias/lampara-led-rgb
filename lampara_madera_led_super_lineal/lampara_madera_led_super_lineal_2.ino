#include <Adafruit_NeoPixel.h>
#define PIN        4
int NUMPIXELS = 113;
int half = (NUMPIXELS / 2);
//#define buttonPin   11
#define buttonPin 8    //triangulo es A1  

const int pinPote = A0;

//Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB);
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRBW + NEO_KHZ800);

int r1, g1, b1, r2, g2, b2, r3, g3, b3;
uint32_t color1 = Adafruit_NeoPixel::Color(230, 30, 220);
uint32_t color2, color3;
unsigned long speedUL = 5; // cuanto menor el numero mayor la velocidad

const int numReadings = 15; // Higher value will result in more stability

int readings[numReadings];
int readIndex = 0;
int total = 0;
int average = 0;
int y;
int x = 35;

int estado = 0;

int minBright = 150;
int maxBright = 240;
int brightness = 50;
int fadeAmount = 1;

const uint32_t Blue = Adafruit_NeoPixel::Color(10, 10, 255);
const uint32_t Pink = Adafruit_NeoPixel::Color(255, 0, 100);
const uint32_t Red = Adafruit_NeoPixel::Color(255, 0, 0);
const uint32_t Yellow = Adafruit_NeoPixel::Color(255, 220, 10);
const uint32_t Green = Adafruit_NeoPixel::Color(10, 255, 10);
const uint32_t Violet = Adafruit_NeoPixel::Color(230, 30, 220);
const uint32_t Turquoise = Adafruit_NeoPixel::Color(50, 255, 150);
const uint32_t Orange = Adafruit_NeoPixel::Color(255, 165, 0);

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);
  pixels.begin();
  pixels.clear();
  pixels.show();
  randomSeed(analogRead(A4));
}
void loop() {
  //Serial.println(estado);
  switch (estado) {
    case 0:
      pixels.fill();
      pixels.show();
      estado = 1;
      break;

    case 1:
      leerBoton();
      break;

    case 2:
      leerBoton();
      variarColor();
      break;

    case 3:

      leerBoton();
      variarBrillo();

      break;

    case 4:

      leerBoton();
      mostrar();

      break;

    case 5:
      estado = 0;
      break;

    case 6:
      leerBoton();
      blanco();
      variarBrilloBlanco();
      break;

    case 7:
      estado = 0;
      break;

    case 8:
      leerBoton();
      primeraMitad();
      break;

    case 9:
      leerBoton();
      variarBrilloPrimeraMitad();
      break;

    case 10:
      leerBoton();
      segundaMitad();
      break;

    case 11:
      leerBoton();
      variarBrilloSegundaMitad();
      break;

    case 12:
      estado = 0;
      break;

    case 13: // Blue, Pink, Red, Yellow, Green, Violet, Turquoise

      randomColor2();
      randomColor3();
      crossFade(color1, color2, speedUL);
      crossFade(color2, color3, speedUL);
      randomColor1();
      crossFade(color3, color1, speedUL);

      //      crossFade(Pink, Blue, speedUL);
      //      crossFade(Blue, Violet, speedUL);
      //      crossFade(Violet, Yellow, speedUL);
      //      crossFade(Yellow, Turquoise, speedUL);
      //      crossFade(Turquoise, Red, speedUL);
      //      crossFade(Red, Pink, speedUL);

      break;

    case 14:
      estado = 0;
      break;

  }

}

void leerBoton() {
  int b = checkButton();
  if (b == 1) clickEvent();
  if (b == 2) doubleClickEvent();
  if (b == 3) holdEvent();
  if (b == 4) longHoldEvent();
}

void clickEvent() {
  estado = estado + 1;
}
void doubleClickEvent() {
  estado = 6;
}
void holdEvent() {
  estado = 8;
}

void longHoldEvent() {
  estado = 13;
}

void variarColor() {

  total = total - readings[readIndex];
  readings[readIndex] = analogRead(pinPote);
  total = total + readings[readIndex];
  readIndex = readIndex + 1;

  if (readIndex >= numReadings) {
    readIndex = 0;
  }
  average = total / numReadings;

  y = map(average, 0, 1024, 0, 65536);
  uint32_t rgbcolor = pixels.ColorHSV(y, 255, x);
  int realTime = int(rgbcolor);
  Serial.println(realTime);
  pixels.fill(rgbcolor);
  pixels.show();
}

void variarColorAuto() {

}

void variarBrillo() {
  total = total - readings[readIndex];
  readings[readIndex] = analogRead(pinPote);
  total = total + readings[readIndex];
  readIndex = readIndex + 1;

  if (readIndex >= numReadings) {
    readIndex = 0;
  }
  average = total / numReadings;

  x = map(average, 0, 1024, 0, 255);

  uint32_t rgbcolor = pixels.ColorHSV(y, 255, x);
  pixels.fill(rgbcolor);
  pixels.show();
}

void variarBrilloBlanco() {

  total = total - readings[readIndex];
  readings[readIndex] = analogRead(pinPote);
  total = total + readings[readIndex];
  readIndex = readIndex + 1;

  if (readIndex >= numReadings) {
    readIndex = 0;
  }

  average = total / numReadings;

  x = map(average, 0, 1024, 0, 255);

  uint32_t white = pixels.Color(x, x, x, 255);
  pixels.fill(white);
  pixels.show();
}

void variarBrilloPrimeraMitad() {
  total = total - readings[readIndex];
  readings[readIndex] = analogRead(pinPote);
  total = total + readings[readIndex];
  readIndex = readIndex + 1;

  if (readIndex >= numReadings) {
    readIndex = 0;
  }
  average = total / numReadings;

  x = map(average, 0, 1024, 0, 255);

  uint32_t rgbcolor = pixels.ColorHSV(y, 255, x);
  half = NUMPIXELS / 2;
  pixels.fill(rgbcolor, 0, half);
  pixels.show();

}

void variarBrilloSegundaMitad() {
  total = total - readings[readIndex];
  readings[readIndex] = analogRead(pinPote);
  total = total + readings[readIndex];
  readIndex = readIndex + 1;

  if (readIndex >= numReadings) {
    readIndex = 0;
  }
  average = total / numReadings;

  x = map(average, 0, 1024, 0, 255);

  uint32_t rgbcolor = pixels.ColorHSV(y, 255, x);
  half = NUMPIXELS / 2;
  pixels.fill(rgbcolor, half , NUMPIXELS);
  pixels.show();

}
void mostrar() {
  uint32_t rgbcolor = pixels.ColorHSV(y, 255, x);
  pixels.fill(rgbcolor);
  pixels.show();
}

void blanco() {
  uint32_t white = pixels.Color(0, 0, 0, 255);
  pixels.fill(white);
  pixels.show();

  // pixels.fill(strip.Color(0, 0, 0, strip.gamma8(0)));
  // pixels.show();
}

void primeraMitad () {
  total = total - readings[readIndex];
  readings[readIndex] = analogRead(pinPote);
  total = total + readings[readIndex];
  readIndex = readIndex + 1;

  if (readIndex >= numReadings) {
    readIndex = 0;
  }
  average = total / numReadings;

  y = map(average, 0, 1024, 0, 65536);
  uint32_t rgbcolor = pixels.ColorHSV(y, 255, x);

  half = NUMPIXELS / 2;
  pixels.fill(rgbcolor, 0, half);
  pixels.show();
}

void segundaMitad() {
  total = total - readings[readIndex];
  readings[readIndex] = analogRead(pinPote);
  total = total + readings[readIndex];
  readIndex = readIndex + 1;

  if (readIndex >= numReadings) {
    readIndex = 0;
  }
  average = total / numReadings;

  y = map(average, 0, 1024, 0, 65536);
  uint32_t rgbcolor = pixels.ColorHSV(y, 255, x);

  half = NUMPIXELS / 2;
  pixels.fill(rgbcolor, half , NUMPIXELS);
  pixels.show();
}

void variarBrilloAuto() {
  brightness = brightness + fadeAmount;

  if (brightness <= minBright || brightness >= maxBright) {
    fadeAmount = -fadeAmount;
  }
  delay(10);
  pixels.setBrightness(brightness);
  pixels.show();
}

void randomColor1() {
  //  r1 = random(0, 255);  g1 = random(0, 255);  b1 = random(0, 255);
  //  color1 = Adafruit_NeoPixel::Color(r1, g1, b1);

  int pic = random(8); // Blue, Pink, Red, Yellow, Green, Violet, Turquoise, Orange
  //  Serial.print("color1: ");
  //  Serial.print(pic);
  switch (pic) {
    case 0:
      color1 = Pink;
      break;

    case 1:
      color1 = Red;
      break;

    case 2:
      color1 = Yellow;
      break;

    case 3:
      color1 = Blue;
      break;

    case 4:
      color1 = Green;
      break;

    case 5:
      color1 = Violet;
      break;

    case 6:
      color1 = Turquoise;
      break;

    case 7:
      color1 = Orange;
      break;

  }
}

void randomColor2() {
  //  r2 = random(0, 255);  g2 = random(0, 255);  b2 = random(0, 255);
  //  color2 = Adafruit_NeoPixel::Color(r2, g2, b2);

  int pic = random(8); // Blue, Pink, Red, Yellow, Green, Violet, Turquoise, Orange
  //  Serial.print(" color2: ");
  //  Serial.print(pic);
  switch (pic) {
    case 0:
      color2 = Pink;
      break;

    case 1:
      color2 = Red;
      break;

    case 2:
      color2 = Yellow;
      break;

    case 3:
      color2 = Blue;
      break;

    case 4:
      color2 = Green;
      break;

    case 5:
      color2 = Violet;
      break;

    case 6:
      color2 = Turquoise;
      break;

    case 7:
      color2 = Orange;
      break;

  }
}

void randomColor3() {
  //  r3 = random(0, 255);  g3 = random(0, 255);  b3 = random(0, 255);
  //  color3 = Adafruit_NeoPixel::Color(r3, g3, b3);

  int pic = random(8); // Blue, Pink, Red, Yellow, Green, Violet, Turquoise, Orange
  //  Serial.print(" color3: ");
  //  Serial.println(pic);

  switch (pic) {
    case 0:
      color3 = Pink;
      break;

    case 1:
      color3 = Red;
      break;

    case 2:
      color3 = Yellow;
      break;

    case 3:
      color3 = Blue;
      break;

    case 4:
      color3 = Green;
      break;

    case 5:
      color3 = Violet;
      break;

    case 6:
      color3 = Turquoise;
      break;

    case 7:
      color3 = Orange;
      break;
  }
}

void setAllpixels(const uint32_t color) {
  byte red = (color >> 16) & 0xff;
  byte green = (color >> 8) & 0xff;
  byte blue = color & 0xff;
  setAllpixels(red, green, blue);
}

void setAllpixels(byte red, byte green, byte blue) {
  // for each strip
  for (int strip = 0; strip < NUMPIXELS; strip++) {
    // for each pixel
    for (int pixel = 0; pixel < NUMPIXELS; pixel++) {
      pixels.setPixelColor(pixel, red, green, blue);
    }
    pixels.show(); // Output to strip
  }
}

void crossFade(const uint32_t startColor, const uint32_t endColor, unsigned long speed) {
  byte startRed = (startColor >> 16) & 0xff;
  byte startGreen = (startColor >> 8) & 0xff;
  byte startBlue = startColor & 0xff;

  byte endRed = (endColor >> 16) & 0xff;
  byte endGreen = (endColor >> 8) & 0xff;
  byte endBlue = endColor & 0xff;

  // for each step in the cross-fade
  for (int step = 0; step < 256; step++) {
    byte red = map(step, 0, 255, startRed, endRed);
    byte green = map(step, 0, 255, startGreen, endGreen);
    byte blue = map(step, 0, 255, startBlue, endBlue);
    setAllpixels(red, green, blue);
    variarBrilloAuto();
    delay(speed);
  }
}
