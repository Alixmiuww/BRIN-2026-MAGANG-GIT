# Library KiCad (KiCad Library Project)

Repositori ini berisi kumpulan pustaka (library) berupa simbol komponen, *footprint*, dan model 3D untuk desain PCB menggunakan perangkat lunak KiCad. Pustaka di dalam proyek ini terbagi menjadi dua kategori utama: pustaka pihak ketiga (dari luar) dan pustaka buatan sendiri (custom).

## 📦 Pihak Ketiga (External Libraries)

Berikut adalah daftar folder atau komponen yang bersumber dari luar (third-party):

* **`kicad-master`**
* **`kicad_parts-master`**
* **`LED_stuff`**
* **`MAX485`** (Modul transceiver RS-485)
* **`MC00100`** (Modul DC-DC LM2596 Step Down Adjustable Converter)
* **`SIM800L`** (Modul GSM/GPRS)

*Peringatan: Untuk komponen pihak ketiga di atas, hak cipta dan lisensi mengikuti masing-masing pembuat aslinya.*

## 🛠️ Buatan Sendiri (Custom Built)

**Selain daftar komponen pihak ketiga yang disebutkan di atas, seluruh file, simbol, dan footprint lainnya di dalam repositori ini adalah buatan sendiri (custom-made).** 

Ini mencakup berbagai file spesifik proyek seperti:
* Simbol dan footprint modul LoRa (misalnya: `Ai-Thinker Ra-01`, `LORA-RFM96`)
* Simbol kustom lainnya (seperti `dsn.kicad_sym`)
* Modifikasi model 3D terkait (seperti file `.wrl` atau `.step` yang disesuaikan)

## ⚙️ Cara Penggunaan di KiCad

1. Unduh atau *clone* repositori ini ke penyimpanan lokal Anda.
2. Buka **KiCad**.
3. **Menambahkan Simbol:** Pergi ke `Preferences` -> `Manage Symbol Libraries...` lalu tambahkan file `.kicad_sym` yang ada di direktori ini.
4. **Menambahkan Footprint:** Pergi ke `Preferences` -> `Manage Footprint Libraries...` lalu tambahkan folder yang memuat file `.kicad_mod` (atau file `.pretty`).
5. **Model 3D:** Jika footprint buatan sendiri terhubung ke model 3D, pastikan path di pengaturan footprint (*Footprint Properties* -> *3D Settings*) sudah mengarah ke file `.step` atau `.wrl` yang tepat di dalam repositori ini.

---
*Dibuat untuk memudahkan manajemen komponen dalam proyek desain elektronika.*
