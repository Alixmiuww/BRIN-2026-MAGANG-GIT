#include <Arduino.h> // Arduino berperan sebagai Controller/Master
#include <Wire.h> // Library untuk komunikasi I2C
void setup() {
  // Memulai komunikasi I2C sebagai Master
  Wire.begin();
  // Memulai komunikasi Serial Monitor
  Serial.begin(9600);
  Serial.println("\nMemulai pencarian alamat I2C...");
}
void loop() {
  byte error, address;
  int nDevices = 0;
  Serial.println("Mencari...");
  // Scan alamat I2C 7-bit: 0x01 - 0x7E
  for(address = 1; address < 127; address++ ) {
    // Mengirim alamat target untuk memulai komunikasi
    Wire.beginTransmission(address);
    // Mengakhiri transmisi dan mengecek respons/ACK
    error = Wire.endTransmission();
    // Jika ACK diterima, perangkat ditemukan
    if (error == 0) {
      Serial.print("Modul I2C ditemukan di alamat: 0x");

      // Menambahkan 0 untuk format 2 digit hexadecimal
      if (address < 16) 
        Serial.print("0");
      // Menampilkan alamat dalam format hexadecimal
      Serial.println(address, HEX); 
      nDevices++;     }    }
  
  // Mengecek apakah ada perangkat yang terdeteksi
  if (nDevices == 0) {
    Serial.println("Tidak ada perangkat I2C yang terdeteksi.");
  } else {
    Serial.println("Pencarian selesai.\n");   }
  // Scan ulang setiap 5 detik
  delay(5000);  }
