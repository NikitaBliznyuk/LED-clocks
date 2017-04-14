#include "Gradient.h"
#include "LED.h"
#include "Clocks.h"

// REFACTOR THIS SHIT!!!
#include <Wire.h>
#include "RTClib.h"
#include <SoftwareSerial.h>
RTC_DS1307 RTC;
////////////////////
SoftwareSerial bluetooth(0, 1);

enum {SPLASH, CLOCK} mode;
enum {GRADIENT} splashType;

void useClock();

void setup()
{
	// THIS TOO!!!
	bluetooth.begin(9600);
	Wire.begin();
	RTC.begin();
	if (!RTC.isrunning()) 
	{
		RTC.adjust(DateTime(__DATE__, __TIME__));
	}
	////////////////////

	LED.strip.setBrightness(30);
	LED.strip.begin();
	LED.strip.show();
	Clocks.SetMode(Mode::Markup);
	Gradient.init();
	mode = CLOCK;
}

void loop()
{
	// check if we need to change mode
	if (bluetooth.available())
	{
		int value = bluetooth.read();
		if (value == 4)
		{
			while (!bluetooth.available);
			value = bluetooth.read();

			switch (value)
			{
			case 0:
				mode = CLOCK;
				break;
			case 1:
				mode = SPLASH;
				while (!bluetooth.available);
				value = bluetooth.read();
				switch (value)
				{
				case 0:
					splashType = GRADIENT;
				default:
					break;
				}
				break;
			default:
				break;
			}
		}
	}

	switch (mode)
	{
	case SPLASH:
		useSplashScreen();
		break;
	case CLOCK:
		useClock();
		break;
	}
}

void useSplashScreen()
{
	Gradient.update();
	delay(100);
}

void useClock()
{
	// THIS OMG!!!

	byte hour = 30;
	byte minute = 60;
	byte second = 60;

	DateTime now = RTC.now();

	hour = now.hour();
	minute = now.minute();
	second = now.second();

	if (hour >= 12)
		hour -= 12;
	if (hour >= 12 || minute >= 60 || second >= 60)
	{
		hour = 11;
		minute = 59;
		second = 59;
	}
	//////////////////////////////

	/// BLUETOOTH PART, REFACTOR!!!

	if (bluetooth.available())
	{
		byte val = bluetooth.read();
		// При символе "W" включаем светодиод
		if (val == 1)
		{
			// HERE - TIME
			while (!bluetooth.available());
			int h = bluetooth.read();
			while (!bluetooth.available());
			int m = bluetooth.read();
			bluetooth.flush();
			char time[8];
			if (m > 9 && h > 9)
				sprintf(time, "%d:%d:00", h, m);
			else if (m < 9 && h > 9)
				sprintf(time, "%d:0%d:00", h, m);
			else if (m > 9 && h < 9)
				sprintf(time, "0%d:%d:00", h, m);
			else
				sprintf(time, "0%d:0%d:00", h, m);
			RTC.adjust(DateTime(__DATE__, time));
		}
		else if (val == 2)
		{
			// HERE WILL BE MODE
			while (!bluetooth.available());
			val = bluetooth.read();
			bluetooth.flush();
			if (val == 'S')
			{
				Clocks.SetMode(Simple);
			}
			else if (val == 'L')
			{
				Clocks.SetMode(Loading);
			}
			else if (val == 'M')
			{
				Clocks.SetMode(Markup);
			}
			else if (val == 'A')
			{
				Clocks.SetMode(Arrows);
			}
		}
		else if (val == 3)
		{
			// HERE WILL BE COLOR
			while (!bluetooth.available());
			val = bluetooth.read();
			while (!bluetooth.available());
			byte r = bluetooth.read();
			while (!bluetooth.available());
			byte g = bluetooth.read();
			while (!bluetooth.available());
			byte b = bluetooth.read();
			bluetooth.flush();

			if (val == 'H')
			{
				Clocks.SetHourColor(r, g, b);
			}
			else if (val == 'M')
			{
				Clocks.SetMinuteColor(r, g, b);
			}
			else if (val == 'S')
			{
				Clocks.SetSecondColor(r, g, b);
			}
		}
	}

	////////////////////////////////

	Clocks.SetTime(hour, minute, second);
	delay(100);
}
