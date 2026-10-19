# Studi Kasus Push Button, LED Toggle, dan Debouncing pada Arduino UNO

## Deskripsi

Studi kasus ini bertujuan untuk mengendalikan LED menggunakan push button pada Arduino UNO. Setiap kali tombol ditekan, status LED akan berubah dari menyala menjadi mati atau sebaliknya. Program juga menghitung jumlah tekanan tombol dan menampilkan informasi tersebut melalui Serial Monitor.

Untuk menghindari pembacaan tekanan ganda akibat pantulan kontak mekanis (*button bouncing*), program menerapkan **software debouncing secara non-blocking** menggunakan fungsi `millis()`.

## Tujuan Percobaan

- Memahami penggunaan push button sebagai input digital.
- Mengendalikan LED menggunakan output digital Arduino.
- Mengimplementasikan logika toggle untuk mengubah status LED.
- Menghitung jumlah tekanan tombol menggunakan counter.
- Memahami dan menerapkan teknik debouncing pada push button.
- Menampilkan status LED dan jumlah tekanan melalui Serial Monitor.

## Komponen yang Digunakan

| No. | Komponen | Jumlah |
|---:|---|---:|
| 1 | Arduino UNO | 1 buah |
| 2 | Push button | 1 buah |
| 3 | LED | 1 buah |
| 4 | Resistor 220 Ω untuk LED | 1 buah |
| 5 | Resistor 10 kΩ untuk tombol (opsional) | 1 buah |
| 6 | Kabel jumper | Secukupnya |
| 7 | Kabel USB | 1 buah |

## Konfigurasi Pin (Wiring)

| Komponen | Pin Arduino UNO | Fungsi |
|---|---|---|
| Push button | D2 dan GND | Input tombol dengan `INPUT_PULLUP` |
| Anoda LED | D8 melalui resistor 220 Ω | Output kendali LED |
| Katoda LED | GND | Ground |
| USB | Komputer | Komunikasi Serial Monitor |

**Catatan:** Karena program menggunakan `INPUT_PULLUP`, tombol dihubungkan antara pin D2 dan GND. Resistor pull-up internal Arduino digunakan sehingga resistor eksternal 10 kΩ tidak diperlukan untuk konfigurasi ini.

## Cara Kerja Program

1. Arduino mengatur pin D2 sebagai input menggunakan `INPUT_PULLUP` dan pin D8 sebagai output LED.
2. Serial Monitor diinisialisasi dengan baud rate 9600.
3. Program membaca kondisi tombol menggunakan `digitalRead()`.
4. Ketika pembacaan tombol berubah, waktu debounce diperbarui menggunakan `millis()`.
5. Perubahan status baru diproses setelah pembacaan stabil selama lebih dari 50 milidetik.
6. Ketika tombol terdeteksi ditekan, status LED dibalik menggunakan `ledState = !ledState`.
7. Counter `pressCount` bertambah satu untuk setiap tekanan yang terdeteksi.
8. Jumlah tekanan dan status LED ditampilkan melalui Serial Monitor.

## Hasil Pengujian

Setiap kali push button ditekan, LED berganti status antara menyala dan mati. Pada saat yang sama, nilai counter bertambah satu dan informasi ditampilkan melalui Serial Monitor.

Contoh keluaran Serial Monitor:

```text
Sistem Siap. Silakan tekan tombol!
Tombol ditekan! Total: 1 | Status LED: MENYALA (Silakan ukur tegangan!)
Tombol ditekan! Total: 2 | Status LED: MATI
Tombol ditekan! Total: 3 | Status LED: MENYALA (Silakan ukur tegangan!)
Tombol ditekan! Total: 4 | Status LED: MATI
```

## Analisis: Apakah Debouncing Diperlukan?

Debouncing diperlukan karena push button mekanis tidak selalu menghasilkan perubahan sinyal yang bersih ketika ditekan atau dilepas. Kontak logam di dalam tombol dapat memantul beberapa kali dalam rentang mikrodetik hingga milidetik sebelum stabil.

Mikrokontroler dapat membaca pantulan tersebut sebagai beberapa perubahan status, meskipun pengguna hanya menekan tombol satu kali. Akibatnya, LED dapat berubah status berulang kali dan counter dapat bertambah lebih dari satu.

Terdapat dua pendekatan utama untuk menangani debouncing.

### 1. Hardware Debouncing

Hardware debouncing menggunakan rangkaian tambahan, seperti resistor-kapasitor (RC) atau IC flip-flop, untuk menyaring perubahan tegangan akibat bouncing sebelum sinyal diterima mikrokontroler.

- **Kelebihan:** Penyaringan dilakukan oleh rangkaian elektronik tanpa bergantung pada pemrosesan debounce di dalam kode.
- **Kekurangan:** Membutuhkan komponen tambahan dan karakteristik penyaringannya ditentukan oleh rangkaian yang digunakan.

### 2. Software Debouncing

Software debouncing menangani bouncing melalui kode program tanpa memerlukan komponen tambahan. Pada program ini, teknik tersebut diterapkan secara non-blocking menggunakan `millis()`.

Variabel `lastDebounceTime` menyimpan waktu ketika perubahan pembacaan terakhir terdeteksi. Status tombol baru diproses apabila pembacaan telah stabil selama lebih dari `debounceDelay`, yaitu 50 milidetik.

Pendekatan non-blocking tidak menghentikan eksekusi `loop()` untuk menunggu seperti penggunaan `delay()`. Dengan demikian, program tetap dapat menjalankan bagian lain selama proses debounce berlangsung.

Nilai debounce yang umum digunakan berkisar 20–50 milidetik, bergantung pada karakteristik tombol dan kebutuhan aplikasi.

## Kesimpulan

Percobaan ini menunjukkan bahwa Arduino UNO dapat membaca push button untuk mengendalikan LED dengan logika toggle serta menghitung jumlah tekanan tombol. Penerapan software debouncing menggunakan `millis()` membantu mengurangi pembacaan ganda akibat bouncing mekanis. Dengan demikian, perubahan status LED dan nilai counter dapat diproses secara lebih konsisten tanpa menghentikan eksekusi program menggunakan `delay()`.

## Software yang Digunakan

- Arduino IDE atau PlatformIO
- Serial Monitor

