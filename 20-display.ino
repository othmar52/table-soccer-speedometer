#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

// Uncomment according to your hardware type
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
//#define HARDWARE_TYPE MD_MAX72XX::GENERIC_HW

// Defining size, and output pins
#define MAX_DEVICES 8
#define CS_PIN 5

#define PRINT(s, x)
#define PRINTS(x)
#define PRINTX(x)

MD_Parola Display = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);


void setupDisplay() {
 
  delay(2000);
  Display.begin(2);
  Display.setZone(0, 0, 3);
  Display.setZone(1, 4, 7);
  Display.setIntensity(0);
  Display.displayClear();
  uint8_t start, end;
  //Display.getZone(0, start, end);
  //Display.setTextAlignment(PA_CENTER);
  //Display.print("13.8");
  //PRINT("\nZone ", 0);

  Display.displayZoneText(0, "22.1", PA_CENTER, 25, 5000, PA_NO_EFFECT, PA_NO_EFFECT);
  Display.displayZoneText(1, "40.3", PA_CENTER, 25, 5000, PA_PRINT, PA_PRINT);
  
  Display.displayAnimate();
  //Display.getZone(1, start, end);
  //Display.setTextAlignment(PA_CENTER);
  // Display.print("22.1");
  //PRINT("\nZone ", 1);
}

void displaySpeedAndHeight(float ballSpeed, float flightHeight) {

}
void displaySpeedAndHeightTimes(float ballSpeed, float flightHeight, float t1, float t2, float t3) {

}

void displaySensorValues() {
 
}

unsigned long lastFoo = 0;
bool aaa = false;
void loopDisplayTemp() {
  if (millis() - lastFoo < 1500) {
    return;
  }
  lastFoo = millis();
  if (aaa) {
    Display.displayZoneText(0, "28.5", PA_CENTER, 0, 0, PA_NO_EFFECT);
    Display.displayZoneText(1, "4.3", PA_CENTER, 0, 0, PA_NO_EFFECT);
  } else {
    Display.displayZoneText(0, "km/h", PA_CENTER, 0, 0, PA_NO_EFFECT);
    Display.displayZoneText(1, "km/h", PA_CENTER, 0, 0, PA_NO_EFFECT);
  }
  aaa = !aaa;
  Display.displayAnimate();
}
