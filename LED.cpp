// 
// 
// 

#include "LED.h"

LEDClass LED;

void LEDClass::calculateIndexes()
{
	for (byte i = 0; i < 60; i++)
	{
		if (i % 2 == 0)
		{
			lines[0][i] = i * 3;
			lines[1][i] = i * 3 + 1;
			lines[2][i] = i * 3 + 2;
		}
		else
		{
			lines[0][i] = i * 3 + 2;
			lines[1][i] = i * 3 + 1;
			lines[2][i] = i * 3;
		}
	}
}

LEDClass::LEDClass()
{
	strip = Adafruit_NeoPixel(180, PIN, NEO_GRB + NEO_KHZ800);

	calculateIndexes();
}

void LEDClass::clear()
{
	for (byte i = 0; i < 180; i++)
	{
		strip.setPixelColor(i, strip.Color(0, 0, 0));
	}
}