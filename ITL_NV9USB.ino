/*
  Serial Read from ITL NVUSB sketch

  Some boards, like the Arduino 101, the MKR1000, Zero, or the Micro, have one
  hardware serial port attached to Digital pins 0-1, and a separate USB serial
  port attached to the IDE Serial Monitor. This means that the "serial
  passthrough" which is possible with the Arduino UNO (commonly used to interact
  with devices/shields that require configuration via serial AT commands) will
  not work by default.

  This sketch allows you to emulate the serial passthrough behaviour. Any text
  you type in the IDE Serial monitor will be written out to the serial port on
  Digital pins 0 and 1, and vice-versa.


  created 29 Sept 2023
  by David Setiyadi

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/SerialPassthrough
  https://www.youtube.com/watch?v=M2E2yWcKJfc&t=463s #billacceptor-
*/
#define NoteAcceptor Serial3

int credit = 0;

//byte channelValues[] = [5, 10, 20];

void setup() {
  Serial.begin(9600);
  //Serial1.begin(300, SERIAL_8N2);
  pinMode(15, INPUT_PULLUP); //PULL UP SERIAL RX PIN
  NoteAcceptor.begin(300, SERIAL_8N2);

}

void loop() {
  if (Serial.available()) {        // If anything comes in Serial (USB),
    //Serial1.write(Serial.read());  // read it and send it out Serial1 (pins 0 & 1)
  }

  if (NoteAcceptor.available()) {       // If anything comes in Serial1 (pins 0 & 1)
    
    //Serial.write(Serial1.read());  // read it and send it out Serial (USB)
    byte byteIn = NoteAcceptor.read();
    //Serial.println("**in**");
    
    //Serial.println("****");
    if (byteIn >= 1 && byteIn <= 8){
      Serial.println(byteIn);
    }
  
  }
}
