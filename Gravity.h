// Gravity.h

#ifndef _GRAVITY_h
#define _GRAVITY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "SplashScreen.h"

struct Point
{
	unsigned char position;
	bool inMove;
};

class GravityClass: SplashScreenClass
{
private:
	Point lines[6][15];
	bool inRotation;

	void changePosition();
	void rotate();
 public:
	void init();
	void update();
	void close();
};

extern GravityClass Gravity;

#endif

