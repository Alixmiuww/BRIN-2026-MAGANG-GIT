# Percobaan ADC Potensiometer pada Arduino UNO

## Deskripsi

Program ini digunakan untuk membaca posisi potensiometer menggunakan fitur **ADC (Analog to Digital Converter)** pada Arduino UNO. Hasil pembacaan tegangan analog diolah menjadi tiga informasi, yaitu:

1. Nilai ADC mentah.
2. Tegangan input dalam satuan volt (V).
3. Persentase posisi putaran potensiometer (%).

Seluruh data ditampilkan melalui **Serial Monitor setiap 1 detik**. Potensiometer berfungsi sebagai input analog yang menghasilkan tegangan berbeda sesuai dengan posisi knop yang diputar.

## Tujuan Percobaan

- Memahami cara kerja ADC pada Arduino UNO.
- Membaca sinyal analog menggunakan pin `A0`.
- Mengonversi nilai ADC menjadi tegangan input.
- Menghitung persentase posisi potensiometer berdasarkan nilai ADC.
- Menampilkan hasil pembacaan secara berkala melalui Serial Monitor.

## Komponen yang Digunakan

- Arduino UNO
- Potensiometer
- Kabel jumper
- Kabel USB untuk menghubungkan Arduino ke komputer

## Konfigurasi Pin (Wiring)

| Pin Potensiometer | Arduino UNO | Fungsi |
|---|---|---|
| Pin 1 | 5V | Tegangan sumber |
| Pin 2 (tengah) | A0 | Output tegangan analog |
| Pin 3 | GND | Ground |

## Cara Kerja Program

1. Potensiometer dihubungkan ke sumber tegangan 5V, GND, dan pin analog `A0`.
2. Ketika knop diputar, tegangan pada pin `A0` berubah dari mendekati 0 V hingga mendekati 5 V.
3. Arduino membaca tegangan tersebut menggunakan ADC 10-bit.
4. Nilai ADC dikonversi menjadi tegangan input.
5. Nilai ADC juga dikonversi menjadi persentase posisi potensiometer.
6. Hasil pembacaan ditampilkan melalui Serial Monitor setiap 1 detik.

## Prinsip Kerja ADC

Arduino UNO menggunakan ADC dengan resolusi 10-bit, sehingga menghasilkan nilai digital dalam rentang **0–1023**.

- Nilai ADC 0 menunjukkan tegangan mendekati 0 V.
- Nilai ADC 512 menunjukkan tegangan sekitar setengah dari tegangan referensi.
- Nilai ADC 1023 menunjukkan tegangan mendekati tegangan referensi 5 V.

### 1. Konversi ADC menjadi Tegangan

Program menggunakan rumus:

```cpp
float tegangan = (nilaiADC * 5.0) / 1024.0;
```

Keterangan:
- `nilaiADC`: hasil pembacaan ADC.
- `5.0`: tegangan referensi (VREF) sebesar 5 V.
- `1024.0`: jumlah kemungkinan nilai digital ADC 10-bit.

Contoh, jika nilai ADC adalah 512:

\[
V_{in}=\frac{512\times5}{1024}=2{,}5\text{ V}
\]

Tegangan input yang terbaca adalah sekitar 2,5 V.

### 2. Konversi ADC menjadi Persentase

Program menggunakan rumus:

```cpp
float persentase = (nilaiADC / 1023.0) * 100.0;
```

Rumus tersebut mengubah rentang nilai ADC 0–1023 menjadi persentase 0–100%.

| Nilai ADC | Persentase | Posisi Knop |
|---:|---:|---|
| 0 | 0% | Minimum |
| 256 | ≈ 25% | Seperempat putaran |
| 512 | ≈ 50% | Sekitar posisi tengah |
| 768 | ≈ 75% | Tiga perempat putaran |
| 1023 | 100% | Maksimum |

## Hasil dan Analisis

Arduino membaca tegangan analog dari potensiometer melalui pin `A0` dan mengubahnya menjadi nilai digital menggunakan ADC 10-bit.

Nilai ADC kemudian digunakan untuk menghitung tegangan input dan persentase posisi potensiometer. Ketika knop diputar, nilai ADC, tegangan, dan persentase akan berubah sesuai dengan tegangan yang diterima oleh pin `A0`.

Sebagai contoh, nilai ADC sebesar 512 menunjukkan tegangan sekitar 2,5 V dan posisi potensiometer sekitar 50%. Dengan demikian, pembacaan ADC dapat digunakan untuk mengetahui perubahan tegangan sekaligus memperkirakan posisi putaran potensiometer.

**Catatan:** Rumus tegangan menggunakan pembagi 1024 sesuai pendekatan kuantisasi ADC 10-bit, sedangkan rumus persentase menggunakan 1023 agar nilai maksimum ADC setara dengan 100%.

## Kesimpulan

Percobaan ini menunjukkan bahwa Arduino UNO dapat membaca tegangan analog menggunakan ADC dan mengolah hasilnya menjadi informasi yang lebih mudah dipahami. Nilai ADC dapat dikonversi menjadi tegangan input dan persentase posisi potensiometer. Hasilnya ditampilkan secara berkala melalui Serial Monitor, sehingga perubahan posisi knop dapat diamati secara langsung.

## Software yang Digunakan

- Arduino IDE
- Serial Monitor
