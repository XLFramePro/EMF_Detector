#define NUM_READINGS 15
const uint8_t senseLimit = 15;
const uint8_t antennaPin = 3;
const uint8_t LED[] = {2, 1, 0, 4};

uint16_t total = 0;
uint8_t readings[NUM_READINGS] = {0};
uint8_t index = 0;

void setup() {
  for (uint8_t i = 0; i < 4; i++) {
    pinMode(LED[i], OUTPUT);
    digitalWrite(LED[i], LOW);
  }

  pinMode(antennaPin, INPUT);

  for (uint8_t i = 0; i < 4; i++) {
    digitalWrite(LED[i], HIGH);
    delay(200);
    digitalWrite(LED[i], LOW);
  }
}

void loop() {
  uint16_t val = analogRead(antennaPin);

  if (val >= 1) {
    val = constrain(val, 1, senseLimit);
    val = map(val, 1, senseLimit, 1, 1023);

    total -= readings[index];
    readings[index] = val;
    total += readings[index];
    index = (index + 1) % NUM_READINGS;

    uint16_t average = total / NUM_READINGS;

    digitalWrite(LED[0], average > 50 ? HIGH : LOW);
    digitalWrite(LED[1], average > 350 ? HIGH : LOW);
    digitalWrite(LED[2], average > 750 ? HIGH : LOW);
    digitalWrite(LED[3], average > 950 ? HIGH : LOW);
  }
}
