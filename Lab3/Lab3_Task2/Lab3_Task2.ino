#include <LiquidCrystal.h>
#include <DHT.h>

const int DHT_PIN = 4;
const int RED_LED_PIN = 5;
const int BLUE_LED_PIN = 10;

const float TEMP_LIMIT = 25.0;
const float HUM_LIMIT = 50.0;

DHT dht(DHT_PIN, DHT22);
LiquidCrystal lcd(12, 11, 9, 8, 7, 6);

void setup() {
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);
  lcd.begin(16, 2);
  dht.begin();
}

void loop() {
  delay(2000);

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    lcd.clear();
    lcd.print("Read error");
    return;
  }

  bool tempHigh = temperature > TEMP_LIMIT;
  bool humHigh = humidity > HUM_LIMIT;

  digitalWrite(RED_LED_PIN, tempHigh);
  digitalWrite(BLUE_LED_PIN, humHigh);

  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temperature, 1);
  lcd.print("C ");
  lcd.print(tempHigh ? "T HIGH! " : "        ");

  lcd.setCursor(0, 1);
  lcd.print("H:");
  lcd.print(humidity, 1);
  lcd.print("% ");
  lcd.print(humHigh ? "H HIGH! " : "        ");
}
