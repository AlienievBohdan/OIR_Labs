const uint8_t LDR_PIN = A0;
const uint8_t LED_PIN = 3;

const int ADC_MIN = 8;
const int ADC_MAX = 1015;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int adc = analogRead(LDR_PIN);
  int limited = constrain(adc, ADC_MIN, ADC_MAX);
  int pwm = map(limited, ADC_MIN, ADC_MAX, 0, 255);
  analogWrite(LED_PIN, pwm);

  Serial.print("ADC:");
  Serial.print(adc);
  Serial.print(",PWM:");
  Serial.println(pwm);
  delay(100);
}
