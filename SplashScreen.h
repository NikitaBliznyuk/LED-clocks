// SplashScreen.h

#ifndef _SPLASHSCREEN_h
#define _SPLASHSCREEN_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "LED.h"

class SplashScreenClass
{
 public:
	 virtual void init() = 0;
	 virtual void update() = 0;
	 virtual void close() = 0;
};

#endif

