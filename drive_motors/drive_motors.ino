int motor1Pin = 23;
int pwmFreq = 50;
int forward = 1700;
int maxForward = 2000;
int neutral = 1440;

void setup() {
    pinMode(motor1Pin, OUTPUT);
}

void loop() {
    digitalWrite(motor1Pin, HIGH);
    delayMicroseconds(forward);
    digitalWrite(motor1Pin, LOW);
    delay(20);
}

