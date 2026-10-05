#include <Arduino.h>

const int pinPotensio = A0;
unsigned long timerADC = 0;
const long intervalADC = 1000;

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (millis() - timerADC >= intervalADC) {
    int nilaiADC = analogRead(pinPotensio);

    // Perhitungan matematis konversi ADC ke Tegangan
    float tegangan = (nilaiADC * 5.0) / 1024.0;

    // Konversi nilai ADC ke persentase putaran knop (0–100%)
    float persentase = (nilaiADC / 1023.0) * 100.0;

    Serial.print("Angka Mentah ADC: ");
    Serial.print(nilaiADC);
    Serial.print(" | Tegangan: ");
    Serial.print(tegangan, 3);
    Serial.print(" V | Putaran: ");
    Serial.print(persentase, 1);
    Serial.println(" %");

    timerADC = millis();
  }
}
