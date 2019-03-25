int frontPin = 22;
int backLeftPin= 21;
int backRightPin= 20;
int pwmFreq = 50;
int backward = 1200;
int forward = 1700;
int maxForward = 2000;
int neutral = 1500;
int r = 1;
unsigned long time;

void setup() {
    pinMode(frontPin, OUTPUT);
    pinMode(backLeftPin, OUTPUT);
    pinMode(backRightPin, OUTPUT);
    Serial.begin(9600);
}

void front(int speed)
{
    digitalWrite(frontPin, HIGH);
    delayMicroseconds(speed);
    digitalWrite(frontPin, LOW);
}
void back_left_wheel(int speed)
{
    if(speed>1500){
      speed = neutral-(speed-neutral);
    }
    digitalWrite(backLeftPin, HIGH);
    delayMicroseconds(speed);
    digitalWrite(backLeftPin, LOW); 
  
}

void back_right_wheel(int speed)
{
    
    digitalWrite(backRightPin, HIGH);
    delayMicroseconds(speed);
    digitalWrite(backRightPin, LOW);
}

void move(int speed, int speed2, int speed3){
  front(speed);
  back_left_wheel(speed2);
  back_right_wheel(speed3);
}

//void parrallel_move(int speed, int speed2, int speed3){
//  front(
//}


void loop() {
    time = millis();
    while((millis()-time)<2000){
      move(neutral,1800,1800);
    }
     time=millis();
    while((millis()-time)<2000){ 
      move(1700,1800,1200); //moveforward
    }
    //move(neutral,1700,1300);
    delay(2);
    
}
