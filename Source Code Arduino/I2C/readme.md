# Percobaan Komunikasi I²C pada Arduino UNO

## Deskripsi

Percobaan ini bertujuan untuk memahami prinsip kerja komunikasi **I²C (Inter-Integrated Circuit)** menggunakan Arduino UNO. I²C merupakan protokol komunikasi serial sinkron yang menggunakan dua jalur utama, yaitu SDA (Serial Data Line) dan SCL (Serial Clock Line).

Percobaan meliputi pemindaian alamat I²C, penggunaan beberapa perangkat slave dalam satu bus, serta pengujian pengaruh kecepatan clock terhadap durasi komunikasi.

### 1. Prinsip Kerja I²C

I²C menggunakan komunikasi serial sinkron, yaitu data dikirimkan secara berurutan bit demi bit dan disinkronkan menggunakan sinyal clock pada jalur SCL.

Bus I²C terdiri dari dua jalur utama:

| Jalur | Nama | Fungsi |
|---|---|---|
| SDA | Serial Data Line | Mengirimkan data antarperangkat |
| SCL | Serial Clock Line | Menyediakan sinyal clock untuk sinkronisasi |

Kedua jalur umumnya menggunakan konfigurasi open-drain/open-collector yang membutuhkan pull-up resistor. Perangkat menarik jalur ke kondisi LOW, sedangkan kondisi HIGH diperoleh melalui resistor pull-up.

Nilai resistor pull-up, kapasitansi bus, panjang kabel, dan jumlah perangkat dapat memengaruhi kualitas serta kecepatan komunikasi.

### 2. Master dan Slave

Dalam komunikasi I²C, master bertugas menginisiasi dan mengatur komunikasi, sedangkan slave merespons permintaan berdasarkan alamatnya.

Contoh perangkat yang digunakan dalam percobaan ini:

- **Master:** Arduino UNO.
- **Slave:** Sensor BH1750, sensor BMP280, dan LCD I²C.

Setiap perangkat slave harus memiliki alamat yang sesuai agar master dapat berkomunikasi dengan perangkat yang dituju.

### 3. Proses Komunikasi I²C

1. **Start Condition:** Master memulai komunikasi dengan mengubah SDA menjadi LOW ketika SCL HIGH.
2. **Alamat Slave:** Master mengirimkan alamat perangkat tujuan beserta bit baca/tulis.
3. **Acknowledgment (ACK):** Perangkat yang sesuai memberikan respons ACK.
4. **Transfer Data:** Data dikirimkan antara master dan slave.
5. **Stop Condition:** Master mengakhiri komunikasi melalui kondisi STOP.

ACK menunjukkan bahwa perangkat menerima respons pada tahap komunikasi terkait, sedangkan NACK menunjukkan bahwa acknowledgment tidak diberikan.

## Percobaan 1: Pemindaian Alamat I²C

### Tujuan

Mengetahui alamat perangkat yang terhubung pada bus I²C menggunakan Arduino UNO.

### Komponen

- Arduino UNO
- Modul atau sensor I²C
- Kabel jumper
- Kabel USB

### Konfigurasi Pin

| Pin Perangkat I²C | Arduino UNO | Fungsi |
|---|---|---|
| SDA | SDA / A4 | Jalur data |
| SCL | SCL / A5 | Jalur clock |
| VCC | Sesuai spesifikasi modul | Tegangan sumber |
| GND | GND | Ground |

### Cara Kerja

1. Arduino memulai komunikasi I²C menggunakan `Wire.begin()`.
2. Program memeriksa alamat dari 1 hingga 126.
3. Setiap alamat diuji menggunakan `Wire.beginTransmission()` dan `Wire.endTransmission()`.
4. Jika perangkat memberikan respons ACK, alamat ditampilkan pada Serial Monitor dalam format heksadesimal.
5. Pemindaian diulang setiap 5 detik.

### Hasil dan Analisis

Arduino berfungsi sebagai master yang memindai alamat perangkat pada bus I²C. Ketika nilai `error == 0`, perangkat dianggap memberikan respons ACK terhadap alamat yang diuji.

Alamat yang ditemukan ditampilkan dalam format heksadesimal, misalnya `0x23` atau `0x27`. Variabel `nDevices` digunakan untuk menghitung jumlah perangkat yang terdeteksi.

Jika tidak ada perangkat yang merespons, program menampilkan pesan bahwa perangkat I²C tidak terdeteksi. Kondisi ini dapat menjadi indikasi untuk memeriksa sambungan SDA, SCL, catu daya, dan alamat perangkat.

## Percobaan 2: Penggunaan Beberapa Slave dalam Satu Bus I²C

### Tujuan

Mengidentifikasi dan menggunakan beberapa perangkat slave secara bersamaan pada satu bus I²C.

### Komponen

- Arduino UNO
- 2 sensor BH1750
- 1 sensor BMP280
- 1 LCD I²C 16×2
- Kabel jumper

### Konfigurasi Alamat

| Perangkat | Alamat I²C |
|---|---|
| BH1750 pertama | `0x23` |
| BH1750 kedua | `0x5C` |
| BMP280 | `0x76` |
| LCD I²C | `0x27` |

Alamat di atas merupakan alamat yang digunakan dalam program percobaan. Pastikan alamat aktual setiap modul sesuai dengan hasil pemindaian I²C.

### Cara Kerja

1. Arduino menginisialisasi bus I²C, LCD, dua sensor BH1750, dan sensor BMP280.
2. Kedua BH1750 dikonfigurasi menggunakan alamat yang berbeda.
3. Sensor membaca intensitas cahaya, suhu, dan tekanan udara.
4. LCD menampilkan data secara bergantian dalam dua halaman.
5. Halaman pertama menampilkan data intensitas cahaya dari kedua BH1750.
6. Halaman kedua menampilkan suhu dan tekanan dari BMP280.

### Hasil dan Analisis

Berdasarkan catatan percobaan, beberapa perangkat dapat digunakan pada satu bus I²C dengan menggunakan alamat yang berbeda.

Dua sensor BH1750 dikonfigurasi menggunakan alamat `0x23` dan `0x5C`, sedangkan BMP280 dan LCD menggunakan alamat masing-masing. Perangkat dapat berbagi jalur SDA dan SCL selama alamatnya tidak bertabrakan dan kondisi listrik bus mendukung komunikasi.

**Catatan:** Untuk menggunakan dua sensor dengan tipe yang sama, periksa datasheet dan konfigurasi pin alamat masing-masing modul. Pada BH1750, pin ADDR digunakan untuk memilih alamat I²C alternatif. Pastikan juga inisialisasi setiap perangkat berhasil sebelum mengandalkan data pembacaan.

## Percobaan 3: Pengujian Kecepatan Komunikasi I²C

### Tujuan

Mengamati pengaruh pengaturan kecepatan clock I²C terhadap durasi pembacaan sensor BH1750.

### Komponen

- Arduino UNO
- Sensor BH1750
- Kabel jumper
- Kabel USB


### Cara Kerja

1. Arduino memulai bus I²C dan menginisialisasi sensor BH1750.
2. Kecepatan clock diatur menggunakan `Wire.setClock(400000)`.
3. Fungsi `micros()` mencatat waktu sebelum dan setelah pemanggilan pembacaan sensor.
4. Selisih waktu digunakan untuk menghitung durasi operasi pembacaan.
5. Nilai intensitas cahaya dan durasi ditampilkan pada Serial Monitor.

Untuk membandingkan kecepatan, pengujian dapat diulang dengan pengaturan `Wire.setClock(100000)` dan `Wire.setClock(400000)`.

### Mode Kecepatan I²C

| Mode | Kecepatan maksimum |
|---|---:|
| Standard Mode | 100 kbit/s |
| Fast Mode | 400 kbit/s |
| Fast-mode Plus | 1 Mbit/s |
| High-Speed Mode | 3,4 Mbit/s |

Nilai tersebut merupakan batas maksimum tiap mode, bukan kecepatan yang harus selalu digunakan. Kecepatan aktual dipengaruhi oleh dukungan perangkat, karakteristik bus, resistor pull-up, kapasitansi, dan panjang kabel.

### Hasil dan Analisis

Berdasarkan catatan pengujian, peningkatan nilai pada `Wire.setClock()` diikuti oleh durasi komunikasi yang lebih cepat pada percobaan tersebut. Catatan hasil menyebutkan nilai maksimum pengujian sebesar 880.000, tetapi satuan dan kondisi pengukurannya tidak dijelaskan lebih lanjut.

Durasi yang diukur menggunakan `micros()` merupakan waktu yang berlalu selama pemanggilan fungsi `readLightLevel()`, bukan pengukuran murni kecepatan transfer bit pada bus. Fungsi tersebut dapat mencakup proses perangkat lunak dan penanganan sensor, sehingga hasilnya tidak selalu berbanding lurus dengan perubahan clock I²C.

Untuk memperoleh perbandingan yang lebih akurat, lakukan beberapa pengukuran pada setiap pengaturan clock dengan kondisi perangkat yang sama, kemudian bandingkan durasi rata-ratanya.

## Kesimpulan

Percobaan ini memperlihatkan penggunaan komunikasi I²C pada Arduino UNO untuk memindai alamat perangkat, membaca beberapa sensor dalam satu bus, dan mengamati pengaruh pengaturan clock terhadap durasi pembacaan.

I²C memungkinkan beberapa perangkat berbagi jalur SDA dan SCL dengan menggunakan alamat masing-masing. Keberhasilan komunikasi bergantung pada konfigurasi alamat, koneksi perangkat, dukungan kecepatan, dan karakteristik listrik bus.

## Library yang Digunakan

- `Wire.h`
- `LiquidCrystal_I2C.h`
- `BH1750.h`
- `Adafruit_BMP280.h`

## Software yang Digunakan

- Arduino IDE
- Serial Monitor

