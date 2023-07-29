

// photodiode "SFH 203"
// https://www.conrad.at/de/p/fotodiode-sfh-203-5-mm-1100-nm-20-osram-sfh-203-154002.html

// photo transistor OSRAM SFH 309 Fototransistor 3 mm 1080 nm 12 °
// https://www.conrad.at/de/p/osram-sfh-309-fototransistor-3-mm-1080-nm-12-sfh-309-153870.html

bool sensorCurrentState[NUM_GOALS][SENSORS_PER_GOAL];
uint32_t sensorEnterTime[NUM_GOALS][SENSORS_PER_GOAL];
uint32_t sensorDuration[NUM_GOALS][SENSORS_PER_GOAL];


// a flag set in isr to track any sensor change
volatile bool flagCheckGoalSensors[NUM_GOALS] = { false, false };

// helper variable that increases or decreases on light barrier state change
// so we can avoid to use for-loops when checking if any light barrier is currently interrupted
int8_t busySensors[NUM_GOALS] = { 0, 0 };


// Declare individual ISR functions for each goal
// its very ugly but with this approach we can avoid nested loops in the ISR
// TODO: is there a way to pass arguments to an interrupt in the ESP32 (lambda)?
void IRAM_ATTR sensorIsrGoal1() {
  sensorIsr(0);
}
void IRAM_ATTR sensorIsrGoal2() {
  sensorIsr(1);
}

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
#if SERIALDEBUG
        Serial.println("button has been pressed");
#endif
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

void sensorIsr(uint8_t goal) {
  flagCheckGoalSensors[goal] = true;
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

void setupSensors() {
  for (uint8_t goal = 0; goal < NUM_GOALS; goal++) {
    for (uint8_t i = 0; i < SENSORS_PER_GOAL; i++) {
      pinMode(sensorPins[goal][i], INPUT);
      sensorCurrentState[goal][i] = digitalRead(sensorPins[goal][i]);

      switch (goal) {
        case 0: attachInterrupt(digitalPinToInterrupt(sensorPins[goal][i]), sensorIsrGoal1, CHANGE); break;
        case 1: attachInterrupt(digitalPinToInterrupt(sensorPins[goal][i]), sensorIsrGoal2, CHANGE); break;
        default: break;
      }
    }
    busySensors[goal] = 0;
    flagCheckGoalSensors[goal] = false;
  }
}

void loopReadSensors() {

  for (uint8_t goal = 0; goal < NUM_GOALS; goal++) {
    if (flagCheckGoalSensors[goal] == false) {
      // no sensor change has been tracked via ISR
      continue;
    }
    flagCheckGoalSensors[goal] = false;
    for (uint8_t index = 0; index < SENSORS_PER_GOAL; index++) {
      bool newReading = digitalRead(sensorPins[goal][index]);

      if (sensorCurrentState[goal][index] == newReading) {
        // state has not changed since last reading
        continue;
      }
      sensorCurrentState[goal][index] = newReading;
#ifdef CALIBRATION
      displaySensorState(goal, index, newReading);
#endif
      if (sensorCurrentState[goal][index] == HIGH) {
        // ball entered light barrier
        sensorEnterTime[goal][index] = micros();
        //displaySensorValues();
        busySensors[goal]++;
#if SERIALDEBUG
        Serial.println("ball entered light barrier");
#endif
        continue;
      }
      // ball leaves light barrier

      sensorDuration[goal][index] = micros() - sensorEnterTime[goal][index];
      busySensors[goal]--;
#if SERIALDEBUG
      Serial.print("ball leaves light barrier ");
      Serial.println(sensorDuration[goal][index]);
#endif
      if (busySensors[goal] > 0) {
        // the ball is still within one light barrier
#if SERIALDEBUG
        Serial.println("the ball is still within one light barrier");
#endif
        continue;
      }
      busySensors[goal] = 0;
      calculateBallMetrics(goal);
      // displaySensorValues();
    }
  }
}
