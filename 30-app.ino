

void calculateBallMetrics() {
  for (uint8_t i = 0; i < NUM_PHOTODIODES; i++) {
    if (ledCurrentState[i] == LOW) {
      // the ball is still within at least one light barrier
      return;
    }
  }


  Serial.println("######### calculate speed and height #############");

  float h = 0.0;  // flight height of ball
  float v = 0.0;  // ball speed

  float distanceToBallCenter = 0.0;

  float ratio = 0.0; // ratio between t-lower and t-upper

  for (uint8_t i = 0; i < NUM_PHOTODIODES-1; i++) {
    if (ledDuration[i] != 0 && ledDuration[i+1] != 0) {
      ratio = float(ledDuration[i])/float(ledDuration[i+1]);
      h = calculateFlightHeight(ratio, heights[i], heights[i+1]);
      distanceToBallCenter = h + r - (heights[i] + ((heights[i+1]-heights[i])/2));
      Serial.print("h = ");
      Serial.print(h);
      Serial.print(" mm idx:");
      Serial.print(i);
      Serial.print(" to center: ");
      Serial.println(abs(distanceToBallCenter), 1);
    }
  }
  if (ratio == 0.0) {
    return;
  }
  v = calculateSpeed(h);
  displaySpeedAndHeight(v, h);
  for (uint8_t i = 0; i < NUM_PHOTODIODES; i++) {
    ledDuration[i] = 0.0;
  }
}


// berechnet die Entfernung der Schnittpunkte einer horizontalen geraden linie in der höhe y mit einem kreis mit durchmesser d
float calculateDistanceInCircle(float y) {

 // Berechnung der Schnittpunkte
  float term = sqrt(sq(r) - sq(y - r));
  float x1x = r - term;
  float x2x = r + term;

  // Berechnung der Entfernung der Schnittpunkte
  return abs(x2x - x1x);
}




float calculateFlightHeight(float ratio, float lower, float upper) {
  /*
  Serial.print(ratio, 5);
  Serial.print(" ");
  Serial.print(lower);
  Serial.print(" ");
  Serial.print(upper);
  Serial.println(" ");
  */
  // https://www.nanolounge.de/37660/welcher-formel-lassen-flughohe-ballgeschwindigkeit-berechnen?show=37679#c37679
  // https://www.wolframalpha.com/input?i=solve+h%2C+x+%3D+sqrt%28sq%28r%29-sq%28a-h-r%29%29+%2F+sqrt%28sq%28r%29-sq%28b-h-r%29
  return (
    sqrt(
      sq(lower)*sq(ratio)-2*lower*upper*sq(ratio)+sq(upper)*sq(ratio)+sq(r)*pow(ratio,4)-2*sq(r)*sq(ratio)+sq(r)
    )*-1-lower+upper*sq(ratio)-r*sq(ratio)+r
    ) / (
      sq(ratio)-1
  );

  // 2nd result for isolating "h"
  // return (sqrt(sq(lower)*sq(ratio)-2*lower*upper*sq(ratio)+sq(upper)*sq(ratio)+sq(r)*pow(ratio,4)-2*sq(r)*sq(ratio)+sq(r))-lower+upper*sq(ratio)-r*sq(ratio)+r)/(sq(ratio)-1);

}



float calculateSpeed(float height) {

  float distanceToBallCenter = 0.0;
  float dist = 0.0;

  float v = 0.0;

  for (uint8_t i = 0; i < NUM_PHOTODIODES; i++) {
    if (ledDuration[i] == 0) {
      continue;
    }
    distanceToBallCenter = height + r - heights[i];
    dist = calculateDistanceInCircle(heights[i]-height);
    // convert microseconds/mm to km/h
    v = dist / float(ledDuration[i]) * 3600;
    
    //Serial.print(dist);
    //Serial.print(" dist-ledDuration[i] ");
    //Serial.println(ledDuration[i]);
    Serial.print("v = ");
    Serial.print(v, 2);
    Serial.print(" km/h idx:");
    Serial.print(i);
    Serial.print(" to center: ");
    Serial.print(abs(distanceToBallCenter));
    Serial.println(" mm");
  }
  return v;
  
}
