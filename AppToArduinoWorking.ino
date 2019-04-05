  /*
  BLE Module– LED Test
  Hardware 1: MLT-BT05 BLE Bluetooth v4.0
  Hardware 2: Arduino Uno R3
  Experimental Sketch: By T.K.Hareendran
  */
  
  #define indPin 13
  char data = 0;
  
  void setup()
  {
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
  }
