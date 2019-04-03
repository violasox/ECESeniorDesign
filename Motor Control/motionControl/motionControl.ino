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

char* xTranslation;
float x_axis=1000;
char* yTranslation;
float y_axis=1000;
char* rot;
float rotation=10000;
char inData[100];
int stage0 = 1;
int stage1 = 0;
int stage2 = 0;
int stage3 = 0;
int stage4 = 0;
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
              Serial.println("Arduino Received: ");
              //Serial.println(inData);

              xTranslation = strtok(inData,",");  
              yTranslation = strtok(NULL,",");          
              rot = strtok(NULL,",");
              
              if(atof(yTranslation)==0 && atof(rot)==0){
                Serial.println("bad data, ignore---");
                break;
              }
          
              x_axis = atof(xTranslation);
              y_axis = atof(yTranslation);
              rotation = atof(rot);
              Serial.print("x_axis: ");
              Serial.println(x_axis);

              Serial.print("y_axis: ");
              Serial.println(y_axis);

              Serial.print("rotation: ");
              Serial.println(rotation);
              Serial.println();
           }
           count++;
        }



     //stage 1
     if(stage0 == 1){
      //rotate clockwise if positive
      //counterclockwise if negative
        
        if(rotation == 10000 ){ 
             move(1700,1700,1700);           
        }
        else{
          stage0 = 0;
          stage1 = 1;
          start = millis();
          Serial.println("exit stage 0 -------------------");
        }
        
     }
     
     //stage 1
     if(stage1 == 1){
      //rotate clockwise if positive
      //counterclockwise if negative
        
        if(rotation > 500){
          start = millis(); 
          move(1400,1400,1400); 
         // Serial.println("runningnnnnnnnnnnn");       
        }
        else if(rotation<-500){
          move(1600,1600,1600); 
          //Serial.println("runningnnnnnnnnnnn"); 
        }
        else{
          stage1 = 0;
          stage2 = 1;
          Serial.println("finish---");
         }
        
     }


      if(stage2 == 1){
      //move right if positive
      //move left if negative
        if(y_axis >= 50){
            move(1375, 1600, 1600);//move in parallel
        }
        else if( y_axis <= -50){
          move(1625,1400,1400); 
        }
        else{
          stage2 = 0;
          stage3 = 1;
        }
     }


     if(stage4 == 1){
        if(x_axis > 400){
          move(neutral,1600,1400);
        }
        else{
          stage1 = 1;
          stage4 = 0;
          x_axis = 0;
          y_axis = 0;
          rotation = 0;
          Serial.println("exit stage 4------------------");
        }
        
     }
    
}
