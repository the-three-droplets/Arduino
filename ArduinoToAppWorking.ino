  /*Developer: Frederik Hauke
  Important Notices:
      This Arduino-Code is written for Visualizating measurement data from a microcontroller via Bluetooth.
      Before starting this application, the Bluetooth-Modul (HC-05) has to be coupled to the Smartphone.
      In the special case of the HC-05 the default PinCode for initiating the Coupling-Process is "1234".
  Wiring: 
    GND of HC-05 to GND Arduino, VCC of HC-05 to VCC Arduino,
    TX HC-05 to Arduino Pin 10 (RX)
    RX HC-05 to TX Arduino (TX)
   */

  #include "RTClib.h"
  RTC_DS1307 rtc;
  DateTime start;
  long unsigned int startunix;
  
  int sensorPin = A0;
  int sensorValue = 0;
  int timeElapsed = 0;
  #define indPin 13
  char data = 0;
  #include <SoftwareSerial.h>
  SoftwareSerial BTSerial = SoftwareSerial(10, 11); // RX | TX
  bool getData = true;
  
  void setup()
  {
   BTSerial.begin(9600);
   pinMode(indPin, OUTPUT);

   rtc.begin();
   if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running. time will be adjusted");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
   }
   
   rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  
   start = rtc.now();
   startunix = start.unixtime();
  }
  
  void loop()
  { 
    DateTime now = rtc.now();
    
    if (BTSerial.available() > 0)
    {
      data = BTSerial.read();
      BTSerial.print("\n");
      if (data == '1')
      {
        digitalWrite(indPin, HIGH);
      }
      else if (data == '0')
      {
        digitalWrite(indPin, LOW);
      }
      else if (data == '2')
      {
        getData = true;
      }
      else if (data == '3')
      {
        getData = false;
      }
      else if (data == '4')
      {
        startunix = now.unixtime();
      }
    }

    if (getData == true)
    {
      sensorValue = analogRead(sensorPin);
      timeElapsed = now.unixtime() - startunix;
        
      //IMPORTANT: The complete String has to be of the Form: 1234,1234,1234,1234;
      //(every Value has to be separated through a comma (',') and the message has to
      //end with a semicolon (';'))
      
      BTSerial.print(sensorValue);
      BTSerial.print(",");
      BTSerial.print(timeElapsed); 
      BTSerial.print(";");

      delay(1000);
    }
    
  }      
