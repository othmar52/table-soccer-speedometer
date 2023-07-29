 

bool buttonCurrentState[NUM_BUTTONS];
uint32_t buttonPressTimestamp[NUM_BUTTONS];
uint32_t buttonDuration[NUM_BUTTONS];

volatile bool flagCheckButtons = false;

void IRAM_ATTR buttonTest() {
  flagCheckButtons = true;
}

void loopReadButtons() {
  if (flagCheckButtons == false) {
    // no button state change has been tracked via ISR
    return;
  }
  flagCheckButtons = false;

  for (uint8_t index = 0; index < NUM_BUTTONS; index++) {

      bool newReading = digitalRead(buttonPins[index]);

      if (buttonCurrentState[index] == newReading) {
        // state has not changed since last reading
        continue;
      }
      buttonCurrentState[index] = newReading;

      if (buttonCurrentState[index] == LOW) {
        // button has been pressed
        buttonPressTimestamp[index] = millis();
        continue;
      }
      // button has been released

      buttonDuration[index] = millis() - buttonPressTimestamp[index];
#if SERIALDEBUG
      Serial.print("button ");
      Serial.print(index);
      Serial.print(" has been released ");
      Serial.println(buttonDuration[index]);
#endif

    }
}


void setupButtons() {
  
  for (uint8_t i = 0; i < NUM_BUTTONS; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
    buttonCurrentState[i] = digitalRead(buttonPins[i]);
    attachInterrupt(digitalPinToInterrupt(buttonPins[i]), buttonTest, CHANGE);
  }
  
  //pinMode(15, INPUT_PULLUP);
  // buttonCurrentState[i] = digitalRead(15);
  //attachInterrupt(digitalPinToInterrupt(15), buttonTest, CHANGE);
  flagCheckButtons = false;
}