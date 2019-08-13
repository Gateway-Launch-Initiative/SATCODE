#include "vars.c""

void dash() {
	analogWrite(SPKpin1, 128);//128 default
	delay(DASHLEN);
	analogWrite(SPKpin1, 0);
	delay(DOTLEN);
}
void dit() {
	analogWrite(SPKpin1, 128);//128 default
	delay(DOTLEN);
	analogWrite(SPKpin1, 0);
	delay(DOTLEN);
}
void send(char c) {
	int i;
	if (c == ' ') {
		Serial.print(c);
		delay(7 * DOTLEN);
		return;
	}
	for (i = 0; i < N_MORSE; i++) {
		if (morsetab[i].c == c) {
			unsigned char p = morsetab[i].pat;
			Serial.print(morsetab[i].c);

			while (p != 1) {
				if (p & 1)
					dash();
				else
					dit();
				p = p / 2;
			}
			delay(2 * DOTLEN);
			return;
		}
	}
	/* if we drop off the end, then we send a space */
	Serial.print("?");
}
void sendmsg(char* str) {
	while (*str)
		send(*str++);
	Serial.println("");
}

void setup() {
	pinMode(SPKpin1, OUTPUT);
	Serial.begin(9600); //serial unnecessary except debugging as needed
	Serial.println("GateSat-01 initializing");
	Serial.println("GateSat-01 is property of the Gateway Cubesat Project");
	Serial.println("..."); //Put credits for other things here.
	Serial.println("Initialized");

	//Serial.println("") ;
}

void loop() {

	//checksensors(); check sensor readings here
	decidemode();//decide mode of transmit: CW vs Tone depednding on interval
	initiateTX();//Initiate the decided form of TX and proceeds to approprite TX void
}

void decidemode() {
	unsigned long currentMillis = millis();//millis counter for length of time in tone transmit mode
	if (currentMillis - previousMillis > interval) {

		// save the last time toggled state
		previousMillis = currentMillis;

		// toggle TX state
		if (TXmode == LOW)
			TXmode = HIGH;
		else
			TXmode = LOW;
	}
}
void initiateTX() {
	if (TXmode == HIGH) TransmitMorse();//Send CW
	else TransmitTone(); //Tone transmit mode based on sensor reading
}

void TransmitMorse() {//Make sure these are all CAPS or will not TX
	sendmsg("?????"); //Preamble to begin receiving
	sendmsg("GATESAT1/");
	sendmsg("OS,OK/");
	sendmsg("SAFEMODE,NO/");
	sendmsg("CORETEMP,");
	sendmsg(coretemp "/")
		sendmsg("LUX,22/ ");
	sendmsg("TELEMETRY,OK/ ");
	sendmsg("PV,520MV/");
	sendmsg("BATT1,/");
	sendmsg(batt1 "/");
	sendmsg("BUS1,");
	sendmsg(busone "/")
		sendmsg("RSSI,4DBM/");

	//All this code needs to be replaced with the INT to CHAR values from monitoring/systems
	//sendmsg ();
	delay(3000);
}

void Batt() {

	//input battery check/monitoring code here
}

void Solar() {

	//input Solar Cell monitoring & code here
}

void TransmitTone() {//Transmit tone based on sensor value- so people can hear space!
	val = analogRead(0);//Sensor to use for tone
	val = map(val, 0, 1024, 100, 200); //(First two are input limits from the sensor- second 2 are the pwm out
	analogWrite(SPKpin1, val);//Send PWM to create tone
}