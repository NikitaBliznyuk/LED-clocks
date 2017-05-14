// Stars.h

#ifndef _STARS_h
#define _STARS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define starCount 180
#define randomValue 1365
#define maxShiningStars 40
#define updateTime 5000 // time in ms
#define fadeValue 15
#define growValue 15

#include "SplashScreen.h"

#include <time.h>

class StarsClass: SplashScreenClass
{
private:
	unsigned char stars[starCount];
	unsigned char currentGrowing;
	unsigned char currentFading;

	void randomizeGrowing();
	void randomizeFading();
 public:
	void init();
	void update();
	void close();
};

extern StarsClass Stars;

#endif

