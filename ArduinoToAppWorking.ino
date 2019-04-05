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
  
  int sensorPin = A0; 
  int sensorValue = 0;
  #define indPin 13
  char data = 0;
  #include <SoftwareSerial.h>
  SoftwareSerial BTSerial = SoftwareSerial(10, 11); // RX | TX
  
  void setup()
  {
   BTSerial.begin(9600);
   Serial.begin(9600);
   pinMode(indPin, OUTPUT);    
  }
  
  void loop()
  {
    if(Serial.available() > 0)
    {
      data = Serial.read();
      Serial.print("BLE LED TEST...");
      Serial.print("\n");
      if (data == '1')
      {
        digitalWrite(indPin, HIGH);
      }
      else if (data == '0')
      {
        digitalWrite(indPin, LOW);
      }
    }
    
    sensorValue = analogRead(sensorPin);
  
    //IMPORTANT: The complete String has to be of the Form: 1234,1234,1234,1234;
    //(every Value has to be seperated through a comma (',') and the message has to
    //end with a semikolon (';'))
    
    BTSerial.print(sensorValue); 
    BTSerial.print(";");
                  
    //message to the receiving device
       
     delay(1000);  
  }      
