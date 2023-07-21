

// photodiode "SFH 203"
// https://www.conrad.at/de/p/fotodiode-sfh-203-5-mm-1100-nm-20-osram-sfh-203-154002.html

#define NUM_GOALS 2 // amount of goals
#define LEDS_PER_GOAL 3 // amount of photo diodes per goal

// Mounting heights of light barriers for each goal
const float heights[NUM_GOALS][LEDS_PER_GOAL] = {
  {15.0, 30.0, 45.0}, // Mounting heights for goal 1
  {10.0, 25.0, 40.0}  // Mounting heights for goal 2
};

// Pin numbers of photo diodes for each goal
const uint8_t ledPins[NUM_GOALS][LEDS_PER_GOAL] = {
  {3, 4, 5}, // LED pins for goal 1
  {6, 7, 8}  // LED pins for goal 2
};

bool ledCurrentState[NUM_GOALS][LEDS_PER_GOAL];
uint32_t ledEnterTime[NUM_GOALS][LEDS_PER_GOAL];
uint32_t ledDuration[NUM_GOALS][LEDS_PER_GOAL];

// helper variable that increases or decreases on light barrier state change
// so we can avoid to use 2 nested for-loops when checking if any light barrier is currently interrupted
int8_t busyLeds[NUM_GOALS] = {0, 0};

void setupPhotoDiodes() {
  for (uint8_t goal = 0; goal < NUM_GOALS; goal++) {
    for (uint8_t i = 0; i < LEDS_PER_GOAL; i++) {
      pinMode(ledPins[goal][i], INPUT);
      ledCurrentState[goal][i] = digitalRead(ledPins[goal][i]);
    }
  }
}

void loopReadPhotoDiodes() {
  for (uint8_t goal = 0; goal < NUM_GOALS; goal++) {
    for (uint8_t i = 0; i < LEDS_PER_GOAL; i++) {
      readPhotoDiode(goal, i);
    }
  }
}

void readPhotoDiode(uint8_t goal, uint8_t index) {
  bool newReading = digitalRead(ledPins[goal][index]);
  
  if (ledCurrentState[goal][index] == newReading) {
    // state has not changed since last reading
    return;
  }
  ledCurrentState[goal][index] = newReading;
  
  if (ledCurrentState[goal][index] == LOW) {
    // ball entered light barrier
    ledEnterTime[goal][index] = micros();
    displaySensorValues();
    busyLeds[goal]++;
    return;
  }
  // ball leaves light barrier
  ledDuration[goal][index] = micros() - ledEnterTime[goal][index];
  busyLeds[goal]--;
  if (busyLeds[goal] > 0) {
    // the ball is still within one light barrier
    return;
  }
  calculateBallMetrics(goal);
  // displaySensorValues();
}
