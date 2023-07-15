

// photodiode "SFH 203"

#define NUM_PHOTODIODES 3 // amount of photo diodes

const float heights[NUM_PHOTODIODES] = {15.0, 30.0, 45.0}; // mounting height light barriers
const uint8_t ledPins[NUM_PHOTODIODES] = {3, 4, 5}; // pin numbers of photo diodes
bool ledCurrentState[NUM_PHOTODIODES];
uint32_t ledEnterTime[NUM_PHOTODIODES];
uint32_t ledDuration[NUM_PHOTODIODES];

void setupPhotoDiodes() {
  for (uint8_t i = 0; i < NUM_PHOTODIODES; i++) {
    pinMode(ledPins[i], INPUT);
    ledCurrentState[i] = digitalRead(ledPins[i]);
  }
}

void loopReadPhotoDiodes() {
  for (uint8_t i = 0; i < NUM_PHOTODIODES; i++) {
    readPhotoDiode(i);
  }
}

void readPhotoDiode(uint8_t index) {
  bool newReading = digitalRead(getPinByIndex(index));
  
  if (ledCurrentState[index] == newReading) {
    // state has not changed since last reading
    return;
  }
  ledCurrentState[index] = newReading;
  
  if (ledCurrentState[index] == LOW) {
    // ball entered light barrier
    ledEnterTime[index] = micros();
    displaySensorValues();
    return;
  }
  // ball leaves light barrier
  ledDuration[index] = micros() - ledEnterTime[index];
  calculateBallMetrics();
  displaySensorValues();
}

int getPinByIndex(uint8_t index) {
  if (index >= 0 && index < NUM_PHOTODIODES) {
    return ledPins[index];
  } 
  return -1; // invalid index
}
