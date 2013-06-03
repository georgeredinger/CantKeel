#include "Arduino.h"
#include "AS5040.h"
#include "Morse.h"

Morse morse(11);
AS5040 encoder = AS5040();
void sos() {
    morse.dot(); morse.dot(); morse.dot();morse.space();
    morse.dash(); morse.dash(); morse.dash();morse.space();
    morse.dot(); morse.dot(); morse.dot();morse.space();
}

void setup()
{
    Serial.begin(9600);
		Serial.println("Canting Keel Encoder");
    encoder.initialize();
    sos();
}

void loop()
{
	int angle = encoder.read();

//	if(angle < 0) {
//		sos();
//	}
  Serial.print(angle);
	Serial.print(" ");
	for(int i=0;i<angle/3;i++) Serial.print("*");
	Serial.println(" ");
}

