#include <stdio.h>
#include <string.h>

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
float x_axis=1000;
char* yTranslation;
float y_axis=1000;
char* rot;
float rotation=-10000;
char inData[100];
int stage0 = 0;
int stage1 = 0;
int stage2 = 1;
int stage3 = 0;
int stage4 = 1;
int stage5 = 0;
int stage6 = 1;
int stage7 = 0;
unsigned long start = 0;
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
           }
           count++;
        }
     //stage 1
//     if(stage1 == 1){
//      //rotate clockwise if positive
//      //counterclockwise if negative
//        
//        if(rotation > 100){
//           move(1400,1400,1400); 
//        }
//        else if(rotation<-00){
//            move(1600,1600,1600); //turn around
//        }
//        else{
//          stage1 = 0;
//          stage2 = 1;
//        }
//     }
  if(x_axis > 1000){
      if(stage2 == 1){
      //move right if positive
      //move left if negative
        if(y_axis >10){
          move(1357, 1600, 1600);//move right ok!
        }
        else if( y_axis <= -10){
          move(1627,1400,1400);  //move left
        }
        else{
          stage2 = 0;
          stage3 = 1;
        }
     }

     if(stage3 == 1){
        move(neutral,1600,1393);
     }
  }
  else if(x_axis<=1000 && x_axis > 500){
     if(stage4 == 1){
          if(y_axis >10){
            move(1357, 1600, 1600);//move right ok!
          }
          else if( y_axis <= -10){
            move(1627,1400,1400);  //move left
          }
          else{
            stage4=0;
            stage5=1;
          }
     }
     
     if(stage5 == 1){
        move(neutral,1600,1393);
     }
  }
  else{
    if(stage6 == 1){
          if(y_axis >10){
            move(1357, 1600, 1600);//move right ok!
          }
          else if( y_axis <= -10){
            move(1627,1400,1400);  //move left
          }
          else{
            stage6=0;
            stage7=1;
          }
     }
     
     if(stage7 == 1){
        move(neutral,1600,1393);
     }
  }
}
