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
	RTC.readClock();
	Batt();
	initiateTX();//Initiate the decided form of TX and proceeds to approprite TX void
}


void initiateTX(){
	voice.say(spGOLF);
	voice.say(spALPHA);
	voice.say(spTANGO);
	voice.say(spECHO);
	voice.say(spSIERRA);
	voice.sat(spALPHA);
	voice.sat(spTANGO);
	voice.say(spONE)
	voice.say(spINFORMATION)
	voice.say(spREADY);
    voice.sat(spbatt)
    sayNumber(Batt1);
    voice.say(spVOLTS);
    voice.say(spBREAK);
    
	voice.say(spTEMPERATURE);
    sayNumber(batTemp); //Bat Temp
	voice.say(spDEGREES);
	voice.say(spCELCIUS);
	voice.say(spBREAK);
	
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

	voice.say(spPROBE);
	voice.say(spTHREE);
	voice.say(spCURRENT);
	voice.say(spTOO_LOW);
	voice.say(spBREAK);

	voice.say(spTIME);
	sayNumber(time);
	voice.say(spREPEAT);
	voice.say(spREPEAT);
	delay(2000);

  }

  void RTCsetup() {
	  //RealTimeClock RTC;//=new RealTimeClock();

	#define Display_Clock_Every_N_Seconds 10           // n.secs to show date/time
	#define Display_ShortHelp_Every_N_Seconds 60       // n.secs to show hint for help
	//#define TEST_Squarewave
	//#define TEST_StopStart
	//#define TEST_1224Switch

	  int count = 0;
	  char formatted[] = "00-00-00 00:00:00x";

	  
		  if (Serial.available())
		  {
			  processCommand();
		  }

		  RTC.readClock();
		  count++;
		  if (count % Display_Clock_Every_N_Seconds == 0) {
		  }
		  void Batt() {
			  Batt1 = analogRead(0) / 10;  //correct this later with proper voltage divider code
			  Serial.println(Batt1);
		  }

		  void RTCclock() {
			  if (Serial.available())
			  {
				  processCommand();
			  }

			  RTC.readClock();
			  count++;
			  if (count % Display_Clock_Every_N_Seconds == 0) {
				  Serial.print(count);
				  Serial.print(": ");
				  RTC.getFormatted(formatted);
				  Serial.print(formatted);
				  Serial.println();
			  }

			  if (count % Display_ShortHelp_Every_N_Seconds == 0) {
				  Serial.println("Send ? for a list of commands.");
			  }
				#ifdef TEST_Squarewave
			  if (count % 10 == 0)
			  {
				  switch (count / 10 % 6)
				  {
				  case 0:
					  Serial.print("Squarewave disabled (low impedance): ");
					  RTC.sqwDisable(0);
					  Serial.println((int)RTC.readData(7));
					  break;
				  case 1:
					  Serial.print("Squarewave disabled (high impedance): ");
					  RTC.sqwDisable(1);
					  Serial.println((int)RTC.readData(7));
					  break;
				  case 2:
					  Serial.println("Squarewave enabled at 1 Hz");
					  RTC.sqwEnable(RTC.SQW_1Hz);
					  break;
				  case 3:
					  Serial.println("Squarewave enabled at 4.096 kHz");
					  RTC.sqwEnable(RTC.SQW_4kHz);
					  break;
				  case 4:
					  Serial.println("Squarewave enabled at 8.192 kHz");
					  RTC.sqwEnable(RTC.SQW_8kHz);
					  break;
				  case 5:
					  Serial.println("Squarewave enabled at 32.768 kHz");
					  RTC.sqwEnable(RTC.SQW_32kHz);
					  break;
				  default:
					  Serial.println("Squarewave test not defined");
				  }//switch
			  }
				#endif

				#ifdef TEST_StopStart
			  if (count % 10 == 0)
			  {
				  if (!RTC.isStopped())
				  {
					  if (RTC.getSeconds() < 45)
					  {
						  Serial.println("Stopping clock for 10 seconds");
						  RTC.stop();
					  }//if we have enough time
				  }
				  else {
					  RTC.setSeconds(RTC.getSeconds() + 11);
					  RTC.start();
					  Serial.println("Adding 11 seconds and restarting clock");
				  }
			  }//if on a multiple of 10 counts
				#endif

			#ifdef TEST_1224Switch  
			  if (count % 10 == 0)
			  {
				  if (count % 20 == 0)
				  {
					  Serial.println("switching to 12-hour time");
					  RTC.switchTo12h();
					  RTC.setClock();
				  }
				  else
				  {
					  Serial.println("switching to 24-hour time");
					  RTC.switchTo24h();
					  RTC.setClock();
				  }
			  }
			#endif
		  }

		  void processCommand() {
			  if (!Serial.available()) { return; }
			  char command = Serial.read();
			  int in, in2;
			  switch (command)
			  {
			  case 'H':
			  case 'h':
				  in = SerialReadPosInt();
				  RTC.setHours(in);
				  RTC.setClock();
				  Serial.print("Setting hours to ");
				  Serial.println(in);
				  break;
			  case 'I':
			  case 'i':
				  in = SerialReadPosInt();
				  RTC.setMinutes(in);
				  RTC.setClock();
				  Serial.print("Setting minutes to ");
				  Serial.println(in);
				  break;
			  case 'S':
			  case 's':
				  in = SerialReadPosInt();
				  RTC.setSeconds(in);
				  RTC.setClock();
				  Serial.print("Setting seconds to ");
				  Serial.println(in);
				  break;
			  case 'Y':
			  case 'y':
				  in = SerialReadPosInt();
				  RTC.setYear(in);
				  RTC.setClock();
				  Serial.print("Setting year to ");
				  Serial.println(in);
				  break;
			  case 'M':
			  case 'm':
				  in = SerialReadPosInt();
				  RTC.setMonth(in);
				  RTC.setClock();
				  Serial.print("Setting month to ");
				  Serial.println(in);
				  break;
			  case 'D':
			  case 'd':
				  in = SerialReadPosInt();
				  RTC.setDate(in);
				  RTC.setClock();
				  Serial.print("Setting date to ");
				  Serial.println(in);
				  break;
			  case 'W':
				  Serial.print("Day of week is ");
				  Serial.println((int)RTC.getDayOfWeek());
				  break;
			  case 'w':
				  in = SerialReadPosInt();
				  RTC.setDayOfWeek(in);
				  RTC.setClock();
				  Serial.print("Setting day of week to ");
				  Serial.println(in);
				  break;

			  case 't':
			  case 'T':
				  if (RTC.is12hour()) {
					  RTC.switchTo24h();
					  Serial.println("Switching to 24-hour clock.");
				  }
				  else {
					  RTC.switchTo12h();
					  Serial.println("Switching to 12-hour clock.");
				  }
				  RTC.setClock();
				  break;

			  case 'A':
			  case 'a':
				  if (RTC.is12hour()) {
					  RTC.setAM();
					  RTC.setClock();
					  Serial.println("Set AM.");
				  }
				  else {
					  Serial.println("(Set hours only in 24-hour mode.)");
				  }
				  break;

			  case 'P':
			  case 'p':
				  if (RTC.is12hour()) {
					  RTC.setPM();
					  RTC.setClock();
					  Serial.println("Set PM.");
				  }
				  else {
					  Serial.println("(Set hours only in 24-hour mode.)");
				  }
				  break;

			  case 'q':
				  RTC.sqwEnable(RTC.SQW_1Hz);
				  Serial.println("Square wave output set to 1Hz");
				  break;
			  case 'Q':
				  RTC.sqwDisable(0);
				  Serial.println("Square wave output disabled (low)");
				  break;

			  case 'z':
				  RTC.start();
				  Serial.println("Clock oscillator started.");
				  break;
			  case 'Z':
				  RTC.stop();
				  Serial.println("Clock oscillator stopped.");
				  break;

			  case '>':
				  in = SerialReadPosInt();
				  in2 = SerialReadPosInt();
				  RTC.writeData(in, in2);
				  Serial.print("Write to register ");
				  Serial.print(in);
				  Serial.print(" the value ");
				  Serial.println(in2);
				  break;
			  case '<':
				  in = SerialReadPosInt();
				  in2 = RTC.readData(in);
				  Serial.print("Read from register ");
				  Serial.print(in);
				  Serial.print(" the value ");
				  Serial.println(in2);
				  break;

			  default:
				  Serial.println("Unknown command. Try these:");
				  Serial.println(" h## - set Hours [range 1..12 or 0..24]");
				  Serial.println(" i## - set mInutes [range 0..59]");
				  Serial.println(" s## - set Seconds [range 0..59]");
				  Serial.println(" d## - set Date [range 1..31]");
				  Serial.println(" m## - set Month [range 1..12]");
				  Serial.println(" y## - set Year [range 0..99]");
				  Serial.println(" w## - set arbitrary day of Week [range 1..7]");
				  Serial.println(" t   - toggle 24-hour mode");
				  Serial.println(" a   - set AM          p   - set PM");
				  Serial.println();
				  Serial.println(" z   - start clock     Z   - stop clock");
				  Serial.println(" q   - SQW/OUT = 1Hz   Q   - stop SQW/OUT");
				  Serial.println();
				  Serial.println(" >##,###  - write to register ## the value ###");
				  Serial.println(" <##      - read the value in register ##");

			  }//switch on command

		  }

		  //read in numeric characters until something else
		  //or no more data is available on serial.
		  int SerialReadPosInt() {
			  int i = 0;
			  boolean done = false;
			  while (Serial.available() && !done)
			  {
				  char c = Serial.read();
				  if (c >= '0' && c <= '9')
				  {
					  i = i * 10 + (c - '0');
				  }
				  else
				  {
					  done = true;
				  }
			  }
			  return i;
		  }
	  }

void Solar(){
  //input Solar Cell monitoring & code here
  }
