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
  bool getData = true;
  
  void setup()
  {
   BTSerial.begin(9600);
   pinMode(indPin, OUTPUT);    
  }
  
  void loop()
  { 
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
 
    }

    if (getData == true)
    {
      sensorValue = analogRead(sensorPin);
        
      //IMPORTANT: The complete String has to be of the Form: 1234,1234,1234,1234;
      //(every Value has to be seperated through a comma (',') and the message has to
      //end with a semikolon (';'))
      
      BTSerial.print(sensorValue); 
      BTSerial.print(";");

      delay(1000);
    }
    
  }      
