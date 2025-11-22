const int PIN_SWITCH = 8;  
const int PIN_V1 = A3;
const int PIN_V2 = A4;
const int PIN_V3 = A5;

const unsigned int N_NORMAL = 1024;
const unsigned int N_OVERSAMPLE = 1024;
const unsigned int OVERSAMPLE = 64;

void setup() {
  Serial.begin(115200);
  delay(200);
  pinMode(PIN_SWITCH, OUTPUT);
  digitalWrite(PIN_SWITCH, LOW);
  Serial.println("READY");
}

void loop() {
  Serial.println("START_NORMAL");

  for (unsigned int i = 0; i < N_NORMAL; i++) {
    unsigned long t0 = millis();

    digitalWrite(PIN_SWITCH, HIGH);
    delayMicroseconds(400);

    (void)analogRead(PIN_V1);
    (void)analogRead(PIN_V2);
    (void)analogRead(PIN_V3);

    int d1 = analogRead(PIN_V1);
    int d2 = analogRead(PIN_V2);
    int d3 = analogRead(PIN_V3);

    digitalWrite(PIN_SWITCH, LOW);

    Serial.print('N'); Serial.print(',');
    Serial.print(d1); Serial.print(',');
    Serial.print(d2); Serial.print(',');
    Serial.println(d3);

    unsigned long dt = millis() - t0;
    if (dt < 20) delay(20 - dt);
  }

  Serial.println("DONE_NORMAL");
  delay(200);
  Serial.println("START_OVERSAMPLE");

  for (unsigned int i = 0; i < N_OVERSAMPLE; i++) {
    unsigned long t0 = millis();

    digitalWrite(PIN_SWITCH, HIGH);
    delayMicroseconds(400);

    (void)analogRead(PIN_V1);
    (void)analogRead(PIN_V2);
    (void)analogRead(PIN_V3);

    unsigned long S1 = 0;
    unsigned long S2 = 0;
    unsigned long S3 = 0;

    for (unsigned int k = 0; k < OVERSAMPLE; k++) {
      S1 += analogRead(PIN_V1);
      S2 += analogRead(PIN_V2);
      S3 += analogRead(PIN_V3);
    }

    digitalWrite(PIN_SWITCH, LOW);

    Serial.print('S'); Serial.print(',');
    Serial.print(S1); Serial.print(',');
    Serial.print(S2); Serial.print(',');
    Serial.println(S3);

    unsigned long dt = millis() - t0;
    if (dt < 20) delay(20 - dt);
  }

  Serial.println("DONE_OVERSAMPLE");

  while (1) delay(1000);
}