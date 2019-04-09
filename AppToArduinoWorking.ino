  /*
  BLE Module– LED Test
  Hardware 1: MLT-BT05 BLE Bluetooth v4.0
  Hardware 2: Arduino Uno R3
  Experimental Sketch: By T.K.Hareendran
  */
  
  #define indPin 13
  char data = 0;
  #include <SoftwareSerial.h>
  SoftwareSerial BTSerial = SoftwareSerial(10, 11); // RX | TX
  
  void setup()
  {
    BTSerial.begin(9600);
    pinMode(indPin, OUTPUT);
  }
  
  void loop()
  {
    if(BTSerial.available() > 0)
    {
      data = BTSerial.read();
      BTSerial.print("BLE LED TEST...");
      BTSerial.print("\n");
      if (data == '1')
      {
        digitalWrite(indPin, HIGH);
      }
      else if (data == '0')
      {
        digitalWrite(indPin, LOW);
      }
    }
  }
