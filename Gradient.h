// Gradient.h

#ifndef _GRADIENT_h
#define _GRADIENT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "SplashScreen.h"

class GradientClass: public SplashScreenClass
{
private:
	unsigned char r1, g1, b1, r2, g2, b2; // *1 for 1st color, *2 - for 2nd.
	int pos1, pos2; // current color position (near R - 0, near G - 1, near B - 2).
	int step; // color changing step.

	void updateColors();
public:
	void init();
	void update();
	void close();
};

extern GradientClass Gradient;

#endif

