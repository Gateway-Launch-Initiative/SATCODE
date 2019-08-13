int SPKpin1 = 3; //Needs to be PWM pin for spk/radio output
int Batt1 = 7.4;// Initialize & Globalize Battery One Level
int TXmode = LOW;//Toggle TX mode between CW and Tone
int val;//used for sensor to tone mapping
long previousMillis = 0; //millis used for time before toggle TX mode
long interval = 5000; // interval (milliseconds) for transmit tone mode (transmit mode toggle)
int batt1
int busone
int coretemp