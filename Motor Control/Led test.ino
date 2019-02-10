int redPin =  2;


void setup()   {                
  pinMode(redPin, OUTPUT);
  }

int redIntensity = 0;

void loop()                     
{
  // set all 3 pins to the desired intensity
  analogWrite(redPin, redIntensity);
  
  // remain at this color, but not for very long
  delay(10);
  
  // increase the red
  redIntensity = redIntensity + 1;
  
  // since 255 is the maximum, set it back to 0
  // when it increments beyond 255
  if (redIntensity > 1800) {
    redIntensity = 0;
  }
}
