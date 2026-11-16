#include "thingProperties.h"

const int LED1_PIN = 19;
const int LED2_PIN = 18;
const int LED3_PIN = 5;
const int LED4_PIN = 17;
const int LDR_PIN = 34;
const float VIN = 3.3;
const float R = 10000;
const int ADC_MAX = 4095;

unsigned long lastRead = 0;

int conversion(int rawValue) {
  float vout = rawValue * (VIN / ADC_MAX);
  if (vout < 0.01) {
    vout = 0.01;
  }
  if (vout > VIN - 0.01) {
    vout = VIN - 0.01;
  }
  float rLdr = (R * vout) / (VIN - vout);
  return (int)(500 / (rLdr / 1000));
}

void setup() {
  Serial.begin(115200);
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);
  pinMode(LED4_PIN, OUTPUT);
  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();
  if (millis() - lastRead >= 1000) {
    lastRead = millis();
    int rawValue = analogRead(LDR_PIN);
    illuminance = conversion(rawValue);
    Serial.print("Analog reading from sensor = ");
    Serial.println(rawValue);
    Serial.print("Illuminance value = ");
    Serial.print(illuminance);
    Serial.println(" Lux");
  }
}

void onLed1Change() {
  digitalWrite(LED1_PIN, led1);
}

void onLed2Change() {
  digitalWrite(LED2_PIN, led2);
}

void onLed3Change() {
  digitalWrite(LED3_PIN, led3);
}

void onBrightnessChange() {
  analogWrite(LED4_PIN, brightness);
}
