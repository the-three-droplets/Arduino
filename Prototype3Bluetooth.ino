#include "HX711.h"
#include <SoftwareSerial.h>

#define SERVICE_UUID "00002902-0000-1000-8000-00805f9b34fb"
#define CHARACTERISTIC_UUID_TX "00002902-0000-1000-8000-00805f9b34fc"

const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;
long average = 0;
int count = 0;
int countData = 0;
long zero = 190600;
double weight;
long reading = 0;
long conversion = 50;
int tareCount;

SoftwareSerial BTSerial = SoftwareSerial(10, 11); // RX | TX

HX711 scale;

void setup() {
  Serial.begin(57600);
  BTSerial.begin(9600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
}

void loop() {
  calculate();
  printValue();
  zeroIt();
}

void calculate() {
  if (scale.is_ready()) {
    reading = scale.read();
    if(reading != 0 && reading != -1) {
      average = average + reading;
      countData++;
    }
    count++;
  } 
}

void printValue() {
  if (count == 20) {
    reading = average / countData;
    if(reading != -1) {
   //   Serial.print("Reading: ");
      weight = (reading + zero)/conversion;
  //    Serial.println(reading + zero);
      Serial.print("Weight (g): ");
      Serial.println(weight);
      BTSerial.print(weight);
      BTSerial.print(";");
      tareIf();
    }
    count = 0;
    average = 0;
    countData = 0;
  }
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
  if(weight <= 1) {
    tareCount++;
  } else {
    tareCount = 0;
  }
//  Serial.println(tareCount);
  if(tareCount == 2) {
    zero -= weight * conversion;
    tareCount = 0;
  }
}
