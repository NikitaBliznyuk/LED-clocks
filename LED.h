// LED.h

#ifndef _LED_h
#define _LED_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Adafruit_NeoPixel.h>

class LEDClass
{
private:
	byte PIN = 6;

	void calculateIndexes();
public:
	Adafruit_NeoPixel strip;
	byte lines[3][60];

	LEDClass();
	void clear();
};

extern LEDClass LED;

#endif

