# Percobaan IC NE555 Timer

## 1. Deskripsi

Percobaan ini bertujuan untuk mempelajari penggunaan IC NE555 sebagai pembangkit sinyal pulsa (*pulse generator*). Rangkaian menggunakan konfigurasi astable atau osilator untuk menghasilkan sinyal keluaran secara periodik.

Sinyal keluaran dari pin 3 IC NE555 digunakan untuk mengendalikan LED sebagai indikator visual. Rangkaian menggunakan sumber tegangan 5 V, jaringan resistor, dan kapasitor untuk menentukan karakteristik sinyal yang dihasilkan.

## 2. Tujuan

- Memahami prinsip kerja IC NE555 Timer.
- Mempelajari konfigurasi rangkaian pembangkit pulsa.
- Memahami pengaruh resistor dan kapasitor terhadap frekuensi sinyal.
- Mengamati keluaran IC NE555 menggunakan LED.
- Memahami fungsi komponen pendukung pada rangkaian timer.

## 3. Alat dan Bahan

| No. | Komponen | Nilai / Tipe |
|---:|---|---|
| 1 | IC Timer | NE555P |
| 2 | Resistor R1 | 10 kΩ |
| 3 | Resistor R2 | 100 kΩ |
| 4 | Resistor R3 | 330 Ω |
| 5 | Kapasitor C1 | 10 µF |
| 6 | Kapasitor C2 | 100 nF |
| 7 | LED | 1 buah |
| 8 | Push button SW1 | 1 buah |
| 9 | Sumber tegangan | +5 V DC |
| 10 | Breadboard dan kabel jumper | Secukupnya |

## 4. Prinsip Kerja

IC NE555 dapat digunakan sebagai pembangkit sinyal pulsa dengan memanfaatkan proses pengisian dan pengosongan kapasitor.

Pada konfigurasi astable, tegangan kapasitor berubah secara periodik. Ketika tegangan kapasitor mencapai ambang tertentu, kondisi keluaran IC berubah sehingga menghasilkan sinyal pulsa berulang.

Sinyal keluaran tersebut dapat digunakan untuk mengendalikan LED sehingga perubahan kondisi keluaran dapat diamati secara visual.

## 5. Fungsi Komponen

| Komponen | Fungsi |
|---|---|
| NE555P | Menghasilkan sinyal pulsa |
| R1 (10 kΩ) | Bagian dari jaringan pengaturan dan pemicu rangkaian |
| R2 (100 kΩ) | Menentukan karakteristik pengisian dan pengosongan kapasitor sesuai konfigurasi |
| R3 (330 Ω) | Membatasi arus LED |
| C1 (10 µF) | Kapasitor timing yang memengaruhi periode sinyal |
| C2 (100 nF) | Kapasitor bypass atau decoupling untuk membantu menstabilkan suplai |
| SW1 | Tombol untuk mengubah kondisi rangkaian sesuai koneksinya |
| LED D1 | Indikator visual keluaran rangkaian |
| J1 | Konektor sumber daya +5 V dan GND |

## 6. Pin IC NE555

| Pin | Nama | Fungsi |
|---:|---|---|
| 1 | GND | Ground rangkaian |
| 2 | TRIG | Pemicu keluaran |
| 3 | OUT | Keluaran sinyal pulsa |
| 4 | RESET | Mengatur ulang atau menonaktifkan operasi IC ketika ditarik LOW |
| 5 | CONT | Mengatur tegangan referensi internal |
| 6 | THRES | Mendeteksi ambang tegangan kapasitor |
| 7 | DISCH | Jalur pengosongan kapasitor |
| 8 | VCC | Tegangan suplai positif |

## 7. Langkah Pengujian

1. Rakit rangkaian sesuai dengan skematik.
2. Pastikan seluruh koneksi IC NE555 sesuai dengan nomor pin.
3. Hubungkan sumber tegangan +5 V dan GND.
4. Amati kondisi LED setelah rangkaian diberi daya.
5. Tekan push button dan amati perubahan kondisi rangkaian.
6. Jika tersedia osiloskop, ukur sinyal keluaran pada pin 3 untuk mengamati bentuk gelombang, frekuensi, dan duty cycle.
7. Catat hasil pengamatan dan bandingkan dengan karakteristik rangkaian yang direncanakan.

## 8. Hasil yang Diharapkan

- IC NE555 bekerja sesuai konfigurasi rangkaiannya.
- Sinyal keluaran dapat diamati pada pin 3.
- LED menunjukkan perubahan kondisi sesuai sinyal keluaran.
- Pengukuran menggunakan osiloskop memperlihatkan bentuk gelombang keluaran yang sesuai dengan konfigurasi rangkaian.

## 9. Kesimpulan

Percobaan ini memperkenalkan penggunaan IC NE555 sebagai pembangkit sinyal pulsa. Resistor dan kapasitor berperan dalam menentukan karakteristik waktu rangkaian, sedangkan LED digunakan sebagai indikator keluaran. Pengukuran menggunakan osiloskop dapat membantu mengetahui frekuensi, periode, dan duty cycle sinyal secara lebih akurat.

## 10. Schematic Rangkaian 
<img width="1377" height="826" alt="image" src="https://github.com/user-attachments/assets/6695b340-7201-41f8-92f3-8d0146d995d7" />

## 11. PCB Rangkaian
<img width="718" height="780" alt="image" src="https://github.com/user-attachments/assets/e1f6b5d0-9230-41f2-bef1-cef3f3f7ca58" />

<img width="721" height="823" alt="image" src="https://github.com/user-attachments/assets/92443619-eef5-4ff5-888b-33e2d56f0978" />



