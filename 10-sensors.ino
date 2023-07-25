

// photodiode "SFH 203"
// https://www.conrad.at/de/p/fotodiode-sfh-203-5-mm-1100-nm-20-osram-sfh-203-154002.html

// photo transistor OSRAM SFH 309 Fototransistor 3 mm 1080 nm 12 °
// https://www.conrad.at/de/p/osram-sfh-309-fototransistor-3-mm-1080-nm-12-sfh-309-153870.html

#define NUM_GOALS 2
#define LEDS_PER_GOAL 8

// Mounting heights of light barriers for each goal
const float heights[NUM_GOALS][LEDS_PER_GOAL] = {
  {15.0, 30.0, 45.0, 60.0, 75.0, 90.0, 105.0, 120.0},  // Mounting heights for goal 1
  {10.0, 25.0, 40.0, 55.0, 70.0, 85.0, 100.0, 115.0}  // Mounting heights for goal 2
};

// Pin numbers of photo diodes for each goal
// @see https://randomnerdtutorials.com/esp32-pinout-reference-gpios/
// matrix display already uses pins 23, 5, 18
const uint8_t ledPins[NUM_GOALS][LEDS_PER_GOAL] = {
  {36, 12, 14, 27, 26, 25, 33, 32},  // LED pins for goal 1
  {35, 34, 15, 2, 4, 16, 17, 19}   // LED pins for goal 2
};

volatile bool ledCurrentState[NUM_GOALS][LEDS_PER_GOAL];
volatile uint32_t ledEnterTime[NUM_GOALS][LEDS_PER_GOAL];
volatile uint32_t ledDuration[NUM_GOALS][LEDS_PER_GOAL];


// helper variable that increases or decreases on light barrier state change
// so we can avoid to use 2 nested for-loops when checking if any light barrier is currently interrupted
volatile int8_t busyLeds[NUM_GOALS] = {0, 0};


// Declare individual ISR functions for each pin
// its very ugly but with this approach we can avoid nested loops in the ISR
// TODO: is there a way to pass arguments to an interrupt in the ESP32 (lambda)?
void IRAM_ATTR photoDiodeISRGoal0Index0() { photoDiodeISR(0, 0); }
void IRAM_ATTR photoDiodeISRGoal0Index1() { photoDiodeISR(0, 1); }
void IRAM_ATTR photoDiodeISRGoal0Index2() { photoDiodeISR(0, 2); }
void IRAM_ATTR photoDiodeISRGoal0Index3() { photoDiodeISR(0, 3); }
void IRAM_ATTR photoDiodeISRGoal0Index4() { photoDiodeISR(0, 4); }
void IRAM_ATTR photoDiodeISRGoal0Index5() { photoDiodeISR(0, 5); }
void IRAM_ATTR photoDiodeISRGoal0Index6() { photoDiodeISR(0, 6); }
void IRAM_ATTR photoDiodeISRGoal0Index7() { photoDiodeISR(0, 7); }

void IRAM_ATTR photoDiodeISRGoal1Index0() { photoDiodeISR(1, 0); }
void IRAM_ATTR photoDiodeISRGoal1Index1() { photoDiodeISR(1, 1); }
void IRAM_ATTR photoDiodeISRGoal1Index2() { photoDiodeISR(1, 2); }
void IRAM_ATTR photoDiodeISRGoal1Index3() { photoDiodeISR(1, 3); }
void IRAM_ATTR photoDiodeISRGoal1Index4() { photoDiodeISR(1, 4); }
void IRAM_ATTR photoDiodeISRGoal1Index5() { photoDiodeISR(1, 5); }
void IRAM_ATTR photoDiodeISRGoal1Index6() { photoDiodeISR(1, 6); }
void IRAM_ATTR photoDiodeISRGoal1Index7() { photoDiodeISR(1, 7); }

void photoDiodeISR(uint8_t goal, uint8_t index) {
  ledCurrentState[goal][index] = digitalRead(ledPins[goal][index]);

  Serial.print("g:");
  Serial.print(goal);
  Serial.print(" i:");
  Serial.print(index);
  Serial.print(" to:");
  Serial.println(ledCurrentState[goal][index]);

  if (ledCurrentState[goal][index] == LOW) {
    // ball entered light barrier
    ledEnterTime[goal][index] = micros();
    busyLeds[goal]++;
    return;
  }
  // ball leaves light barrier
  ledDuration[goal][index] = micros() - ledEnterTime[goal][index];
  busyLeds[goal]--;
  if (busyLeds[goal] > 0) {
    return;
  }
  // the ball has left all light barriers for this goal
  busyLeds[goal] = 0;
  calculateBallMetrics(goal);
}

void setupPhotoDiodes() {
  for (uint8_t goal = 0; goal < NUM_GOALS; goal++) {
    for (uint8_t i = 0; i < LEDS_PER_GOAL; i++) {
      pinMode(ledPins[goal][i], INPUT_PULLUP);
      ledCurrentState[goal][i] = digitalRead(ledPins[goal][i]);

      // Use the void* argument of attachInterrupt to pass the goal and index
      uint8_t isrIndex = goal * LEDS_PER_GOAL + i;
      switch (isrIndex) {
        case 0: attachInterrupt(digitalPinToInterrupt(ledPins[goal][i]), photoDiodeISRGoal0Index0, CHANGE); break;
        case 1: attachInterrupt(digitalPinToInterrupt(ledPins[goal][i]), photoDiodeISRGoal0Index1, CHANGE); break;
        case 2: attachInterrupt(digitalPinToInterrupt(ledPins[goal][i]), photoDiodeISRGoal0Index2, CHANGE); break;
        case 3: attachInterrupt(digitalPinToInterrupt(ledPins[goal][i]), photoDiodeISRGoal0Index3, CHANGE); break;
        case 4: attachInterrupt(digitalPinToInterrupt(ledPins[goal][i]), photoDiodeISRGoal0Index4, CHANGE); break;
        case 5: attachInterrupt(digitalPinToInterrupt(ledPins[goal][i]), photoDiodeISRGoal0Index5, CHANGE); break;
        case 6: attachInterrupt(digitalPinToInterrupt(ledPins[goal][i]), photoDiodeISRGoal0Index6, CHANGE); break;
        case 7: attachInterrupt(digitalPinToInterrupt(ledPins[goal][i]), photoDiodeISRGoal0Index7, CHANGE); break;
        case 8: attachInterrupt(digitalPinToInterrupt(ledPins[goal][i]), photoDiodeISRGoal1Index0, CHANGE); break;
        case 9: attachInterrupt(digitalPinToInterrupt(ledPins[goal][i]), photoDiodeISRGoal1Index1, CHANGE); break;
        case 10: attachInterrupt(digitalPinToInterrupt(ledPins[goal][i]), photoDiodeISRGoal1Index2, CHANGE); break;
        case 11: attachInterrupt(digitalPinToInterrupt(ledPins[goal][i]), photoDiodeISRGoal1Index3, CHANGE); break;
        case 12: attachInterrupt(digitalPinToInterrupt(ledPins[goal][i]), photoDiodeISRGoal1Index4, CHANGE); break;
        case 13: attachInterrupt(digitalPinToInterrupt(ledPins[goal][i]), photoDiodeISRGoal1Index5, CHANGE); break;
        case 14: attachInterrupt(digitalPinToInterrupt(ledPins[goal][i]), photoDiodeISRGoal1Index6, CHANGE); break;
        case 15: attachInterrupt(digitalPinToInterrupt(ledPins[goal][i]), photoDiodeISRGoal1Index7, CHANGE); break;
        default: break;
      }
    }
  }
}
