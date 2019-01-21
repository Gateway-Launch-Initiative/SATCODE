#include "vars.c"
#include <../avr/wdt.h>

void dash() {
  analogWrite(SPKpin, 128) ;//128 default
  delay(DASHLEN);
  analogWrite(SPKpin, 0) ;
  delay(DOTLEN) ;
}
void dit() {
  analogWrite(SPKpin, 128) ;//128 default
  delay(DOTLEN);
  analogWrite(SPKpin, 0) ;
  delay(DOTLEN);
}
void send(char c) {
  int i ;
  if (c == ' ') {
    Serial.print(c) ;
    delay(7*DOTLEN) ;
    return ;
  }
  for (i=0; i<N_MORSE; i++) {
    if (morsetab[i].c == c) {
      unsigned char p = morsetab[i].pat ;
      Serial.print(morsetab[i].c) ;

      while (p != 1) {
          if (p & 1)
            dash() ;
          else
            dit() ;
          p = p / 2 ;
      }
      delay(2*DOTLEN) ;
      return ;
    }
  }
  /* if we drop off the end, then we send a space */
  Serial.print("?") ;
}
void sendmsg(char *str) {
  while (*str)
    send(*str++) ;
  Serial.println("");
}

void setup() {
  wdt_disable();
  wdt_enable (WDTO_8S);//watchdog
  pinMode(SPKpin, OUTPUT) ;
  Serial.begin(9600) ; //serial unnecessary except debugging as needed
  Serial.println("GateSat-01 initializing") ;
  Serial.println("CW DL code by Eric William") ;
  Serial.println("...") ; //Put credits for other things here.
  Serial.println("Initialized") ;
  //Serial.println("") ;
  }

void loop() {
  resetWatchdog();
  //checksensors(); check sensor readings here
  decidemode();//decide mode of transmit: CW vs Tone depednding on interval
  //modeindicator(); add mode indicator LED etc here (DO WE WANT TO GET RID OF THIS? AS IT WILL BE IN SPACE.
  initiateTX();//Initiate the decided form of TX and proceeds to approprite TX void
  }

void decidemode(){
  unsigned long currentMillis = millis();//millis counter for length of time in tone transmit mode
  if(currentMillis - previousMillis > interval) {
   // save the last time toggled state
   previousMillis = currentMillis;
   // toggle TX state
   if (TXmode == LOW)
   TXmode = HIGH;
   else
   TXmode = LOW;
   }
  }
void initiateTX(){
  if (TXmode ==HIGH) TransmitMorse();//Send CW
  else TransmitTone(); //Tone transmit mode based on sensor reading
}

void resetWatchdog() {
	wdt_reset();
}

void TransmitMorse(){//Make sure these are all CAPS or will not TX
   sendmsg("?????") ; //Preamble to begin receiving
   resetWatchdog();
   sendmsg("GATESAT1/") ;
   resetWatchdog();
   sendmsg("OS,OK/") ;
   resetWatchdog();
   sendmsg("SAFEMODE,NO/") ;
   resetWatchdog();
   sendmsg("WATCHDOG,4/") ;
   resetWatchdog();
   sendmsg("ITEMP,0C/ ") ;
   resetWatchdog();
   sendmsg("LUX,22/ ") ;
   resetWatchdog();
   sendmsg("TELEMETRY,OK/ ") ;
   resetWatchdog();
   sendmsg("ANTENNA,DEP/") ;
   resetWatchdog();
   sendmsg("PV,520MV/") ;
   resetWatchdog();
   sendmsg("BATT1,620MV/") ;
   resetWatchdog();
   sendmsg("BUSA,4MA/") ;
   resetWatchdog();
   sendmsg("RSSI,4DBM/") ;
   resetWatchdog();
   //All this code needs to be replaced with the INT to CHAR values from monitoring/systems
   //sendmsg (Batt1);
   delay(3000) ;
   }
void Batt(){
  //input battery check/monitoring code here
  }
void Watchdog(){
  //input Watchdog code here
  }
void Solar(){
  //input Solar Cell monitoring & code here
  }
  
void TransmitTone(){//Transmit tone based on sensor value- so people can hear space!
  val=analogRead(0);//Sensor to use for tone
  val = map(val, 0, 1024, 100, 200); //(First two are input limits from the sensor- second 2 are the pwm out
  analogWrite(SPKpin, val) ;//Send PWM to create tone
  }  
