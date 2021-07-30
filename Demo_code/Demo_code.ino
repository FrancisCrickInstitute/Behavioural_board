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

int IO_pin_1 = 2;
int IO_pin_2 = 3;
int IO_pin_3 = 23;
int IO_pin_4 = 4;
int IO_pin_5 = 8;
int IO_pin_6 = 7;
int IO_pin_7 = 6;
int IO_pin_8 = 5;

volatile bool state = LOW;
volatile bool state_2 = LOW;
volatile bool state_3 = LOW;
volatile bool state_4 = LOW;

elapsedMillis outputTimer = 0;

int th = 7000;

void setup() 
{
  CS_1.set_CS_AutocaL_Millis(0xFFFFFFFF);
  CS_2.set_CS_AutocaL_Millis(0xFFFFFFFF);
  CS_3.set_CS_AutocaL_Millis(0xFFFFFFFF);
  CS_4.set_CS_AutocaL_Millis(0xFFFFFFFF);

  //Pins to be externally triggered
  //pinMode(IO_pin_1, INPUT_PULLUP);
  //pinMode(IO_pin_2, INPUT_PULLUP);
  //pinMode(IO_pin_3, INPUT_PULLUP);
  //pinMode(IO_pin_4, INPUT_PULLUP);
  
  //Interrupt routines can be used to externally trigger the valves for instance
//  attachInterrupt(digitalPinToInterrupt(IO_pin_1),change, RISING);
//  attachInterrupt(digitalPinToInterrupt(IO_pin_2),change_2, RISING);
//  attachInterrupt(digitalPinToInterrupt(IO_pin_3),change_3, RISING);
//  attachInterrupt(digitalPinToInterrupt(IO_pin_4),change_4, RISING);
  
  // Pins that can be used as a digital oputput
  pinMode(IO_pin_1, OUTPUT);
  pinMode(IO_pin_6, OUTPUT);
  pinMode(IO_pin_7, OUTPUT);
  pinMode(IO_pin_8, OUTPUT);

  digitalWrite(IO_pin_1, LOW);
  digitalWrite(IO_pin_6, LOW);
  digitalWrite(IO_pin_7, LOW);
  digitalWrite(IO_pin_8, LOW);

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

  // Actuate the valves
  digitalWrite(valve_1,state);
  digitalWrite(valve_2,state_2);
  digitalWrite(valve_3,state_3);
  digitalWrite(valve_4,state_4);

  // Convert the licking signal to a digital output for a certain threshold
  if (lick_1 >= th)
    {
      digitalWrite(IO_pin_1, HIGH);
    }
  else if (lick_1 < th)
    {
      digitalWrite(IO_pin_1, LOW);
    }
    
  if (lick_2 >= th)
    {
      digitalWrite(IO_pin_6, HIGH);
    }
  else if (lick_2 < th)
    {
      digitalWrite(IO_pin_6, LOW);
    }
    
  if (lick_3 >= th)
    {
      digitalWrite(IO_pin_7, HIGH);
    }
  else if (lick_3 < th)
    {
      digitalWrite(IO_pin_7, LOW);
    }

  if (lick_4 >= th)
    {
      digitalWrite(IO_pin_8, HIGH);
    }
  else if (lick_4 < th)
    {
      digitalWrite(IO_pin_8, LOW);
    }
  
  // print position for display
  if (outputTimer > 20)  
  {
    outputTimer = 0;
    Serial.println(lick_1);
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
