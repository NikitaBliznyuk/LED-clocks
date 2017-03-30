// Clocks.h

#ifndef _CLOCKS_h
#define _CLOCKS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Adafruit_NeoPixel.h>

enum Mode
{
	Loading, Simple
};

class ClocksClass
{
 private:
	 int PIN = 6;
	 int hoursIndex = 0;
	 int minutesIndex = 60;
	 int secondsIndex = 120;

	 uint32_t hourColor, minuteColor, secondColor;

	 int currentTime[3];
	 Mode mode;

	 void SetHours(int hours);
	 void SetMinutes(int minutes);
	 void SetSeconds(int seconds);

 public:
	 ClocksClass();

	int count_led = 180;
	Adafruit_NeoPixel strip;

	void Clear();
	void SetTime(int hours, int minutes, int seconds);
	void SetHourColor(int red, int green, int blue);
	void SetMode(Mode mode);
};

extern ClocksClass Clocks;

#endif

