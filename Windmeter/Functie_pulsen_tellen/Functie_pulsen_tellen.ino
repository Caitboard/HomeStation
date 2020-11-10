  unsigned long startMillis;  
  unsigned long currentMillis;
int analogPin = A0; // linear Hall analog interface
int analogVal;      // analog readings
int value = 0;
bool pulse = false;
int b = 0;

void setup ()
{
  pinMode(analogPin, INPUT); 
  Serial.begin(9600);

  startMillis = millis();
}

void loop ()
{


  // Read the analog interface
  analogVal = analogRead(analogPin);
  if(analogVal > 24 && analogVal <35 && b == 1) {
  value++;
  b = 0;
  } else if(analogVal > 400) {
  b = 1;
  }
//  Counts the pulses
//  Serial.println(value); // print analog value


//  Count pulses per 10 seconds
currentMillis = millis();
if(currentMillis - startMillis >= 9999) {
  Serial.println(value);
  startMillis = currentMillis;
  value = 0;
}

 
}
