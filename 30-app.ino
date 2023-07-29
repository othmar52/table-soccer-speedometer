

void calculateBallMetrics(uint8_t goal) {
#if SERIALDEBUG
  Serial.println("######### calculate speed and height #############");
  for (uint8_t i = 0; i < SENSORS_PER_GOAL; i++) {
    Serial.print(sensorDuration[goal][i]);
    Serial.print(" ");
  }
  Serial.println(" ");
#endif

  float fleightHeight = 0.0;  // flight height of ball
  float v = 0.0;  // ball speed

  float distanceToBallCenter = 0.0;

  float ratio = 0.0; // ratio between t-lower and t-upper

  // Permutation of height calculation
  for (uint8_t i = 0; i < SENSORS_PER_GOAL; i++) {
    for (uint8_t j = 1; j < SENSORS_PER_GOAL; j++) {
      if (i >= j) {
        // we have always lower divided by upper
        continue;
      }
      if (sensorDuration[goal][i] == 0 || sensorDuration[goal][j] == 0) {
        // one of the 2 light barriers has not been interrupted
        // so its not possible to calculate the fleight height with this light barrier combo
        continue;
      }

      ratio = float(sensorDuration[goal][i]) / float(sensorDuration[goal][j]);
      fleightHeight = calculateFlightHeight(ratio, sensorHeights[goal][i], sensorHeights[goal][j]);
      distanceToBallCenter = fleightHeight + r - (sensorHeights[goal][i] + ((sensorHeights[goal][j] - sensorHeights[goal][i]) / 2));

#if SERIALDEBUG
      Serial.print("fleightHeight = ");
      Serial.print(fleightHeight);
      Serial.print(" mm Goal: ");
      Serial.print(goal + 1);
      Serial.print(" idx1: ");
      Serial.print(i);
      Serial.print(" idx2: ");
      Serial.print(j);
      Serial.print(" to center: ");
      Serial.println(abs(distanceToBallCenter), 1);
#endif
    }
  }

  // calculate speed based on flight height
  
  if (fleightHeight != 0.0) {
    v = calculateSpeed(goal, fleightHeight);
    //displaySpeedAndHeight(v, h);
    
  }
  
  displaySpeedAndHeightTimes(v, fleightHeight, sensorDuration[goal][0], sensorDuration[goal][1], sensorDuration[goal][2]);

  // reset measured times as we already have processed it
  for (uint8_t i = 0; i < SENSORS_PER_GOAL; i++) {
    //if (sensorCurrentState[goal][i] == HIGH) {
      sensorDuration[goal][i] = 0;
    //}
  }
  
}

// Calculates the distance between the intersection points of a horizontal straight line at height y and a circle with diameter d.
float calculateDistanceInCircle(float y) {

 // Calculation of intersection points
  float term = sqrt(sq(r) - sq(y - r));
  float x1x = r - term;
  float x2x = r + term;

  // Calculation of distance between the 2 intersection points
  return abs(x2x - x1x);
}



/**
 * @param float ratio: ratio between time-lower and time-upper
 * @param float lower: mounting height of lower light barrier [mm]
 * @param float upper: mounting height of upper light barrier [mm]
 * @return float height: the calculated fleight height [mm]
 */
float calculateFlightHeight(float ratio, float lower, float upper) {
#if SERIALDEBUG
  /*
  Serial.print(ratio, 5);
  Serial.print(" ");
  Serial.print(lower);
  Serial.print(" ");
  Serial.print(upper);
  Serial.println(" ");
  */
#endif
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



float calculateSpeed(uint8_t goal, float fleightHeight) {

  float distanceToBallCenter = 0.0;
  float dist = 0.0;

  float v = 0.0;
  for (uint8_t i = 0; i < SENSORS_PER_GOAL; i++) {

    if (sensorDuration[goal][i] == 0) {
      continue;
    }
    distanceToBallCenter = fleightHeight + r - sensorHeights[goal][i];
    dist = calculateDistanceInCircle(sensorHeights[goal][i]-fleightHeight);
    // convert microseconds/mm to km/h
    v = dist / float(sensorDuration[goal][i]) * 3600;

#if SERIALDEBUG
    //Serial.print(dist);
    //Serial.print(" dist-sensorDuration[goal][i] ");
    //Serial.println(sensorDuration[goal][i]);
    Serial.print("v = ");
    Serial.print(v, 2);
    Serial.print(" km/h idx:");
    Serial.print(i);
    Serial.print(" to center: ");
    Serial.print(abs(distanceToBallCenter));
    Serial.println(" mm");
#endif
  }
  return v;
  
}
