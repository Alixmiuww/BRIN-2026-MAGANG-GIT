# Komunikasi Serial Antar-Arduino UNO Menggunakan SoftwareSerial

## Deskripsi

Studi kasus ini mengimplementasikan komunikasi serial antara dua Arduino UNO, yaitu Arduino 1 sebagai **pengirim (transmitter)** dan Arduino 2 sebagai **penerima (receiver)**.

Arduino 1 membaca input push button menggunakan metode debounce, mengubah status LED setiap kali tombol ditekan, dan menghitung jumlah tekanan tombol. Informasi tersebut ditampilkan melalui Serial Monitor PC pertama sekaligus dikirim ke Arduino 2 menggunakan library `SoftwareSerial`.

Arduino 2 menerima pesan dari Arduino 1 melalui jalur serial tambahan, kemudian meneruskan pesan tersebut ke Serial Monitor PC kedua menggunakan komunikasi serial USB bawaan Arduino.

## Tujuan Percobaan

- Memahami komunikasi serial antara dua mikrokontroler Arduino UNO.
- Mengimplementasikan komunikasi menggunakan library `SoftwareSerial`.
- Memahami perbedaan komunikasi hardware serial dan software serial.
- Menerapkan debounce pada push button untuk menghindari pembacaan ganda.
- Mengendalikan LED berdasarkan input tombol.
- Mengirim dan menerima data secara bersamaan melalui jalur komunikasi yang berbeda.

## Komponen yang Digunakan

| No. | Komponen | Jumlah |
|---:|---|---:|
| 1 | Arduino UNO | 2 buah |
| 2 | Push button | 1 buah |
| 3 | LED | 1 buah |
| 4 | Resistor 220 Ω untuk LED | 1 buah |
| 5 | Resistor 10 kΩ untuk tombol, jika diperlukan | 1 buah |
| 6 | Kabel jumper | Secukupnya |
| 7 | Kabel USB | 2 buah |

## Konfigurasi Pin

### 1. Arduino 1 — Pengirim

| Pin Arduino | Terhubung ke | Fungsi |
|---|---|---|
| D2 | Push button ke GND | Input tombol dengan `INPUT_PULLUP` |
| D8 | Anoda LED melalui resistor 220 Ω | Output kendali LED |
| D10 (RX) | D11 (TX) Arduino 2 | Menerima data dari Arduino 2 |
| D11 (TX) | D10 (RX) Arduino 2 | Mengirim data ke Arduino 2 |
| GND | GND Arduino 2 | Referensi ground bersama |
| USB | PC pertama | Komunikasi Serial Monitor |

### 2. Arduino 2 — Penerima

| Pin Arduino | Terhubung ke | Fungsi |
|---|---|---|
| D10 (RX) | D11 (TX) Arduino 1 | Menerima data dari Arduino 1 |
| D11 (TX) | D10 (RX) Arduino 1 | Jalur pengiriman data balik |
| GND | GND Arduino 1 | Referensi ground bersama |
| USB | PC kedua | Menampilkan data pada Serial Monitor |

**Catatan:** Komunikasi antar-Arduino menggunakan sambungan silang TX ke RX. Dalam studi kasus ini, Arduino 1 mengirim data melalui D11 ke D10 Arduino 2. Jalur D10 Arduino 1 ke D11 Arduino 2 tersedia untuk komunikasi arah sebaliknya, meskipun tidak digunakan oleh program penerima yang diberikan.

Push button menggunakan `INPUT_PULLUP`, sehingga tombol akan terbaca LOW ketika ditekan. Resistor eksternal 10 kΩ tidak diperlukan untuk konfigurasi tombol tersebut.

## Kode Program Arduino 1 — Pengirim

Arduino 1 membaca tombol, menerapkan debounce, mengubah status LED, menghitung jumlah tekanan, dan mengirim informasi melalui Serial USB serta `SoftwareSerial`.

```cpp
#include <Arduino.h>
#include <SoftwareSerial.h>

// Deklarasi pin
const int buttonPin = 2;
const int ledPin = 8;

// SoftwareSerial: RX = D10, TX = D11
SoftwareSerial mySerial(10, 11);

// Variabel status
int ledState = LOW;
int buttonState;
int lastButtonState = HIGH;

// Variabel debounce dan counter
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
int pressCount = 0;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);

  Serial.begin(9600);
  Serial.println("Sistem Siap. Silakan tekan tombol!");

  mySerial.begin(9600);
}

void loop() {
  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == LOW) {
        ledState = !ledState;
        digitalWrite(ledPin, ledState);

        pressCount++;

        // Tampilkan pada PC pertama
        Serial.print("Tombol ditekan! Total: ");
        Serial.print(pressCount);
        Serial.print(" | Status LED: ");
        Serial.println(
          ledState == HIGH ? "MENYALA" : "MATI"
        );

        // Kirim pesan ke Arduino 2
        mySerial.print(
          "Info dari Arduino 1: Tombol ditekan ke-"
        );
        mySerial.print(pressCount);
        mySerial.print(" | LED: ");
        mySerial.println(
          ledState == HIGH ? "NYALA" : "MATI"
        );
      }
    }
  }

  lastButtonState = reading;
}
```

## Kode Program Arduino 2 — Penerima

Arduino 2 menerima karakter dari Arduino 1 menggunakan `SoftwareSerial`, kemudian meneruskannya ke Serial Monitor PC kedua melalui `Serial.write()`.

```cpp
#include <Arduino.h>
#include <SoftwareSerial.h>

// SoftwareSerial: RX = D10, TX = D11
SoftwareSerial mySerial(10, 11);

void setup() {
  // Komunikasi dengan PC kedua
  Serial.begin(9600);

  // Komunikasi dengan Arduino 1
  mySerial.begin(9600);

  Serial.println(
    "Arduino 2 Siap Mendengarkan Pesan dari Arduino 1..."
  );
  Serial.println(
    "--------------------------------------------------"
  );
}

void loop() {
  if (mySerial.available()) {
    Serial.write(mySerial.read());
  }
}
```

## Cara Kerja Sistem

1. Arduino 1 membaca kondisi push button melalui pin D2.
2. Program menggunakan debounce selama 50 ms untuk mengurangi efek bouncing mekanis tombol.
3. Ketika tombol terdeteksi ditekan, status LED pada pin D8 dibalik dari menyala menjadi mati atau sebaliknya.
4. Variabel `pressCount` bertambah satu setiap tekanan tombol yang terdeteksi.
5. Arduino 1 menampilkan jumlah tekanan dan status LED pada Serial Monitor PC pertama.
6. Informasi yang sama dikirim melalui `SoftwareSerial` dengan kecepatan 9600 baud.
7. Arduino 2 menerima data melalui pin D10 dan meneruskannya ke PC kedua melalui koneksi USB.
8. Serial Monitor PC kedua menampilkan pesan yang diterima dari Arduino 1.

## Konfigurasi PlatformIO

Untuk memudahkan proses upload melalui port yang sesuai, tambahkan konfigurasi berikut pada file `platformio.ini` masing-masing proyek:

```ini
upload_port = COM3
```

Ganti `COM3` sesuai dengan port Arduino yang terdeteksi pada komputer. Arduino 1 dan Arduino 2 dapat menggunakan nomor COM yang berbeda.

Pastikan konfigurasi tersebut ditempatkan pada bagian environment yang sesuai di `platformio.ini`.

## Pengujian dan Dokumentasi

### Langkah Pengujian

1. Hubungkan push button dan LED ke Arduino 1 sesuai konfigurasi pin.
2. Hubungkan kedua Arduino melalui jalur TX, RX, dan GND.
3. Upload program pengirim ke Arduino 1.
4. Upload program penerima ke Arduino 2.
5. Buka Serial Monitor masing-masing Arduino dengan baud rate 9600.
6. Tekan push button pada Arduino 1 beberapa kali.
7. Amati perubahan status LED dan jumlah tekanan pada PC pertama.
8. Pastikan pesan yang sama diterima dan ditampilkan pada PC kedua.

### Hasil Pengujian

Berdasarkan dokumentasi percobaan, Serial Monitor Arduino 2 menerima dan menampilkan ulang pesan yang dikirim Arduino 1 setiap kali tombol ditekan.

Pesan mencakup jumlah tekanan tombol dan status LED. Hal ini menunjukkan bahwa jalur komunikasi `SoftwareSerial` antar-Arduino dapat berjalan bersamaan dengan jalur Serial USB menuju PC pada masing-masing Arduino.

## Analisis

Arduino 1 bertindak sebagai pengirim yang mengolah input tombol dan mengirimkan data melalui dua jalur komunikasi. `Serial` digunakan untuk menampilkan informasi pada PC pertama, sedangkan `SoftwareSerial` digunakan untuk komunikasi dengan Arduino 2.

Arduino 2 bertindak sebagai penerima. Data yang masuk melalui `mySerial.read()` diteruskan menggunakan `Serial.write()` agar isi pesan tetap ditampilkan sesuai karakter yang diterima.

Penggunaan baud rate yang sama, yaitu 9600 pada kedua ujung komunikasi, membantu memastikan data dapat diterima dengan benar. Sambungan TX ke RX dan penggunaan GND bersama juga diperlukan agar komunikasi berjalan dengan baik.

## Kesimpulan

Percobaan ini menunjukkan bahwa dua Arduino UNO dapat bertukar informasi menggunakan `SoftwareSerial`, sementara masing-masing tetap berkomunikasi dengan PC melalui USB. Push button berfungsi sebagai pemicu pengiriman data, LED menunjukkan perubahan status, dan counter mencatat jumlah tekanan tombol. Data yang diterima Arduino 2 diteruskan ke Serial Monitor sehingga proses komunikasi dapat diamati secara langsung.

## Library yang Digunakan

- `Arduino.h`
- `SoftwareSerial.h`

## Software yang Digunakan

- Visual Studio Code
- PlatformIO
- Serial Monitor

