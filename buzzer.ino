#include <Wire.h>
#include "GY_85.h"

GY_85 sensor;  // Instanțiază obiectul GY_85

const int buzzerPin = A1;  // Pinul la care este conectat buzzerul
const float minAccel = 200.0;  // Valoarea minimă a accelerației
const float maxAccel = 700.0;  // Valoarea maximă a accelerației
const int minFreq = 50;  // Frecvența minimă a buzzerului (Hz)
const int maxFreq = 2000;  // Frecvența maximă a buzzerului (Hz)
const float threshold = 200.0;  // Pragul minim al accelerației pentru a activa buzzerul

void setup() {
  Serial.begin(115200);  // Setează viteza portului serial la 115200 bps
  sensor.init();         // Inițializează senzorul GY-85
  pinMode(buzzerPin, OUTPUT);  // Setează pinul buzzerului ca ieșire
}

void loop() {
  // Citește datele de la senzor
  int* accel = sensor.readFromAccelerometer();
  
  // Verifică dacă datele au fost citite corect
  if (accel == nullptr) {
    Serial.println("Eroare la citirea accelerometrului!");
    return;
  }

  // Calcularea accelerației absolute
  float ax = accel[0];
  float ay = accel[1];
  float az = accel[2];
  float a_abs = sqrt(ax * ax + ay * ay + az * az);

  // Trimitere date prin portul serial în format pentru Serial Plotter
  Serial.print("X:"); Serial.print(ax);
  Serial.print("\tY:"); Serial.print(ay);
  Serial.print("\tZ:"); Serial.print(az);
  Serial.print("\tA_abs:"); Serial.print(a_abs);
  Serial.println();

  // Verifică dacă accelerația absolută este deasupra pragului
  if (a_abs > minAccel) {
    // Mapare accelerație la frecvența buzzerului
    int buzzerFreq;
    if (a_abs > maxAccel) {
      buzzerFreq = maxFreq;  // Setează frecvența maximă dacă accelerația este mai mare decât maximul
    } else {
      buzzerFreq = map(a_abs, minAccel, maxAccel, minFreq, maxFreq);  // Mapare linia
      buzzerFreq = constrain(buzzerFreq, minFreq, maxFreq);  // Asigură-te că frecvența este în intervalul permis
    }

    // Setează frecvența buzzerului
    tone(buzzerPin, buzzerFreq);
  } else {
    // Nu emite niciun sunet dacă accelerația este sub prag
    noTone(buzzerPin);
  }

  delay(20);  
}
