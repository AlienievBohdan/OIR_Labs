const uint8_t CAR_RED    = 12;
const uint8_t CAR_YELLOW = 11;
const uint8_t CAR_GREEN  = 10;
const uint8_t PED_RED    = 9;
const uint8_t PED_GREEN  = 8;
const uint8_t BUTTON     = 7;
const uint8_t BUZZER     = 6;

const int BUTTON_PRESSED = HIGH;

const unsigned long T_REQUEST_DELAY  = 2000;
const unsigned long T_BLINK          = 500;
const uint8_t       BLINK_COUNT      = 3;
const unsigned long T_CAR_YELLOW     = 2000;
const unsigned long T_ALL_RED        = 1000;
const unsigned long T_PED_GREEN      = 8000;
const unsigned long T_CAR_RED_YELLOW = 2000;
const unsigned long T_MIN_CAR_GREEN  = 5000;

const unsigned long BEEP_PERIOD = 500;
const unsigned long BEEP_LEN    = 120;
const unsigned int  FREQ_START  = 400;
const unsigned int  FREQ_END    = 2000;

void setLights(bool carR, bool carY, bool carG, bool pedR, bool pedG) {
  digitalWrite(CAR_RED,    carR ? HIGH : LOW);
  digitalWrite(CAR_YELLOW, carY ? HIGH : LOW);
  digitalWrite(CAR_GREEN,  carG ? HIGH : LOW);
  digitalWrite(PED_RED,    pedR ? HIGH : LOW);
  digitalWrite(PED_GREEN,  pedG ? HIGH : LOW);
}

bool buttonPressed() {
  if (digitalRead(BUTTON) == BUTTON_PRESSED) {
    delay(30);
    return digitalRead(BUTTON) == BUTTON_PRESSED;
  }
  return false;
}

void pedestrianGreenWithSound() {
  const unsigned int steps = T_PED_GREEN / BEEP_PERIOD;
  for (unsigned int i = 0; i < steps; i++) {

    bool pedGreenOn = (i < steps * 3 / 4) || (i % 2 == 0);
    setLights(true, false, false,  false, pedGreenOn);

    unsigned int freq = map(i, 0, steps - 1, FREQ_START, FREQ_END);
    tone(BUZZER, freq, BEEP_LEN);
    delay(BEEP_PERIOD);
  }
  noTone(BUZZER);
}

void runPedestrianCycle() {
  delay(T_REQUEST_DELAY);

  for (uint8_t i = 0; i < BLINK_COUNT; i++) {
    digitalWrite(CAR_GREEN, LOW);
    delay(T_BLINK);
    digitalWrite(CAR_GREEN, HIGH);
    delay(T_BLINK);
  }

  setLights(false, true, false,  true, false);
  delay(T_CAR_YELLOW);

  setLights(true, false, false,  true, false);
  delay(T_ALL_RED);

  pedestrianGreenWithSound();

  setLights(true, false, false,  true, false);
  delay(T_ALL_RED);

  setLights(true, true, false,  true, false);
  delay(T_CAR_RED_YELLOW);

  setLights(false, false, true,  true, false);
  delay(T_MIN_CAR_GREEN);
}

void setup() {
  const uint8_t outs[] = {CAR_RED, CAR_YELLOW, CAR_GREEN, PED_RED, PED_GREEN, BUZZER};
  for (uint8_t i = 0; i < sizeof(outs); i++) {
    pinMode(outs[i], OUTPUT);
  }
  pinMode(BUTTON, INPUT);
  setLights(false, false, true,  true, false);
}

void loop() {

  setLights(false, false, true,  true, false);

  if (buttonPressed()) {
    runPedestrianCycle();
  }
}
