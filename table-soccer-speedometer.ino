
// SFH 203
// https://stoppi-homemade-physics.de/wp-content/uploads/2021/02/Geschwindigkeitsmesser_Arduino_21-945x1024.jpg
// https://stoppi-homemade-physics.de/geschwindigkeitsmesser-arduino/

// thanks to the guys at nanolounge.de 
// https://www.nanolounge.de/37660/welcher-formel-lassen-flughohe-ballgeschwindigkeit-berechnen

// goal size ~ 200mm x 60mm




const float d = 33.7; // ball diameter
const float r = d/2.0; // ball radius

void setup() {
  //while (! Serial); 
  Serial.begin(115200);
  Serial.println("hello");
  setupPhotoDiodes();
  setupDisplay();
}

void loop() {
  //loopReadPhotoDiodes();
  loopDisplayTemp();
}
