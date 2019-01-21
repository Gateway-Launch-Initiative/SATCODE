int SPKpin = 3; //Needs to be PWM pin for spk/radio output
int Batt1;// Globalize Batt1 Variable
int temp1 = 23;

#include "vars.c"
#include <../avr/wdt.h>
#include "talkie.h"

void setup() {
  pinMode(SPKpin, OUTPUT) ; //this is unecessary for Talkie as it is hardcoded to 3 in Lib
  Serial.begin(9600) ; //serial unnecessary except debugging as needed
  Serial.println("GateSat-01 initializing") ;
  Serial.println("Voice DL code by Eric William") ;
  Serial.println("Initialized") ;
  //Serial.println("") ;
  voice.say(spSTART);//say start to indicate we actually started :)
  voice.say(spSTART);  //repeat because I'm slow
  voice.say(spSTART);  //Repeat and smack user for not listening the first 2 times
  delay (2000);
  }

void loop() {
   //checksensors(); check sensor readings here
    //modeindicator(); add mode indicator LED etc here
  Batt();
  initiateTX();//Initiate the decided form of TX and proceeds to approprite TX void
  }


void initiateTX(){
  voice.say(spREADY);  //Yep
  sayNumber(Batt1);
  voice.say(spVOLTS);
  voice.say(spPROBE);
  //voice.say(spREADY);
  voice.say(spTEMPERATURE);
  sayNumber(temp1);
  voice.say(spDEGREES);
  voice.say(spSTABILISER);
  voice.say(spON); 
  voice.say(spRADIOS);
  voice.say(spMANUAL);
  voice.say(spZONE);
  voice.say(spONE);
  voice.say(spINDICATED);
  voice.say(spALERT);
  voice.say(spZONE);
  voice.say(spTWO);
  voice.say(spNO);
  voice.say(spERROR);
 voice.say(spPROBE);
 voice.say(spTWO);
 voice.say(spPRESSURE);
 voice.say(spINCREASING);
 voice.say(spTWENTY);
 voice.say(spPROBE);
 voice.say(spTHREE);
 voice.say(spCURRENT);
 voice.say(spTOO_LOW);
 voice.say(spZONE);
 voice.say(spFOUR);
 voice.say(spINDICATED);
 voice.say(spTEMPERATURE);
 voice.say(spERROR);
 voice.say(spSPEED);
 sayNumber(1700);
 voice.say(spBREAK);
 
 
 delay(2000);
 
  }


void Batt(){
  Batt1 = analogRead(0) /10;  //correct this later with proper voltage divider code
  Serial.println(Batt1);
    }
void Watchdog(){
  //input Watchdog code here
  }
void Solar(){
  //input Solar Cell monitoring & code here
  }
