//Libraries
#include "DHT.h"
#include <LiquidCrystal_I2C.h>

//global variables lcd
int lcdColumns = 16;
int lcdRows = 2;
//global variables anemometer
  unsigned long startMillis;  
  unsigned long currentMillis;
int analogPin = A0; // linear Hall analog interface
int analogVal;      // analog readings
int value = 0;
bool pulse = false;
int b = 0;

//definitions
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  

#define DHTPIN 2     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));

    // initialize LCD
  lcd.init();
  // turn on LCD backlight                      
  lcd.backlight();
  dht.begin();

  //  initializing the anemometer
   pinMode(analogPin, INPUT);
   startMillis = millis();
}

void loop() {
//  DHT logic
  // Wait a few seconds between measurements.
  
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

//  Serial.print(F("Humidity: "));
//  Serial.print(h);
//  Serial.print(F("%  Temperature: "));
//  Serial.print(t);
//  Serial.print(F("°C "));
//  Serial.print(f);
//  Serial.print(F("°F  Heat index: "));
//  Serial.print(hic);
//  Serial.print(F("°C "));
//  Serial.print(hif);
//  Serial.println(F("°F"));

// LCD logic
  lcd.setCursor(0, 0);
  lcd.print(F("H:"));
  lcd.print(h);
  lcd.print(F("% T:"));
  lcd.print(t);
  lcd.print(F(" C "));

//  Anemometer logic


  // Read the analog interface
  analogVal = analogRead(analogPin);
  if(analogVal > 24 && analogVal <50 && b == 1) {
  value++;
  b = 0;
  } else if(analogVal > 400) {
  b = 1;
  }
//  Serial.println(analogVal);
//  Counts the pulses
//  Serial.println(value); // print analog value


//  Count pulses per 10 seconds
currentMillis = millis();
float kmh = 0;
float mps = 0;
if(currentMillis - startMillis >= 9999) {
  kmh = (value * 0.52424);
  mps = (kmh / 3.6);
  Serial.print(mps);
  Serial.print(F(" meter per seconde"));

  
  lcd.setCursor(0, 1);
  lcd.print(mps);
  lcd.print("m/s");
  
  startMillis = currentMillis;
  value = 0;
  kmh = 0;
  mps = 0;

}
}
