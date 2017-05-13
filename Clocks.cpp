// 
// 
// 

#include "Clocks.h"

void ClocksClass::SetTime(byte hours, byte minutes, byte seconds)
{
	currentTime[0] = hours;
	currentTime[1] = minutes;
	currentTime[2] = seconds;
		
	LED.clear();

	if (mode == Arrows)
	{
		SetArrows(hours, minutes, seconds);
	}
	else
	{
		SetHours(hours);
		SetMinutes(minutes);
		if (mode == Markup)
		{
			ShowMarks();
		}
		else
		{
			SetSeconds(seconds);
		}
	}

	LED.strip.show();
}

void ClocksClass::SetHourColor(byte red, byte green, byte blue)
{
	hourColor = LED.strip.Color(red, green, blue);
}

void ClocksClass::SetMinuteColor(byte red, byte green, byte blue)
{
	minuteColor = LED.strip.Color(red, green, blue);
}

void ClocksClass::SetSecondColor(byte red, byte green, byte blue)
{
	secondColor = LED.strip.Color(red, green, blue);
}

void ClocksClass::SetMode(ClockMode mode)
{
	this->mode = mode;
}

void ClocksClass::SetHours(byte hours)
{
	byte hourStep = 5;
	byte maxValue = hourStep * hours + hourStep;

	byte i = mode == Load ? 0 : hourStep * hours;

	if (mode != Load)
	{
		if (i == 0)
		{
			LED.strip.setPixelColor(LED.lines[0][58], hourColor);
			LED.strip.setPixelColor(LED.lines[0][59], hourColor);
		}
		else
		{
			i -= 2;
		}

		maxValue -= 2;
	}


	for (; i < maxValue; i++)
	{
		LED.strip.setPixelColor(LED.lines[0][i], hourColor);
	}
}

void ClocksClass::SetMinutes(byte minutes)
{
	byte i = mode == Load ? 0 : minutes;

	for (; i <= minutes; i++)
	{
		LED.strip.setPixelColor(LED.lines[1][i], minuteColor);
	}
}

void ClocksClass::SetSeconds(byte seconds)
{
	byte i = mode == Load ? 0 : seconds;

	for (; i <= seconds; i++)
	{
		LED.strip.setPixelColor(LED.lines[2][i], secondColor);
	}
}

void ClocksClass::SetArrows(byte hours, byte minutes, byte seconds)
{
	byte hourIndex = (byte)(((float)hours + (float)minutes / 60.0f) * 5.0f);

	LED.strip.setPixelColor(LED.lines[0][minutes], minuteColor);
	LED.strip.setPixelColor(LED.lines[1][minutes], minuteColor);
	LED.strip.setPixelColor(LED.lines[2][minutes], minuteColor);
	LED.strip.setPixelColor(LED.lines[0][hourIndex], hourColor);
	LED.strip.setPixelColor(LED.lines[1][hourIndex], hourColor);
	LED.strip.setPixelColor(LED.lines[0][seconds], secondColor);
}

void ClocksClass::ShowMarks()
{
	for (byte i = 0; i < 60; i += 5)
	{
		LED.strip.setPixelColor(LED.lines[2][i], secondColor);
	}
}

ClocksClass::ClocksClass()
{
	currentTime[0] = 0;
	currentTime[1] = 0;
	currentTime[2] = 0;

	hourColor = LED.strip.Color(255, 0, 0);
	minuteColor = LED.strip.Color(48, 213, 200);
	secondColor = LED.strip.Color(34, 139, 34);
}


ClocksClass Clocks;

