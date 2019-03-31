#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int frontPin = 22;
int backLeftPin= 21;
int backRightPin= 20;
int pwmFreq = 50;
int backward = 1200;
int forward = 1700;
int maxForward = 2000;
int neutral = 1500;
unsigned long time;

void setup() {
    pinMode(frontPin, OUTPUT);
    pinMode(backLeftPin, OUTPUT);
    pinMode(backRightPin, OUTPUT);
    Serial.begin(9600);
}

void front(int speed1)
{
    digitalWrite(frontPin, HIGH);
    delayMicroseconds(speed1);
    digitalWrite(frontPin, LOW);
}
void back_left_wheel(int speed1)
{
    //speed1 = neutral-(speed1-neutral);
    digitalWrite(backLeftPin, HIGH);
    delayMicroseconds(speed1);
    digitalWrite(backLeftPin, LOW); 
}

void back_right_wheel(int speed1)
{
    
    digitalWrite(backRightPin, HIGH);
    delayMicroseconds(speed1);
    digitalWrite(backRightPin, LOW);
}

void move(int speed1, int speed2, int speed3){
  front(speed1);
  back_left_wheel(speed2);
  back_right_wheel(speed3);
}

//void parrallel_move(int speed, int speed2, int speed3){
//  front(
//}
char str[100] = {0};
char* xTranslation;
float x_axis;
char* yTranslation;
float y_axis;
char* rot;
float rotation;
char inData[100];

void loop() {
  int count =0;
        while (Serial.available() > 0)
        {
          char recieved = Serial.read();
          inData[count] = recieved; 
  
          // Process message when new line character is recieved
          if (recieved == '\n')
          {
              Serial.print("Arduino Received: ");
              Serial.print(inData);
              
           xTranslation = strtok(inData,",");
           x_axis = atof(xTranslation);
           yTranslation = strtok(NULL,",");
           y_axis = atof(yTranslation);
           rot = strtok(NULL,",");
           rotation = atof(rot);
           
           Serial.println(x_axis);
           Serial.println(y_axis);
           Serial.println(rotation);
           break;
           }
           count++;
        }
       
     
//     time = millis();  
//     while((millis()-time)<2000){
//      //move(1375,1600,1600); //move in parallel
//      move(1400,1590,1590);    
//    }
//    delay(1000);
//     
//    time = millis();
//    while((millis()-time)<2000){
//      move(neutral,1400,1600); //go forward
//    }
//    time = millis();
//    while((millis()-time)<2000){
//      move(neutral,1200,1800); //go forward
//    }
//     time=millis();
//    while((millis()-time)<2000){ 
//      move(1800,1800,1800); //turn around
//    }
    
//     time=millis();
//    while((millis()-time)<2000){ 
//      move(1200,1200,1800); //move parallel
//    }
//    time=millis();
//    while((millis()-time)<2000){ 
//    move(neutral,1800,1200); //go backward
//    }
    delay(2);
    
}
