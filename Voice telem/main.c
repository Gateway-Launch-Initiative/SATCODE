int SPKpin = 3; //Needs to be PWM pin for spk/radio output
int Batt1;// Globalize Batt1 Variable
int temp1 = 23; //test temp for bat temp 
int temp2 = 25; //test temp for CPU temp
int time; //Time Variable

#include "vars.c"
#include <avr/wdt.h>
#include "../talkie.h"

/* Say any number between -999,999 and 999,999 */
void sayNumber(long n) {
	if (n < 0) {
		voice.say(spMINUS);
		sayNumber(-n);
	}
	else if (n == 0) {
		voice.say(spZERO);
	}
	else {
		if (n >= 1000) {
			int thousands = n / 1000;
			sayNumber(thousands);
			voice.say(spTHOUSAND);
			n %= 1000;
			if ((n > 0) && (n < 100)) voice.say(spAND);
		}
		if (n >= 100) {
			int hundreds = n / 100;
			sayNumber(hundreds);
			voice.say(spHUNDRED);
			n %= 100;
			if (n > 0) voice.say(spAND);
		}
		if (n > 19) {
			int tens = n / 10;
			switch (tens) {
			case 2: voice.say(spTWENTY); break;
			case 3: voice.say(spTHIR_); voice.say(spT); break;
			case 4: voice.say(spFOUR); voice.say(spT);  break;
			case 5: voice.say(spFIF_);  voice.say(spT); break;
			case 6: voice.say(spSIX);  voice.say(spT); break;
			case 7: voice.say(spSEVEN);  voice.say(spT); break;
			case 8: voice.say(spEIGHT);  voice.say(spT); break;
			case 9: voice.say(spNINE);  voice.say(spT); break;
			}
			n %= 10;
		}
		switch (n) {
		case 1: voice.say(spONE); break;
		case 2: voice.say(spTWO); break;
		case 3: voice.say(spTHREE); break;
		case 4: voice.say(spFOUR); break;
		case 5: voice.say(spFIVE); break;
		case 6: voice.say(spSIX); break;
		case 7: voice.say(spSEVEN); break;
		case 8: voice.say(spEIGHT); break;
		case 9: voice.say(spNINE); break;
		case 10: voice.say(spTEN); break;
		case 11: voice.say(spELEVEN); break;
		case 12: voice.say(spTWELVE); break;
		case 13: voice.say(spTHIR_); voice.say(sp_TEEN); break;
		case 14: voice.say(spFOUR); voice.say(sp_TEEN); break;
		case 15: voice.say(spFIF_); voice.say(sp_TEEN); break;
		case 16: voice.say(spSIX); voice.say(sp_TEEN); break;
		case 17: voice.say(spSEVEN); voice.say(sp_TEEN); break;
		case 18: voice.say(spEIGHT); voice.say(sp_TEEN); break;
		case 19: voice.say(spNINE); voice.say(sp_TEEN); break;
		}
	}
}

//Say any letter from A to Z
void sayLetter() {
	case A: voice.say(spALPHA);
	case B: voice.say(spBRAVO);
	case C: voice.SAY(spCHARLIE);
	case D: voice.say(spDELTA);
		//will add more once tested as I dont think its working as the A,B,C, and D vals arnt highlighting unlike 1234 and 5.

}
#include <../avr/wdt.h>
#include "../talkie.h"

void setup() {
  pinMode(SPKpin, OUTPUT) ; //this is unecessary for Talkie as it is hardcoded to 3 in Lib
  Serial.begin(9600) ; //serial unnecessary except debugging as needed
  Serial.println("GateSat-01 initializing") ;
  Serial.println("Voice DL code by Eric William") ;
  Serial.println("Initialized") ;
  //Serial.println("") ;
  voice.say(spSTART);//say start to indicate we actually started
  voice.say(spSTART);  
  voice.say(spSTART);  
  delay (2000);
  }

void loop() {
   //checksensors(); check sensor readings here
    //modeindicator(); add mode indicator LED etc here
  Batt();
  initiateTX();//Initiate the decided form of TX and proceeds to approprite TX void
  }


void initiateTX(){
  voice.say(spREADY); 
  wdt_reset();
  sayNumber(Batt1);
  wdt_reset();
  voice.say(spVOLTS);
  wdt_reset();
  voice.say(spBREAK);
  wdt_reset();

  voice.say(spTEMPERATURE);
  wdt_reset();
  sayNumber(temp1); //Bat Temp
  wdt_reset();
  voice.say(spDEGREES);
  wdt_reset();
  voice.say(spCELCIUS);
  wdt_reset();
  voice.say(spBREAK);
  wdt_reset();

  voice.say(spTEMPERATURE);
  wdt_reset();
  sayNumber(temp2); //CPU temp
  wdt_reset();
  voice.say(spDEGREES);
  wdt_reset();
  voice.say(spCELCIUS);
  wdt_reset();
  voice.say(spBREAK);


  wdt_reset();
  voice.say(spRADIOS);
  wdt_reset();
  voice.say(spAUTOMATIC);
  wdt_reset();
  voice.say(spBREAK);
  wdt_reset();

  wdt_reset();
  voice.say(spZONE);
  wdt_reset();
  voice.say(spONE);
  wdt_reset();
  voice.say(spINDICATED);
  wdt_reset();
  voice.say(spALERT);
  wdt_reset();
  voice.say(spZONE);
  wdt_reset();
  voice.say(spTWO);
  wdt_reset();
  voice.say(spNO);
  wdt_reset();
  voice.say(spERROR);
  wdt_reset();
  voice.say(spZONE);
  wdt_reset();
  voice.say(spTHREE);
  wdt_reset();
  voice.say(spNO);
  wdt_reset();
  voice.say(spERROR);
  wdt_reset();
  voice.say(spBREAK);

  wdt_reset();
 voice.say(spPROBE);
 wdt_reset();
 voice.say(spTHREE);
 wdt_reset();
 voice.say(spCURRENT);
 wdt_reset();
 voice.say(spTOO_LOW);
 wdt_reset();
 voice.say(spBREAK);

 wdt_reset();
 voice.say(spTIME);
 wdt_reset();
 sayNumber(time);
 wdt_reset();
 voice.say(spREPEAT);
 wdt_reset();
 voice.say(spREPEAT);
 wdt_reset();
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
