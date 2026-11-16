#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>
#include "arduino_secrets.h"

const char DEVICE_LOGIN_NAME[] = SECRET_DEVICE_ID;
const char SSID[] = SECRET_SSID;
const char PASS[] = SECRET_OPTIONAL_PASS;
const char DEVICE_KEY[] = SECRET_DEVICE_KEY;

void onLed1Change();
void onLed2Change();
void onLed3Change();
void onBrightnessChange();

bool led1;
bool led2;
bool led3;
int brightness;
int illuminance;

void initProperties() {
  ArduinoCloud.setBoardId(DEVICE_LOGIN_NAME);
  ArduinoCloud.setSecretDeviceKey(DEVICE_KEY);
  ArduinoCloud.addProperty(led1, READWRITE, ON_CHANGE, onLed1Change);
  ArduinoCloud.addProperty(led2, READWRITE, ON_CHANGE, onLed2Change);
  ArduinoCloud.addProperty(led3, READWRITE, ON_CHANGE, onLed3Change);
  ArduinoCloud.addProperty(brightness, READWRITE, ON_CHANGE, onBrightnessChange);
  ArduinoCloud.addProperty(illuminance, READ, 1 * SECONDS, NULL);
}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);
