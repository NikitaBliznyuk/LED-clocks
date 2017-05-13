#include "Stars.h"
#include <Adafruit_NeoPixel.h>
#include "Loading.h"
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

enum WorkMode {SPLASH, CLOCK} mode;
enum SplashType {GRADIENT, STARS} splashType;

void useClock(int value);

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
	Clocks.SetMode(ClockMode::Markup);
	Gradient.init();
	Loading.init();
	Stars.init();
	while (!Loading.isLoaded())
	{
		Loading.update();
		delay(100);
	}
	Loading.close();
	mode = SPLASH;
	splashType = STARS;
}

void loop()
{
	// check if we need to change mode
	int value = 0;
	if (bluetooth.available())
	{
		value = bluetooth.read();
		if (value == 4)
		{
			while (!bluetooth.available());
			value = bluetooth.read();

			mode = SPLASH;

			switch (value)
			{
			case 0:
				splashType = GRADIENT;
				break;
			case 1:
				splashType = STARS;
				break;
			default:
				break;
			}
		}
		else
		{
			mode = CLOCK;
		}
	}

	switch (mode)
	{
	case SPLASH:
		useSplashScreen();
		break;
	case CLOCK:
		useClock(value);
		break;
	}

	delay(100);
}

void useSplashScreen()
{
	switch (splashType)
	{
	case SplashType::GRADIENT:
		Gradient.update();
		break;
	case SplashType::STARS:
		Stars.update();
		break;
	}
}

void useClock(int value)
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

	if (value != 0)
	{
		// При символе "W" включаем светодиод
		if (value == 1)
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
		else if (value == 2)
		{
			// HERE WILL BE MODE
			while (!bluetooth.available());
			value = bluetooth.read();
			bluetooth.flush();
			if (value == 'S')
			{
				Clocks.SetMode(ClockMode::Simple);
			}
			else if (value == 'L')
			{
				Clocks.SetMode(ClockMode::Load);
			}
			else if (value == 'M')
			{
				Clocks.SetMode(ClockMode::Markup);
			}
			else if (value == 'A')
			{
				Clocks.SetMode(ClockMode::Arrows);
			}
		}
		else if (value == 3)
		{
			// HERE WILL BE COLOR
			while (!bluetooth.available());
			value = bluetooth.read();
			while (!bluetooth.available());
			byte r = bluetooth.read();
			while (!bluetooth.available());
			byte g = bluetooth.read();
			while (!bluetooth.available());
			byte b = bluetooth.read();
			bluetooth.flush();

			if (value == 'H')
			{
				Clocks.SetHourColor(r, g, b);
			}
			else if (value == 'M')
			{
				Clocks.SetMinuteColor(r, g, b);
			}
			else if (value == 'S')
			{
				Clocks.SetSecondColor(r, g, b);
			}
		}
	}

	////////////////////////////////

	Clocks.SetTime(hour, minute, second);
}
