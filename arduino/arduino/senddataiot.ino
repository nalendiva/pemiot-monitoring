#include <ArduinoJson.h>  // Library untuk JSON
#include <WiFi.h>         // Library WiFi
#include <HTTPClient.h>   // Library HTTP

const char* ssid = "iPhone (2)";       // Ganti dengan SSID WiFi Anda
const char* password = "Takeiteasy09"; // Ganti dengan password WiFi Anda
const char* serverUrl = "172.20.10.4/data"; // URL endpoint Flask

void setup() {
  Serial.begin(115200);
  
  // Hubungkan ke WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    // Simulasi data sensor
    float temperature = random(200, 300) / 10.0;  // Temperatur antara 20.0 dan 30.0
    float humidity = random(300, 700) / 10.0;     // Kelembapan antara 30.0 dan 70.0
    float gasLevel = random(0, 1000) / 10.0;      // Gas antara 0.0 dan 100.0

    // Membuat JSON
    StaticJsonDocument<200> doc;
    doc["temperature"] = temperature;
    doc["humidity"] = humidity;
    doc["gas_level"] = gasLevel;

    String jsonData;
    serializeJson(doc, jsonData);

    // Kirim data ke server
    HTTPClient http;
    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/json");

    int httpResponseCode = http.POST(jsonData);
    if (httpResponseCode > 0) {
      Serial.print("Data sent successfully: ");
      Serial.println(httpResponseCode);
    } else {
      Serial.print("Error sending data: ");
      Serial.println(http.errorToString(httpResponseCode).c_str());
    }
    http.end();

  } else {
    Serial.println("WiFi not connected");
  }

  delay(5000); // Tunggu 5 detik sebelum mengirim data berikutnya
}
