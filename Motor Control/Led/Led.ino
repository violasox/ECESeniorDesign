int redPin =  2;
int r=0;

void setup()   {                
  pinMode(redPin, OUTPUT);
  Serial.begin(9600);
  }

int redIntensity = 0;

void loop()                     
{
  // set all 3 pins to the desired intensity
  analogWrite(redPin, redIntensity);
  
  // remain at this color, but not for very long
  delay(10);
  
  if(Serial.available()){         //From RPi to Arduino
    r =Serial.read();  //conveting the value of chars to integer
  }
  // increase the red
  redIntensity = r;
  
  // since 255 is the maximum, set it back to 0
  // when it increments beyond 255
  if (redIntensity > 255) {
    redIntensity = 0;
  }
}
