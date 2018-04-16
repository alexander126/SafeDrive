#include <SoftwareSerial.h>
#include <stdio.h>

#define no_of_shiftregister 2
#define no_of_shiftpins no_of_shiftregister * 8

boolean registers[no_of_shiftpins];

int datapin = 6; //pin 14 on the shift register
int clockpin = 4; //pin 11 on the shift register
int latchpin = 5; //pin 12 on the shift register
byte shiftdata = 0;
const int mic = A2;
const int threshold = 38;
unsigned long currentime = 0;
unsigned long timer = 0;
int increment = 0;
bool redSwitch = LOW;
bool greenSwitch = LOW;
bool blueSwitch = LOW;

char receivedValue;
String value = "";

SoftwareSerial bluetooth (3, 2);

void setup()
{
  Serial.begin(38400);  

  pinMode(datapin, OUTPUT);
  pinMode(clockpin, OUTPUT);
  pinMode(latchpin, OUTPUT);
  pinMode(mic, INPUT);
 
  bluetooth.begin(38400);

  allOff();
  writeToRegisters();
}


void loop()
{

  int soundDetect = analogRead(mic);
  Serial.println(soundDetect);
  if(bluetooth.available())
  { 
    value = "";
  }
  while(bluetooth.available())
  {   
    receivedValue = ((byte)bluetooth.read());
    if(receivedValue == ':')
    {
      break;
    }
    else
    {
      value += receivedValue;
    }
      delay(1);
  }
  
  if(value == "RED ON")
  {
    //ledOn(HIGH, LOW, LOW, soundDetect);

    redSwitch = HIGH;
  }
  else if(value == "RED OFF")
  {
    redSwitch = LOW;
  }
  else if(value == "GREEN ON")
  {
    //ledOn(LOW, HIGH, LOW, soundDetect);

    greenSwitch = HIGH;
  }
  else if(value == "GREEN OFF")
  {
    greenSwitch = LOW;
  }
  else if(value == "BLUE ON")
  {
    //ledOn(LOW, LOW, HIGH, soundDetect);

    blueSwitch = HIGH;
  }
  else if(value == "BLUE OFF")
  {
    blueSwitch = LOW;
  }
  /*else
  {
    ledOn(LOW, LOW, LOW, soundDetect);
  }*/

  ledOn(redSwitch, greenSwitch, blueSwitch, soundDetect);
}

void ledOn(boolean redOn, boolean greenOn, boolean blueOn, int soundDetect)
{
  if(soundDetect >= threshold)
  {
  
  
  setRegisterPin(2, redOn);
  setRegisterPin(3, greenOn);
  setRegisterPin(4, blueOn);
  
  setRegisterPin(5, redOn);
  setRegisterPin(6, greenOn);
  setRegisterPin(7, blueOn);

  setRegisterPin(0, blueOn); //blue
  setRegisterPin(1, greenOn); //green
  setRegisterPin(9, redOn); //red
  setRegisterPin(8, LOW); //green
  
  setRegisterPin(10, blueOn);
  setRegisterPin(11, greenOn);
  setRegisterPin(12, redOn);
  
  setRegisterPin(13, blueOn);
  setRegisterPin(14, greenOn);
  setRegisterPin(15, redOn);

  writeToRegisters();
  allOff();
  }
  else
  {
  setRegisterPin(0, LOW);
  setRegisterPin(1, LOW);
  
  setRegisterPin(2, LOW);
  setRegisterPin(3, LOW);
  setRegisterPin(4, LOW);
  setRegisterPin(5, LOW);
  setRegisterPin(6, LOW);
  setRegisterPin(7, LOW);

  setRegisterPin(8, LOW);
  setRegisterPin(9, LOW);
  setRegisterPin(10, LOW);
  setRegisterPin(11, LOW);
  setRegisterPin(12, LOW);
  setRegisterPin(13, LOW);

  setRegisterPin(14, LOW);
  setRegisterPin(15, LOW);
  
  writeToRegisters();
  allOff();
  }
}

void writeToRegisters()
{
  digitalWrite(latchpin, LOW);

  for(int i = no_of_shiftpins - 1; i >= 0; i--)
  {
    digitalWrite(clockpin, LOW);

    int val = registers[i];

    digitalWrite(datapin, val);
    digitalWrite(clockpin, HIGH);
  }
  digitalWrite(latchpin, HIGH);
}

void allOff()
{
  for(int i = no_of_shiftpins - 1; i >= 0; i++)
  {
    registers[i] = LOW;
  }

  writeToRegisters();
}

void setRegisterPin(int index, int value)
{
  registers[index] = value;
}

//A function used to write to the shift register
void shiftWrite(int desiredPin, int desiredState)
{
  bitWrite(shiftdata, desiredPin, desiredState);
  shiftOut(datapin, clockpin, MSBFIRST, shiftdata);
  digitalWrite(latchpin, HIGH);
  digitalWrite(latchpin, LOW);
}

