#include <PubSubClient.h>
#include <DHT.h>
#include <WiFi.h>

#define PIN_LED 17
#define PIN_SENSOR_DHT 27

const char* MQTT_CLIENT_ID = "assignment1sic6";
const char* MQTT_BROKER = "broker.emqx.io";
const char* MQTT_PUBLISH_TOPIC = "/UNI282/Muhammad_Anjas_Ardiansyah/data_sensor";
const char* MQTT_SUBSCRIBE_TOPIC = "/UNI282/Muhammad_Anjas_Ardiansyah/aktuasi_led";
// const char* MQTT_USER = "";
// const char* MQTT_PASSWORD = "";

DHT dht(PIN_SENSOR_DHT, DHT22);
WiFiClient espClient;
PubSubClient client(espClient);

void connectWiFi() {
  Serial.print("Menghubungkan ke WiFi");
  WiFi.begin("Wokwi-GUEST", "");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Terhubung!");
}

void connectMQTT() {
  Serial.print("Menghubungkan ke server MQTT... ");
  while (!client.connected()) {
    if (client.connect(MQTT_CLIENT_ID)) {
      Serial.println("Terhubung!");
      client.subscribe(MQTT_SUBSCRIBE_TOPIC);
    } else {
      Serial.print("Gagal, kode rc=");
      Serial.print(client.state());
      Serial.println(" Mencoba lagi dalam 5 detik...");
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Pesan diterima pada topik ");
  Serial.print(topic);
  Serial.print(": ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  if (strcmp(topic, MQTT_SUBSCRIBE_TOPIC) == 0) {
    if ((char)payload[0] == 'O' && (char)payload[1] == 'N') {
      digitalWrite(PIN_LED, HIGH); 
      Serial.println("LED dinyalakan!");
    } else if ((char)payload[0] == 'O' && (char)payload[1] == 'F' && (char)payload[2] == 'F') {
      digitalWrite(PIN_LED, LOW); 
      Serial.println("LED dimatikan!");
    }
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(PIN_LED, OUTPUT);
  dht.begin();

  connectWiFi();

  client.setServer(MQTT_BROKER, 1883);
  client.setCallback(callback);

  connectMQTT();
}

void loop() {
  if (!client.connected()) {
    connectMQTT();
  }
  client.loop();

  static unsigned long lastPublish = 0;
  if (millis() - lastPublish >= 5000) {  
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    if (!isnan(temperature) && !isnan(humidity)) {
      char message[50];
      snprintf(message, sizeof(message), "{\"suhu\":%.2f,\"kelembapan\":%.2f}", temperature, humidity);
      Serial.print("Publish pesan: ");
      Serial.println(message);
      client.publish(MQTT_PUBLISH_TOPIC, message);
    } else {
      Serial.println("Gagal membaca data dari sensor DHT!");
    }

    lastPublish = millis();
  }
}
