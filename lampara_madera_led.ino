#include <Adafruit_NeoPixel.h>
#define PIN        5 
#define NUMPIXELS 74

#define BUTTON_PIN   11

const int pinPote = A4;

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

const int numReadings = 15; // Higher value will result in more stability

int readings[numReadings]; 
int readIndex = 0;              
int total = 0;                  
int average = 0;                
int y;
int x = 35;

int buttonState, lastButtonState = 1;
int startPressed, endPressed, holdTime = 0;

int estado = 0;

void setup() {

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pixels.begin();
  pixels.show();

}
void loop() {

  switch (estado) {
    case 0:
      pixels.fill(0, 0, 0);
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
  }

}

void leerBoton() {

  buttonState = digitalRead(BUTTON_PIN); 

  if (buttonState != lastButtonState) {
    if (buttonState == LOW) {
      startPressed = millis();
    } else {
      endPressed = millis();
      holdTime = endPressed - startPressed;

      if (holdTime >= 50 && holdTime < 5000) { //si estuvo apretado menos de 5 segundos
        estado = estado + 1;
        if (estado >4){
          estado=0;
        }
      }
      if (holdTime >= 5000) { //si estuvo apretado mas de 5 segundos
        estado = 6;
      }
    }
  }
  lastButtonState = buttonState;        // save state for next loop
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
  pixels.fill(rgbcolor);
  pixels.show();
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

void mostrar() {
  uint32_t rgbcolor = pixels.ColorHSV(y, 255, x);
  pixels.fill(rgbcolor);
  pixels.show();
}
