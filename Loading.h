// Loading.h

#ifndef _LOADING_h
#define _LOADING_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "SplashScreen.h"

class LoadingClass: public SplashScreenClass
{
private:
	int currentIndex;
	float currentFade;
	bool loaded;
public:
	void init();
	void update();
	void close();
	bool isLoaded();
};

extern LoadingClass Loading;

#endif

