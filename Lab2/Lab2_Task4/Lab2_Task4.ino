const uint8_t LM35_PIN = A0;
const uint8_t RED_PIN  = 12;
const uint8_t BLUE_PIN = 11;

const float TEMP_THRESHOLD = 25.0;

const float ADC_PER_DEGREE = 9.31;

void setup() {
  analogReference(INTERNAL);
  pinMode(RED_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int adc = analogRead(LM35_PIN);
  float tempC = adc / ADC_PER_DEGREE;

  bool hot = tempC > TEMP_THRESHOLD;
  digitalWrite(RED_PIN,  hot ? HIGH : LOW);
  digitalWrite(BLUE_PIN, hot ? LOW : HIGH);

  Serial.print("Temperature = ");
  Serial.print(tempC);
  Serial.print(" *C | ADC = ");
  Serial.print(adc);
  Serial.println(hot ? " | RED" : " | BLUE");
  delay(1000);
}
