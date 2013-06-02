#include "Arduino.h"
#include "AS5040.h"
#include "Morse.h"

Morse morse(13);
AS5040 encoder = AS5040();

void blink_sos(){
    morse.dot(); morse.dot(); morse.dot();
    morse.dash(); morse.dash(); morse.dash();
    morse.dot(); morse.dot(); morse.dot();
}

void setup()
{
    Serial.begin(9600);
    encoder.initialize();
    blink_sos();
}

void loop()
{
  Serial.println(encoder.read());
}

