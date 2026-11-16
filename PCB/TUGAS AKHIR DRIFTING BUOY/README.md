# Drifting Buoy – Sistem Manajemen Daya

Dokumentasi ini menjelaskan rancangan skematik dan tata letak PCB **Drifting Buoy** yang ditampilkan pada tangkapan layar KiCad. Rancangan dibagi menjadi beberapa halaman skematik agar rangkaian mikrokontroler, distribusi daya, telemetri/penyimpanan, dan sensor lebih mudah dibaca.

## 1. Ringkasan Rancangan

Papan menggunakan **ESP32-C3-MINI-1-N4** sebagai mikrokontroler utama. Perangkat yang tampak terhubung pada skematik meliputi:

- **SIM800L** untuk komunikasi seluler melalui UART.
- **NEO-M8N** sebagai modul GPS melalui UART.
- **MicroSD adapter** untuk penyimpanan data melalui SPI.
- **DS3231M** sebagai RTC melalui I²C.
- **DS18B20** sebagai sensor suhu melalui jalur 1-Wire.
- **HT7333** sebagai regulator 3,3 V.
- Rangkaian MOSFET untuk mengendalikan jalur catu daya `V_SWITCHED`.

## 2. Struktur Halaman Skematik

| Halaman | Isi utama |
|---|---|
| `MCU_Core` | ESP32-C3, rangkaian EN, konektor UART0, dan pemetaan sinyal antarmodul |
| `Power_Distribution` | Konektor baterai, sakelar utama, pemantauan tegangan baterai, MOSFET, dan regulator 3,3 V |
| `Telemetry_Storage` | SIM800L, GPS NEO-M8N, dan MicroSD adapter |
| `Sensors_RTC` | RTC DS3231M dan sensor suhu DS18B20 |

## 3. Mikrokontroler dan Pemetaan GPIO

Komponen utama pada halaman `MCU_Core` adalah modul **ESP32-C3-MINI-1-N4**. Pin EN dilengkapi resistor pull-up R1 sebesar 10 kΩ ke 3,3 V dan kapasitor C3 sebesar 1 µF ke GND. Jalur I²C memiliki resistor pull-up R8 dan R9 masing-masing 4,7 kΩ.
<img width="1373" height="722" alt="image" src="https://github.com/user-attachments/assets/a1dd1510-0847-432a-acf4-69a90578d349" />

## 4. Sistem Distribusi Daya

<img width="1213" height="768" alt="image" src="https://github.com/user-attachments/assets/423f56c1-aff8-494a-bd2c-f00e36a073e9" />

### 4.1 Masukan baterai dan regulator

Masukan daya berasal dari konektor baterai `J2` dan melewati sakelar utama `SW1` bertipe SPST. Net `V_BAT` menjadi jalur masukan regulator **HT7333**. Regulator menghasilkan jalur `+3.3V` untuk rangkaian yang menggunakan catu 3,3 V.

Kapasitor yang terlihat pada rangkaian regulator:

| Komponen | Nilai | Posisi/fungsi pada skematik |
|---|---:|---|
| C4 | 10 µF | Kapasitor pada sisi masukan HT7333 |
| C5 | 10 µF | Kapasitor pada sisi keluaran HT7333 |

### 4.2 Pemantauan tegangan baterai

Tegangan baterai dipantau melalui pembagi tegangan yang terlihat menggunakan:

- R7: 100 kΩ sebagai resistor sisi atas.
- R10: 100 kΩ sebagai resistor sisi bawah.
- C9: 100 nF pada jalur `VBAT_ADC`.

Titik keluaran pembagi tegangan diberi nama net `VBAT_ADC` dan terhubung ke GPIO3/IO3 ESP32-C3.

### 4.3 Pengendalian jalur daya

Rangkaian kendali daya menggunakan dua MOSFET:

- Q1: **2N7002** sebagai MOSFET kanal-N pada rangkaian pengendali gate.
- Q2: **AO3401A** sebagai MOSFET kanal-P pada jalur daya.

Sinyal `GATE_CTRL` berasal dari ESP32-C3. Resistor R4 dan R5 masing-masing bernilai 10 kΩ. Keluaran rangkaian diberi nama net `V_SWITCHED`.

Pada halaman telemetri, net `V_SWITCHED` terlihat digunakan untuk memasok SIM800L. Di dekat catu SIM800L terdapat kapasitor C6 sebesar 1000 µF dan C7 sebesar 100 nF.

## 5. Telemetri dan Penyimpanan Data

<img width="1338" height="757" alt="image" src="https://github.com/user-attachments/assets/356fa7a8-70ab-459e-9176-b895a27a2c4d" />

### 5.1 SIM800L

Modul SIM800L terhubung ke mikrokontroler menggunakan UART:

| Pin SIM800L | Koneksi |
|---|---|
| VCC | `V_SWITCHED` |
| RXD | `SIM_TX_MCU` |
| TXD | `SIM_RX_MCU` |
| GND | GND |

Kapasitor C6 (1000 µF) dan C7 (100 nF) dipasang pada jalur catu `V_SWITCHED` di sekitar koneksi SIM800L.

### 5.2 GPS NEO-M8N

Modul GPS NEO-M8N pada skematik mendapatkan catu `+3.3V` dan GND. Komunikasi dengan ESP32-C3 menggunakan UART:

| Pin GPS | Koneksi |
|---|---|
| RXD | `GPS_TX_MCU` |
| TXD | `GPS_RX_MCU` |
| VCC | `+3.3V` |
| GND | GND |
| PPS | Tidak digunakan pada skematik yang ditampilkan |

### 5.3 MicroSD adapter

MicroSD adapter mendapatkan catu `+3.3V` dan GND. Jalur komunikasinya menggunakan SPI:

| Sinyal MicroSD | Nama net |
|---|---|
| SCK | `SPI_SCK` |
| MOSI | `SPI_MOSI` |
| MISO | `SPI_MISO` |
| CS | `SD_CS` |

## 6. Sensor dan RTC

<img width="1282" height="797" alt="image" src="https://github.com/user-attachments/assets/38c173a1-dc41-45cf-8d0c-9b31e07ccfcc" />

### 6.1 RTC DS3231M

RTC **DS3231M** terhubung ke ESP32-C3 melalui bus I²C dan mendapatkan catu `+3.3V`.

| Pin DS3231M | Koneksi pada skematik |
|---|---|
| VCC | `+3.3V` |
| GND | GND |
| SDA | `I2C_SDA` |
| SCL | `I2C_SCL` |
| VBAT | Tidak terhubung (NC) |
| 32KHz | Tidak terhubung (NC) |
| INT/SQW | Tidak terhubung (NC) |
| RST | Tidak terhubung (NC) |

Kapasitor C8 sebesar 100 nF terlihat terpasang antara jalur 3,3 V dan GND pada rangkaian RTC.

### 6.2 Sensor suhu DS18B20

Sensor DS18B20 mendapatkan catu `+3.3V` dan GND. Pin data sensor dihubungkan ke net `DS18B_DQ`.

| Pin DS18B20 | Koneksi |
|---|---|
| VDD | `+3.3V` |
| DQ | `DS18B_DQ` |
| GND | GND |

## 7. Tata Letak PCB

<img width="1247" height="782" alt="image" src="https://github.com/user-attachments/assets/520e158c-fcd4-4fc0-bd87-4fe55a84af6f" />

<img width="1331" height="890" alt="image" src="https://github.com/user-attachments/assets/5a613772-e109-41b3-a1e1-447947536585" />

Screenshot PCB memperlihatkan rancangan papan berbentuk lingkaran. Penempatan footprint yang terlihat mencakup area ESP32-C3 di bagian tengah, modul SIM800L di sisi kiri, footprint modul GPS di sisi kanan atas, konektor sensor, area MicroSD, rangkaian catu daya, serta tombol BOOT dan RESET.

Terdapat beberapa lubang pemasangan di area tepi papan. Tampilan editor juga menunjukkan penggunaan layer tembaga depan (`F.Cu`) dan belakang (`B.Cu`). Ukuran fisik, ketebalan PCB, spesifikasi lubang, serta status akhir routing belum dapat ditentukan dari screenshot.

## 8. GERBER FILE
<img width="1050" height="782" alt="image" src="https://github.com/user-attachments/assets/4dce2d57-9620-4fff-a264-c9b31cbc4b65" />

<img width="1158" height="792" alt="image" src="https://github.com/user-attachments/assets/8965352b-b092-45aa-95a5-c66b0620b908" />

