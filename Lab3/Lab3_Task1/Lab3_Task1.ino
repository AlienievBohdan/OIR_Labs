#include <LiquidCrystal.h>

const int TRIG_PIN = 2;
const int ECHO_PIN = 3;
const int LED_PIN = 5;
const int BUZZER_PIN = 10;

const int LIMIT_1 = 20;
const int LIMIT_2 = 10;

LiquidCrystal lcd(12, 11, 9, 8, 7, 6);

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  lcd.begin(16, 2);
}

long readDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  return duration * 0.034 / 2 + 0.5;
}

void loop() {
  long distance = readDistance();

  lcd.setCursor(0, 0);
  lcd.print("Distance: ");
  lcd.print(distance);
  lcd.print(" cm   ");

  lcd.setCursor(0, 1);
  if (distance < LIMIT_2) {
    lcd.print("WARNING! Close!");
    digitalWrite(LED_PIN, HIGH);
    tone(BUZZER_PIN, 1000);
    delay(100);
  } else if (distance < LIMIT_1) {
    lcd.print("                ");
    digitalWrite(LED_PIN, LOW);
    int pause = map(distance, LIMIT_2, LIMIT_1, 100, 800);
    tone(BUZZER_PIN, 1000, 80);
    delay(pause);
    noTone(BUZZER_PIN);
  } else {
    lcd.print("                ");
    digitalWrite(LED_PIN, LOW);
    noTone(BUZZER_PIN);
    delay(100);
  }
}
