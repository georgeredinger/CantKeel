#include "Arduino.h"
#include "AS5040.h"
#include "Morse.h"

int blinkPin=12;
Morse morse(11);
AS5040 encoder = AS5040();
int blink_rate=0;

void sos() {
    morse.dot(); morse.dot(); morse.dot();morse.space();
    morse.dash(); morse.dash(); morse.dash();morse.space();
    morse.dot(); morse.dot(); morse.dot();morse.space();
}

ISR(TIMER1_COMPA_vect)          // timer compare interrupt service routine
{
	digitalWrite(blinkPin, digitalRead(blinkPin) ^ 1);   // toggle LED pin
}


void setup()
{
	Serial.begin(9600);
	Serial.println("Canting Keel Encoder");
	encoder.initialize();
	pinMode(12, OUTPUT);
	pinMode(11, OUTPUT);
	noInterrupts();           // disable all interrupts
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1  = 0;

	OCR1A = 31250;            // compare match register 16MHz/256/2Hz
	TCCR1B |= (1 << WGM12);   // CTC mode
	TCCR1B |= (1 << CS12);    // 256 prescaler
	TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt
	interrupts();             // enable all interrupts

}

void loop()
{
	int angle = encoder.read();

  Serial.println(angle);
 	noInterrupts();
	if((angle > 0) && (angle < 90)) {
     digitalWrite(12, LOW);
		 blinkPin = 11;
	}
	if(angle > 270) {
     digitalWrite(11, LOW);
		 blinkPin = 12;
	}
	OCR1A = angle*1000;
	interrupts();
}


