# Project Integrasi IoT dengan Protokol MQTT (Studi Kasus: Sensor DHT & LED)

## Deskripsi Proyek
Proyek ini merupakan simulasi integrasi Internet of Things (IoT) menggunakan protokol MQTT untuk menghubungkan ESP32 dengan sensor DHT dan LED. Sistem ini memungkinkan:

1. **Publikasi Data Sensor**: Data suhu dan kelembapan dari sensor DHT diterbitkan secara berkala ke broker MQTT.
2. **Kontrol LED melalui MQTT**: LED dapat dihidupkan (ON) atau dimatikan (OFF) dengan mengirimkan pesan ke topik MQTT tertentu.

Simulasi ini dijalankan menggunakan [Wokwi](https://wokwi.com/), platform simulator IoT berbasis web.

---

## Fitur Utama
- **ESP32 sebagai Mikrokomputer**
- **Protokol MQTT** untuk komunikasi perangkat
- **Sensor DHT22** untuk membaca suhu dan kelembapan
- **Kontrol LED** melalui topik MQTT dengan pesan ON/OFF
- **Simulasi di Wokwi** untuk mempermudah pengembangan tanpa perangkat keras fisik

---

## Teknologi yang Digunakan
- **Bahasa Pemrograman**: C++
- **Platform**: Wokwi IoT Simulator
- **Protokol**: MQTT (Broker: `broker.emqx.io`)
- **Hardware Virtual**:
  - ESP32
  - Sensor DHT22
  - LED

---

## Cara Menjalankan Proyek

### 1. Persiapan
1. Buka [Wokwi](https://wokwi.com/projects/new/esp32).
2. Tambahkan komponen berikut ke dalam canvas Wokwi:
   - **ESP32**
   - **DHT22** (hubungkan ke pin D27 ESP32)
   - **LED** (hubungkan ke pin D17 ESP32)

### 2. Masukkan Kode
Salin kode dari file `main.ino` di repository ini ke editor Wokwi.

### 3. Jalankan Simulasi
1. Klik tombol `Play` di Wokwi untuk menjalankan simulasi.
2. Pastikan perangkat ESP32 terhubung ke WiFi simulator (`Wokwi-GUEST`).
3. Pastikan telah mendownload dan menjalankan Wokwi IoT Gateway

### 4. Menguji MQTT
Gunakan **HiveMQ WebSocket Client** atau alat lain untuk menguji:
- **Publish Data Sensor**: Pantau data suhu dan kelembapan di topik:
  ```
  /UNI282/NamaAnda/data_sensor
  ```
- **Kontrol LED**: Kirim pesan ke topik berikut untuk mengontrol LED:
  ```
  /UNI282/NamaAnda/aktuasi_led
  ```
  - Kirim `ON` untuk menyalakan LED.
  - Kirim `OFF` untuk mematikan LED.

---

## Struktur Topik MQTT
| **Topik**                             | **Fungsi**                              |
|---------------------------------------|-----------------------------------------|
| `/UNI282/NamaAnda/data_sensor`        | Publikasi data suhu dan kelembapan      |
| `/UNI282/NamaAnda/aktuasi_led`        | Subscribe untuk kontrol LED (ON/OFF)    |

---

## Contoh Output Serial Monitor
### Saat Terhubung ke WiFi:
```
Menghubungkan ke WiFi... Terhubung!
```

### Saat Terhubung ke MQTT:
```
Menghubungkan ke server MQTT... Terhubung!
```

### Data Sensor Diterbitkan:
```
Publish pesan: {"suhu":25.50,"kelembapan":60.00}
```

### Kontrol LED:
- Saat menerima pesan `ON`:
```
Pesan diterima pada topik /UNI282/NamaAnda/aktuasi_led: ON
LED dinyalakan
```
- Saat menerima pesan `OFF`:
```
Pesan diterima pada topik /UNI282/NamaAnda/aktuasi_led: OFF
LED dimatikan
```

---

## Catatan
- Pastikan broker MQTT yang digunakan mendukung koneksi tanpa autentikasi jika menggunakan `broker.emqx.io`.
- Ganti `NamaAnda` pada topik MQTT sesuai dengan nama atau identitas Anda.

---

## Referensi
- [Wokwi IoT Simulator](https://wokwi.com/)
- [MQTTX APP WebSocket Client](https://mqttx.app/web)
- [MQTT Protocol Documentation](https://mqtt.org/)

---

