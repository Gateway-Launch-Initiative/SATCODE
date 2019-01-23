void ints{
int SPKpin = 3; //Needs to be PWM pin for spk/radio output
int Batt1;// Globalize Batt1 Variable
int batTemp = 23; //test temp for bat temp
int cpuTemp = 25; //test temp for CPU temp
int time=; //Time Variable
int Z1ERR; //zone one error (Top 1U of sat)
int Z2ERR; //zone two error (Middle 1U of sat)
int Z3ERR; //zone three error (Lower 1U of Sat)
}

#include "voice select.c" //local voice library
#include "talkie.h" //talkie library for voice
//#include <avr/wdt.h> //watch dog timer library (requires Aurdrino Mega board)
#include <Wire.h> //RTClib
#include <RealTimeClockDS1307.h>//RTClib

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
	case a: voice.say(spALPHA);
	case b: voice.say(spBRAVO);
	case c: voice.SAY(spCHARLIE);
	case d: voice.say(spDELTA);
		//will add more once tested as I dont think its working as the A,B,C, and D vals arnt highlighting unlike the numbers.

}


void setup() {
  pinMode(SPKpin, OUTPUT) ; //this is unecessary for Talkie as it is hardcoded to digital pin 3 in Lib
  Serial.begin(9600) ; //serial unnecessary except debugging as needed
  Serial.println("GateSat-01 initializing") ;
  Serial.println("Voice DL code by Carsten Gallini") ;
  delay(2000);
  Serial.println("GateSat-01 Is the property of ");
  delay(2000);
  Serial.println("Initialized") ;
  //Serial.println("") ;
  Wire.begin();
  Serial.begin(9600);
  pinMode(A3, OUTPUT);     //*** pin 16 (Analog pin 2) as OUTPUT   ***
  digitalWrite(A3, HIGH);   //*** pin 16 (Analog pin 2) set to LOW  ***
  pinMode(A2, OUTPUT);     //*** pin 17 (Analog pin 3) as OUTPUT   ***
  digitalWrite(A2, LOW);  //*** pin 17 (Analog pin 3) set to HIGH ***
  //*** Analog Pin settings to power RTC module ***
  voice.say(spSTART);//say start to indicate we actually started
  voice.say(spSTART);
  voice.say(spSTART);
  delay (2000);
  }

void loop() {
  //checksensors(); check sensor readings here
  
  Batt();
  initiateTX();//Initiate the decided form of TX and proceeds to approprite TX void
  }


void initiateTX(){
	voice.say(spGOLF);
	//wdt_reset();
    voice.say(spALPHA);
	//wdt_reset();
	voice.say(spTANGO);
	//wdt_reset();
	voice.say(spECHO);
	//wdt_reset();
	voice.say(spSIERRA);
	//wdt_reset();
	voice.sat(spALPHA);
	//wdt_reset();
	voice.sat(spTANGO);
	//wdt_reset();
	voice.say(spONE)
	//wdt_reset();
	voice.say(spINFORMATION)
	//wdt_reset();
	voice.say(spREADY);
    //wdt_reset();
    voice.sat(spbatt)
    //wdt_reset();
    sayNumber(Batt1);
    //wdt_reset();
    voice.say(spVOLTS);
    //wdt_reset();
    voice.say(spBREAK);
    //wdt_reset();

    voice.say(spTEMPERATURE);
    //wdt_reset();
	sayNumber(batTemp); //Bat Temp
	//wdt_reset();
	voice.say(spDEGREES);
	//wdt_reset();
	voice.say(spCELCIUS);
	//wdt_reset();
	voice.say(spBREAK);
	//wdt_reset();

	voice.say(spTEMPERATURE);
	//wdt_reset();
	sayNumber(cpuTemp); //CPU temp
	//wdt_reset();
	voice.say(spDEGREES);
	//wdt_reset();
	voice.say(spCELCIUS);
	//wdt_reset();
	voice.say(spBREAK);


	//wdt_reset();
	voice.say(spRADIOS);
	//wdt_reset();
	voice.say(spAUTOMATIC);
	//wdt_reset();
	voice.say(spBREAK);
	//wdt_reset();

	voice.say(spZONE);
	//wdt_reset();
	voice.say(spONE);
	//wdt_reset();
	if (Z1ERR = 1) {
		voice.say(spINDICATED);
		//wdt_reset();
		voice.say(spALERT);
		//wdt_reset();
	}
		else {
			voice.say(spNO);
			//wdt_reset();
			voice.say(spERROR)
			//wdt_reset();
		}
	voice.say(spZONE);
	//wdt_reset();
	voice.say(spTWO);
	//wdt_reset();
	if (Z2ERR = 1) {
		voice.say(spINDICATED);
		//wdt_reset();
		voice.say(spALERT);
		//wdt_reset();
	}
		else {
			voice.say(spNO);
			//wdt_reset();
			voice.say(spERROR);
			//wdt_reset();
		}
	voice.say(spZONE);
	//wdt_reset();
	voice.say(spTHREE);
	//wdt_reset();
  if (Z3ERR = 1) {
	  voice.say(spINDICATED);
	  //wdt_reset();
	  voice.say(spALERT);
	  //wdt_reset();
  }
		else {
			voice.say(spNO);
			//wdt_reset();
			voice.say(spERROR);
			//wdt_reset();
		}
	voice.say(spBREAK);

	//wdt_reset();
	voice.say(spPROBE);
	//wdt_reset();
	voice.say(spTHREE);
	//wdt_reset();
	voice.say(spCURRENT);
	//wdt_reset();
	voice.say(spTOO_LOW);
	//wdt_reset();
	voice.say(spBREAK);

	//wdt_reset();
	voice.say(spTIME);
	//wdt_reset();
	sayNumber(time);
	//wdt_reset();
	voice.say(spREPEAT);
	//wdt_reset();
	voice.say(spREPEAT);
	//wdt_reset();
	delay(2000);

  }

  void RTC() {
	  //RealTimeClock RTC;//=new RealTimeClock();

	#define Display_Clock_Every_N_Seconds 10           // n.secs to show date/time
	#define Display_ShortHelp_Every_N_Seconds 60       // n.secs to show hint for help
	//#define TEST_Squarewave
	//#define TEST_StopStart
	//#define TEST_1224Switch

	  int count = 0;
	  char formatted[] = "00-00-00 00:00:00x";

	  void setup() {
		  
	  }

	  void loop() {
		  if (Serial.available())
		  {
			  processCommand();
		  }

		  RTC.readClock();
		  count++;
		  if (count % Display_Clock_Every_N_Seconds == 0) {
}
void Batt(){
  Batt1 = analogRead(0) /10;  //correct this later with proper voltage divider code
  Serial.println(Batt1);
    }

void Watchdog(){
  //wdt_enable(WDTO_8S);
  }

void Solar(){
  //input Solar Cell monitoring & code here
  }
