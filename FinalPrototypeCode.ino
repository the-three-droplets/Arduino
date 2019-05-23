#include "HX711.h"
#include <SoftwareSerial.h>
#include "RTClib.h"

RTC_Millis rtc;
DateTime start;
HX711 scale;
long unsigned int startunix;

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
long timeElapsed = 0;
int stCount = 0;

SoftwareSerial BTSerial = SoftwareSerial(10, 11); // RX | TX

void setup() {
  //Serial.begin(57600);
  BTSerial.begin(9600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  
  rtc.begin(DateTime(__DATE__, __TIME__));
  
  start = rtc.now();
  startunix = start.unixtime();
}

void loop() {
  calculate();
  if(count == 10)
  {
    printValue();
  }
  zeroIt();
  tareIf();
}

void calculate() {
  if (scale.is_ready()) {
    reading = scale.read();
    if(reading != 0 && reading != -1) {
      average += reading;
      countData += 1;
      count += 1;
    }
  } 
  delay(10);
}

void printValue() {
    
    if(reading != -1) {
      //Serial.println(zero);
      newWeight = (reading + zero)/conversion;

      DateTime now = rtc.now();
      timeElapsed = now.unixtime() - startunix;
      
      if(newWeight != weight)
      {
        weight = newWeight;
        String data = String(weight);
        String timeData = String(timeElapsed);

        data = data + "," + timeData;

        if(abs(weight) < 500)
        {
        //  Serial.println(data);
          BTSerial.print(data);
        }
        delay(10);

        tareAtStart += 1;
        stCount = 0;
        tareIf();
      }
      else if(newWeight == 0)
      {
        weight = newWeight;

        stCount = 0;
      }
      
      if(newWeight == weight)
      {
        tareAtStart += 1;
        
        if(abs(weight) < 10)
        {
          stCount += 1;
          tareIf();
        }
      }
    }
    count = 0;
    average = 0;
    countData = 0;
}

void zeroIt() {
//  if (Serial.available())
//  {
//    char ch = Serial.read();
//    if (ch == 't')
//    {
//      zero -= weight * conversion;
//    }
//  }
  
  delay(10);
}

void tareIf() {
  if(tareAtStart == 4)
  {
    zero -= weight * conversion;
    tareAtStart++;
  }
  if(stCount == 5)
  {
    zero -= weight * conversion;
    stCount = 0;
  }
}
