#include <Servo.h>

const uint8_t POT_PIN   = A0;
const uint8_t SERVO_PIN = 5;

Servo servo;

void setup() {
  servo.attach(SERVO_PIN);
  Serial.begin(9600);
}

void loop() {
  int adc   = analogRead(POT_PIN);
  int angle = map(adc, 0, 1023, 0, 180);
  servo.write(angle);

  Serial.print("ADC: ");
  Serial.print(adc);
  Serial.print(" | Angle: ");
  Serial.println(angle);
  delay(15);
}
