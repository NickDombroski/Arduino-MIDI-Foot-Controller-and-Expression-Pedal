/*
  MIDI Foot Switches and Expression Pedal Project

  Designed for use with 3PDT Latching buttons. This is written for 6 buttons, with the 
  5th button also enabling/disabling the expression pedal.
  At 5ms intervals, the Arduino checks the state of each of the buttons and sends a corresponding
  MIDI message if the state of the button has been changed. This means that each button sends the 
  same MIDI signal when turned on and off (this was designed with Ableton in mind). Additionally, 
  the analog input from expression pedal is read and mapped into the range of [0,127] and a CC 
  message is sent if the value has changed from the last interval. 

  Note Messages are sent via Channel 11
  CC Messages are sent on CC#1 (Mod wheel)

  Created by Nicholas Dombroski
  nick.m.dombroski@gmail.com
  Last updated 1-7-2021
*/

// Assign each button to a port. 
const int button1Pin = 2;     
const int button2Pin = 3;
const int button3Pin = 4;
const int button4Pin = 5;
const int button5Pin = 6; //also acts as CC on/off
const int button6Pin = 7;
const int expPin = A0;
const int CCNum = 1;

// Initalize variables for reading the button status
int lastButton1State = 0; 
int lastButton2State = 0;         
int lastButton3State = 0; 
int lastButton4State = 0; 
int lastButton5State = 0; 
int lastButton6State = 0; 
int newButton1State = 0; 
int newButton2State = 0;         
int newButton3State = 0; 
int newButton4State = 0; 
int newButton5State = 0; 
int newButton6State = 0;
//Initialize variables to read expression pedal status
int newExpVal = 0;
int lastExpVal = 0;

void setup() {
  // Initialize each button as input
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  pinMode(button3Pin, INPUT);
  pinMode(button4Pin, INPUT);
  pinMode(button5Pin, INPUT);
  pinMode(button6Pin, INPUT);
  // Set MIDI baud rate:
  Serial.begin(31250);
}

void loop() {
  // PROCESS BUTTONS...
  
  // read the state of the pushbutton value:
  newButton1State = digitalRead(button1Pin);
  newButton2State = digitalRead(button2Pin);
  newButton3State = digitalRead(button3Pin);
  newButton4State = digitalRead(button4Pin);
  newButton5State = digitalRead(button5Pin);
  newButton6State = digitalRead(button6Pin);

  if (newButton1State != lastButton1State) {
    sendNote(0x9A, 0x00, 0x45); //C -1
  }
  if (newButton2State != lastButton2State) {
    sendNote(0x9A, 0x01, 0x45); //C# -1
  }
  if (newButton3State != lastButton3State) {
    sendNote(0x9A, 0x02, 0x45); //D -1
  }
  if (newButton4State != lastButton4State) {
    sendNote(0x9A, 0x03, 0x45); //D# -1
  }
  if (newButton5State != lastButton5State) {
    sendNote(0x9A, 0x04, 0x45); //E -1
  }
  if (newButton6State != lastButton6State) {
    sendNote(0x9A, 0x05, 0x45); //F -1
  }

  lastButton1State = newButton1State;
  lastButton2State = newButton2State;
  lastButton3State = newButton3State;
  lastButton4State = newButton4State;
  lastButton5State = newButton5State;
  lastButton6State = newButton6State;

  //PROCESS EXPRESSION PEDAL...

  newExpVal = analogRead(expPin);
  newExpVal = map(newExpVal, 0, 1023, 0, 127);
  newExpVal = constrain(newExpVal, 0, 127);
  if (newExpVal != lastExpVal && lastButton5State==1) {
      sendCC(newExpVal);
  }
  lastExpVal = newExpVal;
  delay(10);
}


void sendNote(int cmd, int pitch, int velocity) {
  Serial.write(cmd);      // Defines message as "Note on" over specified channel
  Serial.write(pitch);    // Defines pitch
  Serial.write(velocity); // Defines velocity
}


void sendCC(int val) {
  Serial.write(176);      // Defines message as Control Change
  Serial.write(CCNum);    // Defines CC number
  Serial.write(val);      // Defines value
}
