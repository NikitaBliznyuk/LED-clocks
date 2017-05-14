// 
// 
// 

#include "Stars.h"

void StarsClass::randomizeGrowing()
{
	int count = 0;
	do
	{
		currentGrowing = rand() % starCount;
		count++;
	} while (currentFading == currentGrowing || (stars[currentGrowing] > 0 && count < 50));
}

void StarsClass::randomizeFading()
{
	int count = 0;
	do
	{
		currentFading = rand() % starCount;
		count++;
	} while (currentFading == currentGrowing || (stars[currentFading] == 0 && count < 50));
}

void StarsClass::init()
{
	LED.clear();

	srand(randomValue);

	// Initial random

	for (int i = 0; i < starCount; i++)
	{
		stars[i] = 0;
	}

	for (int i = 0; i < maxShiningStars; i++)
	{
		stars[rand() % starCount] = 255 - rand() % 150;
	}

	randomizeFading();
	randomizeGrowing();
}

void StarsClass::update()
{
	LED.clear();

	for (int i = 0; i < starCount; i++)
	{
		float value = stars[i];
		value /= 255.0f;
		LED.setColor(i, (int)(32.0f * value), (int)(128.0f * value), (int)(212.0f * value));
	}

	LED.show();

	// Update fading and growing stars


	if (stars[currentFading] <= fadeValue)
	{
		stars[currentFading] = 0;

		randomizeFading();
	}
	else
	{
		stars[currentFading] -= fadeValue;
	}

	int maxValue = 255 - rand() % 150;

	if (stars[currentGrowing] >= maxValue - growValue)
	{
		stars[currentGrowing] = stars[currentGrowing] > maxValue ? stars[currentGrowing] : maxValue;

		randomizeGrowing();
	}
	else
	{
		stars[currentGrowing] += growValue;
	}

}

void StarsClass::close()
{
	LED.clear();
}


StarsClass Stars;

