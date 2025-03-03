#include <Wire.h>
#include "GY_85.h"

GY_85 sensor;  // Instanțiază obiectul GY_85

int last_ax = 0, last_ay = 0;  // Variabile pentru a stoca valorile anterioare

void setup() {
  Serial.begin(115200);  // Setează viteza portului serial la 115200 bps
  sensor.init();         // Inițializează senzorul GY-85
}

void loop() {
  int* accel = sensor.readFromAccelerometer();

  int ax = accel[0];
  int ay = accel[1];

  // Verifică dacă diferența dintre valorile consecutive este mai mare de 10
  if (abs(ax - last_ax) > 50 || abs(ay - last_ay) > 50) {
    // Transmite doar valorile ax și ay
    Serial.print("{"); 
    Serial.print("\"ax\":"); Serial.print(ax); Serial.print(",");
    Serial.print("\"ay\":"); Serial.print(ay);
    Serial.println("}");

    // Actualizează valorile anterioare
    last_ax = ax;
    last_ay = ay;
  } 

  delay(100);  // Așteaptă 100 ms înainte de a citi din nou
}
