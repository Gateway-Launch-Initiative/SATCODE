#include <Wire.h>

#define NODE_ADDRESS 41  // Change this unique address for each I2C slave node
#define PAYLOAD_SIZE 2 // Number of bytes  expected to be received by the master I2C node
int x = 0;
byte nodePayload[PAYLOAD_SIZE];

void setup()
{

  Serial.begin(9600);  
  Serial.println("GateSat-01 initializing");
  delay(2000);
  Serial.println("GateSat-01 Is the property of the Gateway Cubesat Project");
  Serial.print("Node address: ");
  Serial.println(NODE_ADDRESS);
  Serial.print("Payload size: ");
  Serial.println(PAYLOAD_SIZE);
  Wire.begin(NODE_ADDRESS);  // Activate I2C network
  Wire.onReceive(receiveEvent);
  
  //Wire.onRequest(requestEvent); // Request attention of master node
}

void loop()
{ 
  delay(100);
  //nodePayload[0] = NODE_ADDRESS; // I am sending Node address back.  Replace with any other data 
  //nodePayload[1] = analogRead(A0)/4; // Read A0 and fit into 1 byte. Replace this line with your sensor value
  
}

void intsig() {
	if (x == 1) {
		Serial.println("Initialized");
	}
	else {
		delay(100)
	}
}

void receiveEvent(int bytes) {
	x = Wire.read();    // read one character from the I2C
	intsig();
}

void requestEvent()
{
  Wire.write(nodePayload,PAYLOAD_SIZE);  
}
