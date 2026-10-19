Program ini digunakan untuk membaca posisi potensiometer menggunakan fitur ADC (Analog to Digital Converter) pada Arduino.
Hasil pembacaan kemudian diolah menjadi tiga informasi:
1.	Nilai ADC mentah
2.	Tegangan input
3.	Persentase posisi putaran potensiometer
Data ditampilkan melalui Serial Monitor setiap 1 detik. Potensiometer menghasilkan tegangan analog yang berubah sesuai dengan posisi knop.
Konfigurasi Pin :
Pin Potensiometer	Arduino	Fungsi
Pin 1	5V	Tegangan sumber
Pin 2 (tengah)	A0	Output tegangan analog
Pin 3	GND	Ground
Ketika knop diputar, tegangan pada pin A0 berubah dari mendekati 0 V hingga 5 V. Arduino kemudian mengubah tegangan tersebut menjadi nilai digital menggunakan ADC. Pada Arduino UNO, ADC memiliki resolusi 10-bit, sehingga nilai yang dihasilkan berada pada rentang 0–1023.

Hasil	Analisis : Arduino membaca tegangan dari potensiometer melalui pin A0 menggunakan ADC 10-bit. Hasil pembacaan ADC berada pada rentang 0–1023.
Nilai tersebut kemudian dikonversi menjadi tegangan. Pada program digunakan rumus:
float tegangan = (nilaiADC * 5.0) / 1024.0;
Angka 5.0 menunjukkan tegangan referensi atau VREF sebesar 5 V.
Sebagai contoh, jika nilai ADC yang terbaca adalah 512, maka tegangan pada pin A0 sekitar 2,5 V.
Selain tegangan, program juga mengubah nilai ADC menjadi persentase posisi potensiometer.
float persentase = (nilaiADC / 1023.0) * 100.0;
Karena nilai ADC berada pada rentang 0–1023, maka rentang tersebut diubah menjadi 0–100%.
Nilai ADC	Persentase
0	0%
256	≈ 25%
512	≈ 50%
768	≈ 75%
1023	100%
Dengan cara ini, posisi potensiometer dapat dipahami dengan lebih mudah. Misalnya, ADC = 512 berarti posisi potensiometer sekitar 50%, sehingga knop berada di sekitar posisi tengah.
