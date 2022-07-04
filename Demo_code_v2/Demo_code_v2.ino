#include <CapacitiveSensor.h>

byte N = 20;

//Capacitive sensor objects
CapacitiveSensor   CS_1 = CapacitiveSensor(15,16);
CapacitiveSensor   CS_2 = CapacitiveSensor(17,18);
CapacitiveSensor   CS_3 = CapacitiveSensor(19,20);
CapacitiveSensor   CS_4 = CapacitiveSensor(21,22);

// Licking sensor variables
long lick_1;
long lick_2;
long lick_3;
long lick_4;

//Valve variables
int valve_1 = 12;
int valve_2 = 11;
int valve_3 = 10;
int valve_4 = 9;

//Input/output pins

int trig_1 = 1; //IO_pin_1
int trig_2 = 2; //IO_pin_2
int trig_3 = 3; //IO_pin_3
int trig_4 = 4; //IO_pin_4
int lick_1_out = 5; //IO_pin_5
int lick_2_out = 6; //IO_pin_6
int lick_3_out = 7; //IO_pin_7
int lick_4_out = 8; //IO_pin_8

volatile bool state = LOW;
volatile bool state_2 = LOW;
volatile bool state_3 = LOW;
volatile bool state_4 = LOW;

elapsedMillis outputTimer = 0;

int th = 5000;

//Encoder encoder(23,14); // mistake connecting encoder to pin 13 (it has the LED attached)

void setup() 
{
  CS_1.set_CS_AutocaL_Millis(0xFFFFFFFF);
  CS_2.set_CS_AutocaL_Millis(0xFFFFFFFF);
  CS_3.set_CS_AutocaL_Millis(0xFFFFFFFF);
  CS_4.set_CS_AutocaL_Millis(0xFFFFFFFF);

  //Pins to be externally triggered
  //pinMode(trig_1, INPUT_PULLUP); // Teensy LC does not have interrupt capability on pin 1
  pinMode(trig_2, INPUT_PULLUP);
  pinMode(trig_3, INPUT_PULLUP);
  pinMode(trig_4, INPUT_PULLUP);
  
  //Interrupt routines can be used to externally trigger the valves for instance
  //attachInterrupt(digitalPinToInterrupt(trig_1),change, RISING); // Teensy LC does not have interrupt capability on pin 1
  attachInterrupt(digitalPinToInterrupt(trig_2),change_2, RISING);
  attachInterrupt(digitalPinToInterrupt(trig_3),change_3, RISING);
  attachInterrupt(digitalPinToInterrupt(trig_4),change_4, RISING);
  
  // Pins that can be used as a digital oputput
//  pinMode(trig_1, OUTPUT);
//  pinMode(trig_2, OUTPUT);
//  pinMode(trig_3, OUTPUT);
//  pinMode(trig_4, OUTPUT);

  //Valve pins declared as an output
  pinMode(lick_1_out, OUTPUT);
  pinMode(lick_2_out, OUTPUT);
  pinMode(lick_3_out, OUTPUT);
  pinMode(lick_4_out, OUTPUT);

  // Pins that can be used as a digital oputput
  digitalWrite(lick_1_out, LOW);
  digitalWrite(lick_2_out, LOW);
  digitalWrite(lick_3_out, LOW);
  digitalWrite(lick_4_out, LOW);

  //Valve pins declared as an output
  pinMode(valve_1, OUTPUT);
  pinMode(valve_2, OUTPUT);
  pinMode(valve_3, OUTPUT);
  pinMode(valve_4, OUTPUT);
}

void loop() 
{
  //Variable to check the performance of the loop function in us
  //long start = micros();

  //Read all the licking sensors
  lick_1 =  CS_1.capacitiveSensor(N);
  lick_2 =  CS_2.capacitiveSensor(N);
  lick_3 =  CS_3.capacitiveSensor(N);
  lick_4 =  CS_4.capacitiveSensor(N);

  // Actuate the valves, when each of the trig_ pins see a rising edge the state variable changes cand the 
  // vale state also changes
  //digitalWrite(valve_1,state);
  digitalWrite(valve_2,state_2);
  digitalWrite(valve_3,state_3);
  digitalWrite(valve_4,state_4);

  // Convert the licking signal to a digital output for a certain threshold
  if (lick_1 >= th)
    {
      digitalWrite(lick_1_out, HIGH);
    }
  else if (lick_1 < th)
    {
      digitalWrite(lick_1_out, LOW);
    }
    
  if (lick_2 >= th)
    {
      digitalWrite(lick_2_out, HIGH);
    }
  else if (lick_2 < th)
    {
      digitalWrite(lick_2_out, LOW);
    }
    
  if (lick_3 >= th)
    {
      digitalWrite(lick_3_out, HIGH);
    }
  else if (lick_3 < th)
    {
      digitalWrite(lick_3_out, LOW);
    }

  if (lick_4 >= th)
    {
      digitalWrite(lick_4_out, HIGH);
    }
  else if (lick_4 < th)
    {
      digitalWrite(lick_4_out, LOW);
    }

  
  // print position for display
  if (outputTimer > 20)  
  {
    outputTimer = 0;
    //Serial.println(state_4);
    //Serial.println(micros() - start);
  }
  

}

void change()
{
  state = !state;
}

void change_2()
{
  state_2 = !state_2;
}

void change_3()
{
  state_3 = !state_3;
}

void change_4()
{
  state_4 = !state_4;
}
