#include <ThingerESP32.h>
#include <DHT.h>
#include "secrets.h"

const int DHT_PIN = 16;
const int LED1_PIN = 5;
const int LED2_PIN = 4;

DHT dht(DHT_PIN, DHT22);
ThingerESP32 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

float temperature = 0;
float humidity = 0;
int brightness = 0;
unsigned long lastRead = 0;

void setup() {
  Serial.begin(115200);
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  dht.begin();

  thing.add_wifi(SSID, SSID_PASSWORD);
  thing["led1"] << digitalPin(LED1_PIN);
  thing["led2"] << [](pson& in) {
    if (in.is_empty()) {
      in = brightness;
    } else {
      brightness = in;
      analogWrite(LED2_PIN, brightness);
    }
  };
  thing["temperature"] >> outputValue(temperature);
  thing["humidity"] >> outputValue(humidity);
}

void loop() {
  thing.handle();

  if (millis() - lastRead >= 2000) {
    lastRead = millis();
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    if (!isnan(h) && !isnan(t)) {
      humidity = h;
      temperature = t;
      Serial.print("Temperature: ");
      Serial.print(temperature, 1);
      Serial.print(" *C  Humidity: ");
      Serial.print(humidity, 1);
      Serial.println(" %");
    }
  }
}
