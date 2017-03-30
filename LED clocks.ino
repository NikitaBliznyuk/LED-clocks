#include "Clocks.h"

// REFACTOR THIS SHIT!!!
#include <Wire.h>
#include "RTClib.h"
RTC_DS1307 RTC;
////////////////////

void setup()
{
	// THIS TOO!!!
	Serial.begin(9600);
	Wire.begin();
	RTC.begin();
	if (!RTC.isrunning()) {
		Serial.println("RTC is NOT running!");
		// following line sets the RTC to the date & time this sketch was compiled
		RTC.adjust(DateTime(__DATE__, __TIME__));
	}
	////////////////////

	Clocks.strip.setBrightness(20);
	Clocks.strip.begin();
	Clocks.strip.show();
	Clocks.SetMode(Loading);
}

void loop()
{
	// THIS OMG!!!
	int hour = 30;
	int minute = 60;
	int second = 60;

	DateTime now = RTC.now();
	Serial.print(now.hour(), DEC);
	Serial.print(':');
	Serial.print(now.minute(), DEC);
	Serial.print(':');
	Serial.print(now.second(), DEC);
	Serial.println();

	hour = now.hour();
	minute = now.minute();
	second = now.second();

	if (hour >= 12)
		hour -= 12;
	if (hour >= 12 || minute >= 60 || second >= 60)
	{
		hour = 0;
		minute = 0;
		second = 0;
	}
	//////////////////////////////

	Clocks.SetTime(hour, minute, second);
	delay(100);
}
