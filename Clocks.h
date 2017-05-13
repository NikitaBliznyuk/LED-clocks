// Clocks.h

#ifndef _CLOCKS_h
#define _CLOCKS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "LED.h"

enum ClockMode
{
	Load, Simple, Markup, Arrows
};

class ClocksClass
{
 private:
	 uint32_t hourColor, minuteColor, secondColor;

	 byte currentTime[3];
	 ClockMode mode;

	 void SetHours(byte hours);
	 void SetMinutes(byte minutes);
	 void SetSeconds(byte seconds);
	 void SetArrows(byte hours, byte minutes, byte seconds);
	 void ShowMarks();

 public:
	 ClocksClass();

	 void SetTime(byte hours, byte minutes, byte seconds);
	 void SetHourColor(byte red, byte green, byte blue);
	 void SetMinuteColor(byte red, byte green, byte blue);
	 void SetSecondColor(byte red, byte green, byte blue);
	 void SetMode(ClockMode mode);
};

extern ClocksClass Clocks;

#endif

