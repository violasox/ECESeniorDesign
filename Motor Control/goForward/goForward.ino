int frontPin = 22;
int backLeftPin= 21;
int backRightPin= 20;
int pwmFreq = 50;
int maxForward = 2400;

void setup() {
    pinMode(frontPin, OUTPUT);
    pinMode(backLeftPin, OUTPUT);
    pinMode(backRightPin, OUTPUT);
     
void loop() {
    digitalWrite(backLeftPin, HIGH);
    delayMicroseconds(maxForward);
    digitalWrite(backLeftPin, LOW);
    digitalWrite(backRightPin, HIGH);
    delayMicroseconds(maxForward);
    digitalWrite(backRightPin, LOW);
    // send new pulses at about 50 Hz
    delay(1000/pwmFreq);
}
