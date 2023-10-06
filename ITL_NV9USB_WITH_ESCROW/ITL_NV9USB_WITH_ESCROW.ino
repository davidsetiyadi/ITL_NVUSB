/*
  SerialPassthrough sketch

  Some boards, like the Arduino 101, the MKR1000, Zero, or the Micro, have one
  hardware serial port attached to Digital pins 0-1, and a separate USB serial
  port attached to the IDE Serial Monitor. This means that the "serial
  passthrough" which is possible with the Arduino UNO (commonly used to interact
  with devices/shields that require configuration via serial AT commands) will
  not work by default.

  This sketch allows you to emulate the serial passthrough behaviour. Any text
  you type in the IDE Serial monitor will be written out to the serial port on
  Digital pins 0 and 1, and vice-versa.

  On the 101, MKR1000, Zero, and Micro, "Serial" refers to the USB Serial port
  attached to the Serial Monitor, and "Serial1" refers to the hardware serial
  port attached to pins 0 and 1. This sketch will emulate Serial passthrough
  using those two Serial ports on the boards mentioned above, but you can change
  these names to connect any two serial ports on a board that has multiple ports.

  created 23 May 2016
  by Erik Nyquist

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/SerialPassthrough
  https://www.youtube.com/watch?v=M2E2yWcKJfc&t=463s #billacceptor-
  https://www.youtube.com/watch?v=M2E2yWcKJfc
  https://kriss-sport.com/dl-files/thirdParty/bv20_operations_manual.pdf
  https://www.youtube.com/watch?v=gegpO70tos8
*/
#define NoteAcceptor Serial3

int credit = 0;
int pushButton = 4;
const int ledPin = 13;    // the number of the LED pin
int incomingByte = 0;   
byte noteInEscrow = 0;
//byte channelValues[] = [5, 10, 20];

void setup() {
  Serial.begin(9600);
  //Serial1.begin(300, SERIAL_8N2);
  pinMode(15, INPUT_PULLUP); //PULL UP SERIAL RX PIN
  pinMode(pushButton, INPUT_PULLUP); 
  NoteAcceptor.begin(300, SERIAL_8N2);
  pinMode(ledPin, OUTPUT);
  NoteAcceptor.write(170);//enable escrow

}

void loop() {
  /*if (Serial.available()) {        // If anything comes in Serial (USB),
    NoteAcceptor.write(Serial.read());  // read it and send it out Serial1 (pins 0 & 1)

     if (Serial.available() > 0) {
      // read the incoming byte:
      incomingByte = Serial.read();

      // say what you got:
      Serial.print("I received: ");
      Serial.println(incomingByte, DEC);
    }

    // if (byteInx == 255){
    //   digitalWrite(ledPin, HIGH);
    //   delay(5000);
    //   digitalWrite(ledPin, LOW);
    // }
  }*/
  int buttonState = digitalRead(pushButton);
  if (buttonState){
  Serial.println(buttonState);
  delay(5000);
  }
  delay(1);
  if (NoteAcceptor.available()) {       // If anything comes in Serial1 (pins 0 & 1)
    
    //Serial.write(Serial1.read());  // read it and send it out Serial (USB)
    byte byteIn = NoteAcceptor.read();
    //Serial.println("**in**");
    
    //Serial.println("****");
    if (byteIn >= 1 && byteIn <= 8){
      Serial.println(byteIn);
      if (noteInEscrow)//if note in escrow > 0
      {
        Serial.println("Escrow Accepted");
        noteInEscrow = 0;
      }else{
        Serial.print("Rp ");
        Serial.print(byteIn);
        noteInEscrow = byteIn;
      }
    }
  
  }
  if (Serial.available()) { 
    byte byteln = Serial.read();
    if (byteln == 'Y'){
      digitalWrite(ledPin, HIGH);
      delay(3000);
      digitalWrite(ledPin, LOW);
      NoteAcceptor.write(172);
    }
    if (byteln == 'N'){
      digitalWrite(ledPin, HIGH);
      delay(500);
      digitalWrite(ledPin, LOW);
      delay(500);
       digitalWrite(ledPin, HIGH);
      delay(500);
      digitalWrite(ledPin, LOW);
      NoteAcceptor.write(173);
    }
  }

}
