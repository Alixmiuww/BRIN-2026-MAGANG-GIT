# Dokumentasi Pembelajaran SPI (Serial Peripheral Interface)

## Deskripsi

Percobaan ini mempelajari komunikasi **SPI (Serial Peripheral Interface)** menggunakan Arduino UNO dan Flash Memory W25Q32. Pengujian mencakup pemahaman jalur komunikasi SPI, perbandingan kecepatan transfer pada 1 MHz dan 8 MHz, proses menulis dan membaca data pada memori Flash, serta identifikasi chip melalui pembacaan JEDEC ID.

## Tujuan Pembelajaran

- Memahami prinsip kerja komunikasi SPI dan fungsi jalur MOSI, MISO, SCK, dan CS.
- Mengetahui pengaruh kecepatan clock SPI terhadap waktu transfer data.
- Memahami proses komunikasi antara Arduino UNO dan Flash Memory W25Q32.
- Melakukan operasi hapus, tulis, dan baca data pada memori Flash.
- Mengidentifikasi pabrikan, tipe, dan kapasitas memori melalui JEDEC ID.

## Dasar Teori

SPI merupakan protokol komunikasi serial sinkron yang mendukung komunikasi **full-duplex**, yaitu pengiriman dan penerimaan data secara bersamaan. Komunikasi umumnya menggunakan arsitektur master dan slave, dengan pemilihan perangkat melalui jalur Chip Select (CS).

### Jalur Komunikasi SPI

| Pin | Arah Sinyal | Fungsi |
|---|---|---|
| MOSI | Master → Slave | Mengirim data dari Arduino ke perangkat |
| MISO | Slave → Master | Menerima data dari perangkat ke Arduino |
| SCK / SCLK | Master → Slave | Menyediakan sinyal clock untuk sinkronisasi |
| CS / SS | Master → Slave | Memilih perangkat slave yang akan berkomunikasi |

### Kelebihan SPI

- Mendukung kecepatan transfer data yang tinggi.
- Memungkinkan pengiriman dan penerimaan data secara bersamaan.
- Memiliki mekanisme komunikasi yang relatif sederhana.

### Kekurangan SPI

- Membutuhkan lebih banyak pin dibandingkan I²C.
- Tidak memiliki mekanisme ACK bawaan untuk memastikan penerimaan data.
- Lebih sesuai untuk komunikasi jarak pendek karena kualitas sinyal dapat menurun pada kabel panjang.

## Percobaan 1: Pengujian Kecepatan Transfer SPI

### Tujuan

Membandingkan waktu transfer data pada kecepatan clock SPI sebesar 1 MHz dan 8 MHz.

### Konfigurasi Pin

| Pin Arduino UNO | Pin W25Q32 | Fungsi |
|---|---|---|
| D13 (SCK) | CLK | Jalur clock |
| D11 (MOSI) | DI | Pengiriman data |
| D12 (MISO) | DO | Penerimaan data |
| D10 (CS) | CS | Pemilihan chip |

### Hasil Pengujian

| Kecepatan SPI | Jumlah Data | Waktu Transfer |
|---|---:|---:|
| 1 MHz | 1.000 byte | 9.288 µs |
| 8 MHz | 1.000 byte | 2.232 µs |

### Analisis

Berdasarkan hasil pengujian, peningkatan clock SPI dari 1 MHz menjadi 8 MHz menghasilkan waktu transfer yang lebih singkat, dari 9.288 µs menjadi 2.232 µs.

Secara teoritis, transfer 1.000 byte membutuhkan waktu sekitar 8.000 µs pada 1 MHz dan 1.000 µs pada 8 MHz. Perbedaan dengan hasil pengukuran disebabkan oleh overhead perangkat lunak, pemanggilan fungsi transfer, perulangan program, dan pengendalian pin CS.

Pengujian dijadwalkan setiap tiga detik menggunakan `millis()` sehingga program tidak perlu menggunakan `delay()` untuk mengatur interval pengujian.

## Percobaan 2: Write dan Read Flash Memory W25Q32

### Tujuan

Menguji komunikasi SPI antara Arduino UNO dan memori Flash W25Q32 melalui proses penghapusan sektor, penulisan data, dan pembacaan kembali data.

### Tahapan Pengujian

1. **Write Enable (`0x06`)** — Mengaktifkan izin operasi tulis atau hapus.
2. **Sector Erase (`0x20`)** — Menghapus sektor memori sebesar 4 KB pada alamat yang ditentukan.
3. **Pengecekan Status (`0x05`)** — Memeriksa bit WIP (*Write In Progress*) untuk mengetahui apakah proses masih berlangsung.
4. **Page Program (`0x02`)** — Menulis data berupa karakter `SPI` ke alamat memori.
5. **Read Data (`0x03`)** — Membaca kembali tiga byte data yang telah disimpan.

Alur komunikasi:

`Write Enable → Sector Erase → Tunggu WIP selesai → Write Enable → Page Program → Tunggu WIP selesai → Read Data`

### Hasil dan Analisis

Berdasarkan hasil pengujian, komunikasi SPI dengan memori W25Q32 berhasil dilakukan. Sektor memori berhasil dihapus, data `SPI` berhasil ditulis, dan proses pembacaan menghasilkan kembali data yang sama.

Pengecekan bit WIP diperlukan karena operasi penghapusan dan penulisan Flash membutuhkan waktu untuk diselesaikan. Arduino harus memastikan chip tidak lagi sibuk sebelum menjalankan operasi berikutnya.

## Percobaan 3: Membaca JEDEC ID W25Q32

### Tujuan

Mengidentifikasi memori Flash W25Q32 melalui pembacaan JEDEC ID untuk memastikan komunikasi dasar SPI berjalan dengan baik.

### Dasar Teori

JEDEC ID merupakan identitas yang diberikan oleh chip memori. Informasi ini umumnya terdiri dari tiga byte:

| Byte | Nama | Fungsi |
|---|---|---|
| Byte 1 | Manufacturer ID | Mengidentifikasi pabrikan |
| Byte 2 | Memory Type | Mengidentifikasi jenis atau keluarga memori |
| Byte 3 | Capacity | Mengidentifikasi kapasitas memori |

Pembacaan JEDEC ID menggunakan perintah `0x9F`. Setelah perintah dikirimkan, Arduino membaca tiga byte identitas dari chip.

### Alur Komunikasi

1. Pin CS ditarik LOW untuk memilih chip.
2. Arduino mengirim perintah `0x9F`.
3. Arduino membaca Manufacturer ID.
4. Arduino membaca Memory Type.
5. Arduino membaca Capacity.
6. Pin CS dikembalikan ke HIGH untuk mengakhiri komunikasi.

### Hasil Pengujian

| Parameter | Hasil |
|---|---|
| Manufacturer ID | `0xEF` |
| Memory Type | `0x40` |
| Capacity | `0x16` |

### Analisis

Hasil pembacaan JEDEC ID menunjukkan nilai `EF 40 16`. Manufacturer ID `0xEF` umumnya menunjukkan produsen Winbond, yang memproduksi seri memori W25Q.

Keberhasilan pembacaan JEDEC ID menunjukkan bahwa komunikasi dasar antara Arduino UNO dan chip W25Qxx kemungkinan telah berjalan dengan baik. Pengujian ini dapat dilakukan sebelum menjalankan operasi penyimpanan data seperti erase, write, dan read.

## Kesimpulan

Percobaan SPI menunjukkan bahwa Arduino UNO dapat berkomunikasi dengan Flash Memory W25Q32 untuk menguji kecepatan transfer, menghapus sektor memori, menulis dan membaca data, serta mengidentifikasi chip melalui JEDEC ID.

Peningkatan kecepatan clock dari 1 MHz menjadi 8 MHz memperpendek waktu transfer pada pengujian yang dilakukan. Selain itu, keberhasilan penulisan dan pembacaan data `SPI`, serta pembacaan JEDEC ID `EF 40 16`, menunjukkan bahwa jalur komunikasi SPI berfungsi pada konfigurasi pengujian tersebut.

## Software dan Library

- Arduino IDE / PlatformIO
- `Arduino.h`
- `SPI.h`
- Serial Monitor

