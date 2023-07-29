
// SFH 203
// https://stoppi-homemade-physics.de/wp-content/uploads/2021/02/Geschwindigkeitsmesser_Arduino_21-945x1024.jpg
// https://stoppi-homemade-physics.de/geschwindigkeitsmesser-arduino/

// thanks to the guys at nanolounge.de 
// https://www.nanolounge.de/37660/welcher-formel-lassen-flughohe-ballgeschwindigkeit-berechnen

// goal size ~ 200mm x 60mm

#define NUM_BUTTONS 4

#define NUM_GOALS 2
#define SENSORS_PER_GOAL 10

// do not use serial debug in production to assure we have the most accurate measurements [microseconds]
#define SERIALDEBUG 1
#define CALIBRATION 1

// Mounting heights [mm] of light barriers for each goal
const float sensorHeights[NUM_GOALS][SENSORS_PER_GOAL] = {
  { 15.0, 30.0, 45.0, 60.0, 75.0, 90.0, 105.0, 120.0 }, // Sensor mounting heights for goal 1
  { 15.0, 30.0, 45.0, 60.0, 75.0, 90.0, 105.0, 120.0 }  // Sensor mounting heights for goal 2
};

// Pin numbers of sensors (photo diode or photo transistor) for each goal
// @see https://randomnerdtutorials.com/esp32-pinout-reference-gpios/
// matrix display already uses pins 23, 5, 18
const uint8_t sensorPins[NUM_GOALS][SENSORS_PER_GOAL] = {
  { 33, 25, 26, 36, 39, 34, 35, 32 },  // Sensor pins for goal 1
  { 27, 14, 12, 13, 17, 19, 21, 22 }   // Sensor pins for goal 2
};


const uint8_t buttonPins[NUM_BUTTONS] = { 16, 4, 2, 15 };

const float d = 33.7; // ball diameter
const float r = d/2.0; // ball radius


void setup() {
#if SERIALDEBUG
  Serial.begin(115200);
  Serial.println("table-soccer-speedometer setup()");
#endif
  setupSensors();
  setupButtons();
  setupDisplay();
}


void loop() {
  //loopReadPhotoDiodes();
  // loopDisplayTemp();
  loopReadSensors();
  loopReadButtons();
}
