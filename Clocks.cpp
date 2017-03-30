// 
// 
// 

#include "Clocks.h"

void ClocksClass::Clear()
{
	for (int i = 0; i < count_led; i++)
	{
		strip.setPixelColor(i, strip.Color(0, 0, 0));
	}
}

void ClocksClass::SetTime(int hours, int minutes, int seconds)
{
	currentTime[0] = hours;
	currentTime[1] = minutes;
	currentTime[2] = seconds;
		
	Clear();

	SetHours(hours);
	SetMinutes(minutes);
	SetSeconds(seconds);

	strip.show();
}

void ClocksClass::SetHourColor(int red, int green, int blue)
{
	hourColor = strip.Color(red, green, blue);
}

void ClocksClass::SetMode(Mode mode)
{
	this->mode = mode;
}

void ClocksClass::SetHours(int hours)
{
	int hourStep = 5;

	if (hours == 0)
	{
		for (int i = hoursIndex; i < hoursIndex + 60; i++)
		{
			strip.setPixelColor(i, strip.Color(0, 0, 0));
		}
	}

	int i = hoursIndex;
	i += mode == Loading ? 0 : hourStep * hours;

	for (; i < hourStep * hours + hourStep; i++)
	{
		strip.setPixelColor(i, hourColor);
	}
}

void ClocksClass::SetMinutes(int minutes)
{
	if (minutes == 0)
	{
		for (int i = minutesIndex; i < minutesIndex + 60; i++)
		{
			strip.setPixelColor(i, strip.Color(0, 0, 0));
		}
	}
	
	int i = minutesIndex;
	i += mode == Loading ? 0 : minutes;

	for (; i <= minutesIndex + minutes; i++)
	{
		strip.setPixelColor(i, minuteColor);
	}
}

void ClocksClass::SetSeconds(int seconds)
{
	if (seconds == 0)
	{
		for (int i = secondsIndex; i < secondsIndex + 60; i++)
		{
			strip.setPixelColor(i, strip.Color(0, 0, 0));
		}
	}
	
	int i = secondsIndex;
	i += mode == Loading ? 0 : seconds;

	for (; i <= secondsIndex + seconds; i++)
	{
		strip.setPixelColor(i, secondColor);
	}
}

ClocksClass::ClocksClass()
{
	strip = Adafruit_NeoPixel(count_led, PIN, NEO_GRB + NEO_KHZ800);

	currentTime[0] = 0;
	currentTime[1] = 0;
	currentTime[2] = 0;

	hourColor = strip.Color(255, 0, 0);
	minuteColor = strip.Color(48, 213, 200);
	secondColor = strip.Color(34, 139, 34);
}


ClocksClass Clocks;

