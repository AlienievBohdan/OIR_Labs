#include <WiFi.h>
#include <WebServer.h>
#include <DHT.h>

const int DHT_PIN = 5;
const char* WIFI_SSID = "Wokwi-GUEST";
const char* WIFI_PASSWORD = "";

DHT dht(DHT_PIN, DHT22);
WebServer server(80);

String buildPage(float temperature, float humidity) {
  String page = "<!DOCTYPE html><html><head>";
  page += "<meta charset=\"utf-8\">";
  page += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
  page += "<meta http-equiv=\"refresh\" content=\"3\">";
  page += "<title>ESP32 DHT</title>";
  page += "<style>body{font-family:Helvetica;text-align:center;margin-top:50px;}";
  page += "h1{color:#444444;}p{font-size:24px;color:#444444;}</style>";
  page += "</head><body><div id=\"webpage\">";
  page += "<h1>Температура та вологість</h1>";
  page += "<p>Температура: " + String(temperature, 1) + " &deg;C</p>";
  page += "<p>Вологість: " + String(humidity, 1) + " %</p>";
  page += "</div></body></html>";
  return page;
}

void handleRoot() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  if (isnan(humidity) || isnan(temperature)) {
    server.send(500, "text/plain", "Sensor read error");
    return;
  }
  Serial.print("Request served, T = ");
  Serial.print(temperature, 1);
  Serial.print(" *C, H = ");
  Serial.print(humidity, 1);
  Serial.println(" %");
  server.send(200, "text/html", buildPage(temperature, humidity));
}

void setup() {
  Serial.begin(115200);
  dht.begin();

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD, 6);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  static unsigned long lastRead = 0;
  if (millis() - lastRead >= 2000) {
    lastRead = millis();
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();
    if (!isnan(humidity) && !isnan(temperature)) {
      Serial.print("Temperature: ");
      Serial.print(temperature, 1);
      Serial.print(" *C  Humidity: ");
      Serial.print(humidity, 1);
      Serial.println(" %");
    }
  }
  server.handleClient();
}
