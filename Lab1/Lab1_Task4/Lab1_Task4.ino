const uint8_t CAR_RED    = 12;
const uint8_t CAR_YELLOW = 11;
const uint8_t CAR_GREEN  = 10;
const uint8_t PED_RED    = 9;
const uint8_t PED_GREEN  = 8;

const unsigned long T_ALL_RED        = 1000;
const unsigned long T_PED_GREEN      = 5000;
const unsigned long T_CAR_RED_YELLOW = 2000;
const unsigned long T_CAR_GREEN      = 6000;
const unsigned long T_BLINK          = 500;
const uint8_t       BLINK_COUNT      = 3;
const unsigned long T_CAR_YELLOW     = 2000;

void setLights(bool carR, bool carY, bool carG, bool pedR, bool pedG) {
  digitalWrite(CAR_RED,    carR ? HIGH : LOW);
  digitalWrite(CAR_YELLOW, carY ? HIGH : LOW);
  digitalWrite(CAR_GREEN,  carG ? HIGH : LOW);
  digitalWrite(PED_RED,    pedR ? HIGH : LOW);
  digitalWrite(PED_GREEN,  pedG ? HIGH : LOW);
}

void setup() {
  const uint8_t pins[] = {CAR_RED, CAR_YELLOW, CAR_GREEN, PED_RED, PED_GREEN};
  for (uint8_t i = 0; i < sizeof(pins); i++) {
    pinMode(pins[i], OUTPUT);
  }
}

void loop() {

  setLights(true, false, false,  true, false);
  delay(T_ALL_RED);

  setLights(true, false, false,  false, true);
  delay(T_PED_GREEN);

  setLights(true, false, false,  true, false);
  delay(T_ALL_RED);

  setLights(true, true, false,  true, false);
  delay(T_CAR_RED_YELLOW);

  setLights(false, false, true,  true, false);
  delay(T_CAR_GREEN);

  for (uint8_t i = 0; i < BLINK_COUNT; i++) {
    digitalWrite(CAR_GREEN, LOW);
    delay(T_BLINK);
    digitalWrite(CAR_GREEN, HIGH);
    delay(T_BLINK);
  }

  setLights(false, true, false,  true, false);
  delay(T_CAR_YELLOW);

}
