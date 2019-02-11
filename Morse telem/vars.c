int SPKpin = 3; //Needs to be PWM pin for spk/radio output
int Batt1 = 7.4;// Initialize & Globalize Battery One Level
int TXmode=LOW;//Toggle TX mode between CW and Tone
int val;//used for sensor to tone mapping
long previousMillis = 0; //millis used for time before toggle TX mode
long interval = 5000; // interval (milliseconds) for transmit tone mode (transmit mode toggle)
int batt1
int busone
int coretemp
struct t_mtab { char c, pat; } ;
struct t_mtab morsetab[] = {
	{'.', 106},
	{',', 115},
	{'?', 76},
	{'/', 41},
	{'A', 6},
	{'B', 17},
	{'C', 21},
	{'D', 9},
	{'E', 2},
	{'F', 20},
	{'G', 11},
	{'H', 16},
	{'I', 4},
	{'J', 30},
	{'K', 13},
	{'L', 18},
	{'M', 7},
	{'N', 5},
	{'O', 15},
	{'P', 22},
	{'Q', 27},
	{'R', 10},
	{'S', 8},
	{'T', 3},
	{'U', 12},
	{'V', 24},
	{'W', 14},
	{'X', 25},
	{'Y', 29},
	{'Z', 19},
	{'1', 62},
	{'2', 60},
	{'3', 56},
	{'4', 48},
	{'5', 32},
	{'6', 33},
	{'7', 35},
	{'8', 39},
	{'9', 47},
	{'0', 63}
} ;

#define N_MORSE  (sizeof(morsetab)/sizeof(morsetab[0]))
#define SPEED  (30)  //default 12 25 still stable 35 working
#define DOTLEN  (1200/SPEED)
#define DASHLEN  (3*(1200/SPEED))
