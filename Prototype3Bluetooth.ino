#include "HX711.h"
#include <SoftwareSerial.h>

const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;
long average = 0;
int count = 0;
int countData = 0;
long zero = 190600;
double weight;
double newWeight;
long reading = 0;
long conversion = 50;
int tareAtStart = 0;
int stCount;

SoftwareSerial BTSerial = SoftwareSerial(10, 11); // RX | TX

HX711 scale;

void setup() {
  Serial.begin(57600);
  BTSerial.begin(9600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);  
}

void loop() {
  calculate();
  if (count == 10) {
    printValue();
  }
  zeroIt();
  tareIf();
}

void calculate() {
  if (scale.is_ready()) {
    reading = scale.read();
    if(reading != 0 && reading != -1) {
      average = average + reading;
      countData += 1;
    }
    count += 1;
  } 
}

void printValue() {
    reading = average / countData;
    
    if(reading != -1) {
  //  Serial.print("Reading: ");
      newWeight = (reading + zero)/conversion;
      
  //  Serial.println(reading + zero);

      if(newWeight != weight)
      {
        Serial.print("Weight (g): ");
        Serial.println(weight);
   
        String data = String(weight);
        BTSerial.print(data);
        weight = newWeight;

        tareAtStart += 1;
        stCount = 0;
      }
      else if(newWeight == 0)
      {
        Serial.print("Weight (g): ");
   
        String data = String(weight);
        Serial.println(data);
        BTSerial.print(data);
        weight = newWeight;
      }
      
      if(newWeight == weight)
      {
        stCount += 1;
      }
    }
    count = 0;
    average = 0;
    countData = 0;
}

void zeroIt() {
  if (Serial.available())
  {
    char ch = Serial.read();
    if (ch == 't')
    {
      zero -= weight * conversion;
    }
  }
  delay(10);
}

void tareIf() {
  if(tareAtStart == 2)
  {
    zero -= weight * conversion;
    tareAtStart++;
  }
  if(stCount == 10 && abs(weight) < 7)
  {
    zero -= weight * conversion;
    stCount = 0;
  }
}
