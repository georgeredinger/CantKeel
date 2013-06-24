#include "Arduino.h"
#include "AS5040.h"
#include <Adafruit_NeoPixel.h>
int errorBlink=0;
int blinkPin=12;
AS5040 encoder = AS5040();
const int NbrLEDs = 4;
// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(4, 12, NEO_GRB + NEO_KHZ800);

int full_circle_to_port_starboard(int angle){
	if(angle < 0){
		//Serial.println("sensor error");
		return -99;
	}
	if(angle < 46 ){
		return(angle);
	}
	if(angle > 314){
		return(-(360-angle));
	}
	//Serial.println("Out of range");
  return(-100);
}

void setup()
{
	Serial.begin(9600);
	Serial.println("Canting Keel Encoder");
	encoder.initialize();
	strip.begin();
	strip.show(); // Initialize all pixels to 'off'
}

void loop()
{
	int red,green,blue;
	int ledLevel;
	int angle;
	bool centered=false;
  delay(100);
  angle	= encoder.read();
	angle = full_circle_to_port_starboard(angle);
	Serial.println(angle);
	if(angle > -46){
		if(angle < 0  ) { //port
			angle = -angle;
			red=1;green=0;blue=0;
			centered = (angle < 2);
			ledLevel = map(angle, 0,45 , 0, NbrLEDs); // map to number of LEDs
		} else { //starboard
			green=1;red=0;blue=0;
			centered = (angle < 2 );
			ledLevel = map(angle, 0,45 , 0, NbrLEDs); // map to number of LEDs for (int led = 0; led < NbrLEDs; led++) {
		}
		}else{
			if(errorBlink){
				strip.setPixelColor(0, 0x0000ff);
				strip.setPixelColor(1, 0x0000ff);
				strip.setPixelColor(2, 0x0000ff);
				strip.setPixelColor(3, 0x0000ff);
			}else{
				strip.setPixelColor(0, 0);
				strip.setPixelColor(1, 0);
				strip.setPixelColor(2, 0);
				strip.setPixelColor(3, 0);
			}
		  strip.show();
			errorBlink = !errorBlink;
			ledLevel=0;
		}

		if(centered){
	      Serial.println("centered");
				strip.setPixelColor(0, 0xff0000);
				strip.setPixelColor(1, 0xff0000);
				strip.setPixelColor(2, 0x00ff00);
				strip.setPixelColor(3, 0x00ff00);
			  strip.show();
		}else{	
		for (int led = 0; led < NbrLEDs; led++) {
			if (led < ledLevel ) {
				strip.setPixelColor(led, red*0xff,green*0xff,blue*0xff);
			}
			else {
				strip.setPixelColor(led, 0);
			}
		}
		if(angle > 0){
			strip.setPixelColor(ledLevel, abs(angle-ledLevel*11)*23*red,abs(angle-ledLevel*11)*23*green,blue*0xff);
			strip.show();
		}
	}
	}

