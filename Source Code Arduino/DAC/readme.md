# Percobaan DAC Menggunakan PWM pada Arduino UNO

## Deskripsi

Program ini mensimulasikan konsep **DAC (Digital to Analog Converter)** menggunakan fitur **PWM (Pulse Width Modulation)** pada Arduino UNO. Potensiometer digunakan sebagai input analog yang dibaca melalui ADC, kemudian nilai ADC dikonversi menjadi nilai PWM untuk mengatur duty cycle sinyal keluaran.

Semakin besar putaran potensiometer, semakin besar nilai ADC dan PWM yang dihasilkan. Nilai PWM juga digunakan untuk menghitung estimasi tegangan keluaran secara matematis.

Data ditampilkan melalui Serial Monitor setiap 500 ms.

## Tujuan Percobaan

- Memahami konsep DAC menggunakan PWM.
- Membaca tegangan analog dari potensiometer melalui ADC.
- Mengonversi nilai ADC 10-bit menjadi nilai PWM 8-bit.
- Memahami hubungan nilai ADC, duty cycle PWM, dan estimasi tegangan keluaran.
- Mengamati perubahan nilai melalui Serial Monitor.

## Komponen yang Digunakan

- Arduino UNO
- Potensiometer
- Kabel jumper
- Kabel USB
- Multimeter (opsional, untuk pengukuran tegangan)

## Konfigurasi Pin (Wiring)

| Komponen | Pin Arduino UNO | Fungsi |
|---|---|---|
| Potensiometer | 5V | Tegangan sumber |
| Potensiometer (pin tengah) | A0 | Input analog / ADC |
| Potensiometer | GND | Ground |
| Output PWM | D9 | Keluaran sinyal PWM |

## Cara Kerja Program

1. **Pembacaan ADC:** Arduino membaca tegangan dari potensiometer melalui pin A0. Hasil pembacaan memiliki rentang 0–1023.
2. **Konversi ADC ke PWM:** Nilai ADC dibagi 4 untuk menghasilkan nilai PWM dalam rentang 0–255.
3. **Keluaran PWM:** Fungsi `analogWrite()` menghasilkan sinyal PWM pada pin D9 sesuai nilai yang diperoleh.
4. **Estimasi tegangan:** Program menghitung estimasi tegangan berdasarkan nilai PWM dengan asumsi tegangan referensi 5 V.
5. **Monitoring:** Nilai ADC, PWM, dan estimasi tegangan ditampilkan melalui Serial Monitor setiap 500 ms.

## Prinsip Kerja PWM sebagai DAC

Arduino UNO tidak memiliki DAC sejati pada pin D9. Sebagai gantinya, PWM digunakan untuk menghasilkan sinyal digital yang memiliki duty cycle bervariasi.

Duty cycle menunjukkan persentase waktu sinyal berada pada kondisi HIGH dalam satu periode.

| Nilai PWM | Duty Cycle | Estimasi Tegangan Rata-rata |
|---:|---:|---:|
| 0 | 0% | 0 V |
| 64 | ≈ 25% | ≈ 1,25 V |
| 128 | ≈ 50% | ≈ 2,51 V |
| 192 | ≈ 75% | ≈ 3,76 V |
| 255 | 100% | 5 V |


**Catatan:** Tegangan pada pin D9 tetap berupa pulsa digital HIGH dan LOW, bukan tegangan analog konstan. Untuk memperoleh tegangan yang lebih halus, sinyal PWM dapat dilewatkan melalui rangkaian low-pass filter RC.

## Hasil dan Analisis

Berdasarkan pengujian, ketika nilai ADC mencapai 1023, nilai PWM yang dihasilkan adalah 255. Kondisi ini menunjukkan duty cycle PWM mencapai 100%, sehingga keluaran pin D9 berada pada kondisi HIGH secara terus-menerus.

Pengukuran menggunakan multimeter menunjukkan tegangan sekitar 5,17 V, sedangkan program memperkirakan tegangan sebesar 5,00 V.

Perbedaan tersebut dapat disebabkan oleh tegangan catu daya aktual, karakteristik board Arduino, dan ketelitian alat ukur. Nilai 5,00 V dalam program merupakan asumsi perhitungan, bukan hasil pengukuran tegangan aktual.

Secara keseluruhan, hasil percobaan menunjukkan bahwa semakin besar nilai ADC dari potensiometer, semakin besar pula nilai PWM yang dihasilkan. Dengan demikian, duty cycle PWM dapat digunakan untuk mengendalikan tegangan rata-rata keluaran, terutama jika sinyal dilewatkan melalui low-pass filter.

## Kesimpulan

Percobaan ini menunjukkan bahwa konsep DAC dapat disimulasikan menggunakan PWM pada Arduino UNO. Nilai ADC dari potensiometer dikonversi menjadi nilai PWM 8-bit untuk mengatur duty cycle keluaran. Perubahan nilai PWM menghasilkan perubahan tegangan rata-rata secara ideal, meskipun sinyal pada pin D9 tetap berupa pulsa digital. Oleh karena itu, PWM dapat digunakan sebagai alternatif sederhana untuk menghasilkan tegangan analog semu dengan bantuan rangkaian filter.

## Software yang Digunakan

- Arduino IDE
- Serial Monitor

