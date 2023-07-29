
// @see https://microcontrollerslab.com/led-dot-matrix-display-esp32-max7219/

#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW

// Defining size, and output pins
#define MAX_DEVICES 8
#define CLK_PIN   18  // or SCK
#define DATA_PIN  23  // or MOSI
#define CS_PIN    5  // or SS


MD_Parola Display = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
MD_MAX72XX *pM;

long randomNumber;

void setupDisplay() {

  delay(2000);
  // define a zone for each goal
  Display.begin(2);
  Display.setZone(0, 0, 3);
  Display.setZone(1, 4, 7);

  Display.setIntensity(0);
  Display.displayClear();
  uint8_t start, end;
  Display.displayZoneText(0, "22.1", PA_CENTER, 25, 5000, PA_NO_EFFECT, PA_NO_EFFECT);
  Display.displayZoneText(1, "40.3", PA_CENTER, 25, 5000, PA_PRINT, PA_PRINT);
  Display.displayAnimate();
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
    Display.displayZoneText(0, "> 28.5", PA_CENTER, 0, 0, PA_NO_EFFECT);
    Display.displayZoneText(1, "< 4.3", PA_CENTER, 0, 0, PA_NO_EFFECT);
  } else {
    Display.displayZoneText(0, "km/h", PA_CENTER, 0, 0, PA_NO_EFFECT);
    Display.displayZoneText(1, "km/h", PA_CENTER, 0, 0, PA_NO_EFFECT);
  }
}

#ifdef CALIBRATION
void displaySensorState(uint8_t goal, uint8_t index, bool state) {
  pM = Display.getGraphicObject();
  pM->setPoint(
    index,
    (goal == 0) ? 0 : 32,
    state
  );
}
#endif
