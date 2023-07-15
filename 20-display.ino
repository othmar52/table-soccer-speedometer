
#include <Wire.h>
#include <hd44780.h>                       // main hd44780 header
#include <hd44780ioClass/hd44780_I2Cexp.h> // i2c expander i/o class header

hd44780_I2Cexp lcd; // declare lcd object: auto locate & auto config expander chip

byte charUpperBoth[8] = {
  0b11111, 0b11111, 0b11111, 0b00000, 0b00000, 0b00000, 0b11111, 0b11111
};
byte charUpperTop[8] = {
  0b11111, 0b11111, 0b11111, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000
};
byte charUpperBottom[8] = {
  0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b11111, 0b11111
};
byte charLowerBoth[8] = {
  0b11111, 0b11111, 0b00000, 0b00000, 0b00000, 0b11111, 0b11111, 0b11111
};
byte charLowerTop[8] = {
  0b11111, 0b11111, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000
};
byte charLowerBottom[8] = {
  0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b11111, 0b11111, 0b11111
};
byte charEmpty[8] = {
  0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000
};

void setupDisplay() {
  lcd.begin(16,2);               // initialize the lcd 
  lcd.createChar(0, charUpperBoth);
  lcd.createChar(1, charUpperTop);
  lcd.createChar(2, charUpperBottom);
  lcd.createChar(3, charLowerBoth);
  lcd.createChar(4, charLowerTop);
  lcd.createChar(5, charLowerBottom);
  lcd.createChar(6, charEmpty);
  
  lcd.setCursor(2,0);
  lcd.print("Table  Soccer");
  lcd.setCursor(3,1);
  lcd.print("Speedometer");
  
}


void displaySpeedAndHeight(float ballSpeed, float flightHeight) {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(ballSpeed, 1);
  lcd.print(" km/h");
  lcd.setCursor(0,1);
  lcd.print(flightHeight, 1);
  lcd.print(" mm");
  displaySensorValues();
}

void displaySensorValues() {
  uint8_t upperCharIndex = 6; // empty
  uint8_t lowerCharIndex = 6; // empty
  if (ledCurrentState[2] == LOW && ledCurrentState[1] == LOW) {
    upperCharIndex = 0; //charUpperBoth
  }
  if (ledCurrentState[2] == LOW && ledCurrentState[1] == HIGH) {
    upperCharIndex = 1; //charUpperTop
  }
  if (ledCurrentState[2] == HIGH && ledCurrentState[1] == LOW) {
    upperCharIndex = 2; //charUpperBottom
  }
  if (ledCurrentState[0] == LOW && ledCurrentState[1] == LOW) {
    lowerCharIndex = 3; //charLowerBoth
  }
  if (ledCurrentState[0] == LOW && ledCurrentState[1] == HIGH) {
    lowerCharIndex = 5; //charLowerBottom
  }
  if (ledCurrentState[0] == HIGH && ledCurrentState[1] == LOW) {
    lowerCharIndex = 4; //charLowerTop
  }

  lcd.setCursor(15, 0);
  lcd.write((uint8_t)upperCharIndex);
  lcd.setCursor(15, 1);
  lcd.write((uint8_t)lowerCharIndex);
  //lcd.display();
}
