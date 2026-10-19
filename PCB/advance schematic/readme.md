# ESP32 Controller — Schematic Documentation

## 1. Deskripsi Proyek

Proyek ini merupakan pengembangan rangkaian kontroler berbasis **ESP32-DevKitC-32E** yang menggunakan dua modul joystick analog, beberapa tombol kontrol, sensor GY-521 (MPU6050), LED RGB, serta rangkaian pemantauan tegangan baterai.

Rangkaian dirancang sebagai perangkat input untuk membaca pergerakan joystick, menerima perintah dari tombol, dan menyediakan data sensor untuk kebutuhan sistem kendali elektronik, seperti robot atau kendaraan berbasis mikrokontroler.

## 2. Fitur Utama

- **Dual Analog Joystick:** Membaca input sumbu X dan Y dari dua modul joystick.
- **Button Control:** Menyediakan tombol untuk kontrol drop, pickup, peningkatan kecepatan, penurunan kecepatan, dan pemilihan mode.
- **IMU Sensor:** Menggunakan GY-521 berbasis MPU6050 untuk membaca percepatan dan kecepatan sudut.
- **Battery Voltage Monitoring:** Menyediakan rangkaian pembagi tegangan untuk membaca tegangan baterai melalui ADC ESP32.
- **RGB LED Indicator:** Menyediakan indikator visual melalui LED RGB.
- **ESP32 Microcontroller:** Bertindak sebagai pusat pembacaan input dan pemrosesan data kontrol.

## 3. Komponen yang Digunakan

| Komponen | Fungsi |
|---|---|
| ESP32-DevKitC-32E | Mikrokontroler utama |
| 2× Joystick Module | Input analog sumbu X dan Y |
| 6× Push Button | Input perintah kontrol |
| GY-521 (MPU6050) | Sensor gerak berbasis IMU |
| LED RGB | Indikator status |
| Resistor 10 kΩ | Jaringan tombol dan pembagi tegangan |
| Resistor 100 kΩ | Pembagi tegangan pemantauan baterai |
| Konektor baterai | Input tegangan baterai |
| Sakelar | Pengendalian jalur rangkaian sesuai skematik |

## 4. Pemetaan Pin ESP32

### A. Input Joystick

| Sinyal | GPIO ESP32 |
|---|---:|
| JOY.VRx1 | GPIO 33 |
| JOY.VRy1 | GPIO 32 |
| JOY.VRx2 | GPIO 35 |
| JOY.VRy2 | GPIO 34 |

GPIO 32, 33, 34, dan 35 digunakan untuk membaca sinyal analog dari kedua joystick. GPIO 34 dan GPIO 35 merupakan pin input-only sehingga sesuai untuk pembacaan ADC.

### B. Tombol Kontrol

| Sinyal | GPIO ESP32 | Fungsi |
|---|---:|---|
| CONTROL.drop | GPIO 13 | Perintah drop |
| CONTROL.plck | GPIO 14 | Perintah pickup |
| CONTROL.up | GPIO 26 | Menaikkan kecepatan |
| CONTROL.down | GPIO 25 | Menurunkan kecepatan |
| SW.mode.joy1 | GPIO 18 | Pemilihan mode joystick |
| SW.mode.sensor | GPIO 19 | Pemilihan mode sensor |

**Catatan:** Pemetaan pin mengikuti label jaringan pada skematik. Pastikan konfigurasi pin pada program sesuai dengan hasil akhir desain PCB.

### C. Sensor GY-521 (MPU6050)

| Sinyal | Koneksi |
|---|---|
| VCC | +5 V sesuai skematik |
| GND | GND |
| SDA | Jalur I²C SDA |
| SCL | Jalur I²C SCL |
| AD0 | Tidak terhubung |
| INT | Tidak terhubung |
| XCL dan XDA | Tidak terhubung |

Jalur SDA dan SCL dihubungkan ke GPIO ESP32 yang ditentukan dalam konfigurasi perangkat lunak. Pin AD0 yang tidak terhubung umumnya membuat alamat I²C MPU6050 berada pada `0x68`, tetapi kondisi pin perlu dipastikan pada modul yang digunakan.

### D. LED RGB

LED RGB digunakan sebagai indikator status perangkat. Setiap kanal warna terhubung ke jalur GPIO melalui rangkaian pada skematik.

**Catatan:** Nomor GPIO untuk setiap kanal LED perlu dipastikan dari label net dan koneksi lengkap pada skematik sebelum diimplementasikan dalam kode.

### E. Pemantauan Tegangan Baterai

Rangkaian pemantauan tegangan menggunakan resistor pembagi tegangan untuk menyesuaikan tegangan baterai dengan rentang input ADC ESP32.

Nilai tegangan input dapat dihitung menggunakan:

`V_baterai = V_ADC × (R_atas + R_bawah) / R_bawah`

Rumus tersebut berlaku untuk pembagi tegangan standar, dengan `R_atas` terhubung dari baterai positif ke titik ADC dan `R_bawah` terhubung dari titik ADC ke GND.

**Penting:** Nilai resistor dan jalur pada skematik perlu diverifikasi. Pastikan tegangan yang masuk ke pin ADC tidak melebihi batas aman ESP32. Jika ingin mengukur tegangan baterai di atas rentang ADC, gunakan pembagi tegangan yang sesuai.

## 5. Prinsip Kerja Sistem

1. ESP32 dinyalakan melalui sumber daya yang sesuai.
2. Kedua joystick menghasilkan sinyal analog sesuai posisi sumbu X dan Y.
3. ESP32 membaca perubahan sinyal analog melalui ADC.
4. Tombol memberikan perintah digital untuk drop, pickup, pengaturan kecepatan, dan pemilihan mode.
5. Sensor MPU6050 menyediakan data percepatan dan kecepatan sudut melalui komunikasi I²C.
6. Rangkaian pembagi tegangan menyediakan sinyal yang mewakili tegangan baterai untuk dipantau ESP32.
7. Data input diproses oleh firmware untuk menentukan perintah kontrol dan status sistem.

## 6. Perangkat Lunak

Firmware dapat dikembangkan menggunakan Arduino IDE atau PlatformIO dengan framework Arduino.

Library yang dapat digunakan:
- `Arduino.h` — fungsi dasar ESP32.
- `Wire.h` — komunikasi I²C.
- Library MPU6050 yang kompatibel — pembacaan data IMU.

## 7. Catatan Desain dan Pengujian

Sebelum rangkaian diproduksi atau digunakan, lakukan pemeriksaan berikut:

- Verifikasi semua koneksi daya, GND, dan GPIO.
- Pastikan setiap tombol memiliki logika input yang sesuai dengan konfigurasi resistor.
- Periksa apakah resistor 10 kΩ pada jaringan tombol berfungsi sebagai pull-up atau pull-down sesuai kebutuhan.
- Pastikan tegangan keluaran joystick tidak melebihi batas ADC ESP32.
- Verifikasi konfigurasi pembagi tegangan baterai dan batas tegangan ADC.
- Pastikan LED RGB memiliki resistor pembatas arus yang sesuai untuk setiap kanal.
- Periksa alamat I²C MPU6050 dan jalur SDA/SCL menggunakan pemindaian I²C.
- Lakukan pemeriksaan ERC pada skematik dan DRC pada layout PCB sebelum fabrikasi.

## 8. Kesimpulan

Rangkaian ini dirancang sebagai kontroler berbasis ESP32 dengan input joystick analog, tombol digital, sensor IMU, indikator RGB, dan pemantauan tegangan baterai. Integrasi komponen tersebut memungkinkan ESP32 mengumpulkan berbagai input untuk diproses menjadi perintah kendali. Validasi koneksi daya, pemetaan GPIO, dan rangkaian ADC perlu dilakukan sebelum implementasi perangkat lunak dan pembuatan PCB.

## 9. Schematic Rancangan
<img width="1380" height="697" alt="Cuplikan layar 2026-10-19 093344" src="https://github.com/user-attachments/assets/23844059-2483-4d9f-9fe1-2af210ca59ed" />

## 10. PCB Rancangan
<img width="1212" height="732" alt="image" src="https://github.com/user-attachments/assets/ea8af84e-dba8-453e-a4ef-96b0b1cf7d60" />
<img width="972" height="587" alt="image" src="https://github.com/user-attachments/assets/45741d34-0866-4ef0-b917-1ffc1f987192" />

