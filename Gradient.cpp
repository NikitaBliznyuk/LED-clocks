// 
// 
// 

#include "Gradient.h"

void GradientClass::updateColors()
{
	switch (pos1)
	{
	case 0:
		r1 -= step;
		g1 += step;
		if (g1 >= 255)
		{
			pos1++;
			r1 = 0;
			g1 = 255;
		}
		break;
	case 1:
		g1 -= step;
		b1 += step;
		if (b1 >= 255)
		{
			pos1++;
			g1 = 0;
			b1 = 255;
		}
		break;
	case 2:
		b1 -= step;
		r1 += step;
		if (r1 >= 255)
		{
			pos1 = 0;
			b1 = 0;
			r1 = 255;
		}
		break;
	}

	switch (pos2)
	{
	case 0:
		r2 -= step;
		g2 += step;
		if (g2 >= 255)
		{
			pos2++;
			r2 = 0;
			g2 = 255;
		}
		break;
	case 1:
		g2 -= step;
		b2 += step;
		if (b2 >= 255)
		{
			pos2++;
			g2 = 0;
			b2 = 255;
		}
		break;
	case 2:
		b2 -= step;
		r2 += step;
		if (r2 >= 255)
		{
			pos2 = 0;
			b2 = 0;
			r2 = 255;
		}
		break;
	}
}

void GradientClass::init()
{
	r1 = 255; g1 = 0; b1 = 0;
	r2 = 0; g2 = 255; b2 = 0;

	pos1 = 0, pos2 = 1;

	step = 1;
}

void GradientClass::update()
{
	LED.clear();
	// update colors
	updateColors();
	// set colors to LEDs
	double stepR = (double)(r2 - r1) / 30.0;
	double stepG = (double)(g2 - g1) / 30.0;
	double stepB = (double)(b2 - b1) / 30.0;

	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			LED.strip.setPixelColor(LED.lines[j][i], LED.strip.Color(r1 + stepR * i, g1 + stepG * i, b1 + stepB * i));
			LED.strip.setPixelColor(LED.lines[j][i + 30], LED.strip.Color(r2 - stepR * i, g2 - stepG * i, b2 - stepB * i));
		}
	}
	// show LEDs
	LED.strip.show();
}

void GradientClass::close()
{
	LED.clear();
}

GradientClass Gradient;
