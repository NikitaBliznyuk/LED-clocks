#include "LED.h"
#include "Clocks.h"

// REFACTOR THIS SHIT!!!
#include <Wire.h>
#include "RTClib.h"
#include <SoftwareSerial.h>
RTC_DS1307 RTC;
////////////////////
SoftwareSerial mySerial(0, 1);

void setup()
{
	// THIS TOO!!!
	mySerial.begin(9600);
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
}

void loop()
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

	if (mySerial.available())
	{
		byte val = mySerial.read();
		// При символе "W" включаем светодиод
		if (val == 1)
		{
			// HERE - TIME
			while (!mySerial.available());
			char h = mySerial.read() + '0';
			while (!mySerial.available());
			char m = mySerial.read() + '0';
			mySerial.flush();
			char time[8];
			sprintf(time, "%d:%d:00", h, m);
			RTC.adjust(DateTime(__DATE__, time));
		}
		else if (val == 2)
		{
			// HERE WILL BE MODE
			while (!mySerial.available());
			val = mySerial.read();
			mySerial.flush();
			if (val == 'S')
			{
				Clocks.SetMode(Simple);
			}
			// При символе "S" выключаем светодиод
			if (val == 'L')
			{
				Clocks.SetMode(Loading);
			}
		}
		else if (val == 3)
		{
			// HERE WILL BE COLOR
			while (!mySerial.available());
			val = mySerial.read();
			while (!mySerial.available());
			byte r = mySerial.read();
			while (!mySerial.available());
			byte g = mySerial.read();
			while (!mySerial.available());
			byte b = mySerial.read();
			mySerial.flush();

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
