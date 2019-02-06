int SPKpin = 3; //Needs to be PWM pin for spk/radio output
int Batt1;// Globalize Batt1 Variable
int batTemp = 39; //test temp for bat temp
int cpuTemp = 43; //test temp for CPU temp
int time; //Time Variable
int Z1ERR=0; //zone one error sector (Top 1U of sat)
int Z2ERR=0; //zone two error sector (Middle 1U of sat)
int Z3ERR=0; //zone three error sector (Lower 1U of Sat)
int abort=0;

#include "voice select.h" //local voice library
#include "talkie.h" //talkie library for voice
#include "Wire.h" //RTClib
#include "RTClib.h"//RTClib
#include "RTCsetup.h"//local RTC setup script

#define PAYLOAD_SIZE 2 // how many bytes to expect from each I2C salve node
#define NODE_MAX 3 // maximum number of slave nodes (I2C addresses) to probe
#define START_NODE 41 // The starting I2C address of slave nodes
#define NODE_READ_DELAY 1000 // Some delay between I2C node reads

int nodePayload[PAYLOAD_SIZE];

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
	case 'a': voice.say(spALPHA);
	case 'b': voice.say(spBRAVO);
	case 'c': voice.SAY(spCHARLIE);
	case 'd': voice.say(spDELTA);
		//will add more once tested.
}


void setup() {
  pinMode(SPKpin, OUTPUT) ; //this is unnecessary for Talkie as it is hard coded to digital pin 3 in Lib
  Serial.begin(9600) ; //serial unnecessary except debugging as needed
  Serial.println("GateSat-01 initializing") ;
  Wire.begin();
  pinMode(A3, OUTPUT);     //*** pin 16 (Analog pin 2) as OUTPUT   ***
  digitalWrite(A3, HIGH);   //*** pin 16 (Analog pin 2) set to LOW  ***
  pinMode(A2, OUTPUT);     //*** pin 17 (Analog pin 3) as OUTPUT   ***
  digitalWrite(A2, LOW);  //*** pin 17 (Analog pin 3) set to HIGH ***
  //*** Analog Pin settings to power RTC module ***
  Serial.println("Voice DL code by Carsten Gallini") ;
  delay(2000);
  Serial.println("GateSat-01 Is the property of the Gateway Cubesat Project");
  delay(2000)
  Serial.println("This is the master read node.");
  delay(1000)
  Serial.print("Maximum Slave Nodes: ");
  Serial.println(NODE_MAX);
  Serial.print("Payload size: ");
  Serial.println(PAYLOAD_SIZE);
  voice.say(spWHAT_IS_THY_BIDDING);
  delay(2000);
  Wire.beginTransmission(41); // transmit to device A
  Wire.write(1);
  Wire.endTransmission();    // stop transmitting
  Wire.beginTransmission(42); // transmit to device B
  Wire.write(1);
  Wire.endTransmission();    // stop transmitting
  Wire.beginTransmission(43); // transmit to device C
  Wire.write(1);
  Wire.endTransmission();    // stop transmitting
  voice.say(spREADY_TO_START);
  Serial.println("Initialized") ;
  //Serial.println("") ;
  voice.say(spSTART);//say start to indicate we actually started
  voice.say(spSTART);
  voice.say(spSTART);
  delay (2000);
  }

void loop() {
  //checksensors(); check sensor readings here
	RTC.readClock();
	Batt();
	TXswitch();//Initiate the decided form of TX and proceeds to appropriate TX void
}

void rtc() {

}

void TXswitch() {
if (abort=1)
{
	initiateTX2();
	Serial.println("WARNING MISSION ABORT!");
} 
else
{
	initiateTX();
}
}

void initiateTX(){
	voice.say(spGOLF);
	voice.say(spALPHA);
	voice.say(spTANGO);
	voice.say(spECHO);
	voice.say(spSIERRA);
	voice.say(spALPHA);
	voice.say(spTANGO);
	voice.say(spONE);
	voice.say(spINFORMATION);
	voice.say(spREADY);
	delay(2000);

	voice.say(spPOWER);
	voice.say(spZONE);
	voice.say(spONE);
	sayNumber(Batt1);
	voice.say(spVOLTS);
		
	voice.say(spTEMPERATURE);
	sayNumber(batTemp); //Bat Temp
	voice.say(spDEGREES);
	voice.say(spCELCIUS);
	voice.say(spBREAK);
	
	voice.say(spCONTROL);
	voice.say(spZONE);
	voice.say(spTEMPERATURE);
	sayNumber(cpuTemp); //CPU temp
	voice.say(spDEGREES);
	voice.say(spCELCIUS);
	voice.say(spBREAK);
		
	voice.say(spRADIOS);
	voice.say(spAUTOMATIC);
	voice.say(spBREAK);
	
	voice.say(spZONE);
	voice.say(spONE);
	if (Z1ERR = 1) {
		voice.say(spINDICATED);
		voice.say(spALERT);
	}
		else {
			voice.say(spNO);
			voice.say(spERROR)	
		}
	delay(1000);
	voice.say(spZONE);
	voice.say(spTWO);
	if (Z2ERR = 1) {
		voice.say(spINDICATED);
		voice.say(spALERT);
	}
		else {
			voice.say(spNO);
			voice.say(spERROR);
			
		}
	delay(1000);
	voice.say(spZONE);
	voice.say(spTHREE);
	if (Z3ERR = 1) {
	  voice.say(spINDICATED);
	  voice.say(spALERT);
	  
	}
		else {
			voice.say(spNO);
			voice.say(spERROR);
			
		}
	voice.say(spBREAK);

	/*voice.say(spPROBE);
	voice.say(spTHREE);
	voice.say(spCURRENT);
	voice.say(spTOO_LOW);
	voice.say(spBREAK);*/

	voice.say(spTHE);
	voice.say(spTIME);
	voice.say(spIS);
	sayNumber(time);
	delay(1000);
	voice.say(spREPEAT);
	voice.say(spREPEAT);
	delay(3000);

  }

void initiateTX2() {
	voice.say(spOPERATOR);
	voice.say(spABORT);
	initiateTX2();
}

void Error_Checks() {
	if (battemp < 60) {
		Z1ERR = 1
	}
	else {
		Z1ERR = 0
	}
	//if (sensor < crit val){
	//    *Zone Number* = 1
	//}
	//else{
	//     *Zone Number* = 0
	//}
}

void Solar(){
  //input Solar Cell monitoring & code here
  }
