// 
// 
// 

#include "Loading.h"

void LoadingClass::init()
{
	loaded = false;
	currentIndex = 0;
	currentFade = 1.0f;
}

void LoadingClass::update()
{
	if (currentIndex < 60)
	{
		for (int i = 0; i < 3; i++)
			LED.strip.setPixelColor(LED.lines[i][currentIndex], LED.strip.Color(48, 213, 200));
		currentIndex++;
	}
	else
	{
		currentFade -= 0.1f;
		for(int i = 0; i < 60; i++)
			for(int j = 0; j < 3; j++)
				LED.strip.setPixelColor(LED.lines[j][i], LED.strip.Color(48 * currentFade, 213 * currentFade, 200 * currentFade));
		if (currentFade <= 0.1f)
			loaded = true;
	}

	LED.strip.show();
}

void LoadingClass::close()
{
	LED.clear();
}

bool LoadingClass::isLoaded()
{
	return loaded;
}


LoadingClass Loading;

