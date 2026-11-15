const uint8_t POT_PIN = A0;
const uint8_t LED_PIN = 3;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int adc = analogRead(POT_PIN);
  int pwm = map(adc, 0, 1023, 0, 255);

  Serial.print("ADC: ");
  Serial.print(adc);
  Serial.print(" | PWM: ");
  Serial.println(pwm);

  analogWrite(LED_PIN, pwm);
  delay(10);
}
