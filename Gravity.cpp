// 
// 
// 

#include "Gravity.h"

void GravityClass::changePosition()
{
	int end = 0;
	for (int k = 0; k < 3; k++)
	{
		for (int i = 15 - 1; i >= 0; i--)
		{
			if (lines[k][i].inMove)
			{
				if (lines[k][i].position < (90 - (15 - i) * 3))
				{
					lines[k][i].position += lines[k][i].position % 2 == 0 ? 1 + 2 * k : 5 - 2 * k;
				}
				else if (i == 0)
				{
					end++;
				}
			}
			else
			{
				int value = rand() % 3;
				lines[value][i].inMove = true;
				break;
			}
		}
	}
	for (int k = 3; k < 6; k++)
	{
		for (int i = 15 - 1; i >= 0; i--)
		{
			if (lines[k][i].inMove)
			{
				if (lines[k][i].position >= (90 + (15 - i) * 3))
				{
					lines[k][i].position -= lines[k][i].position % 2 == 0 ? 1 + 2 * (k - 3) : 5 - 2 * (k - 3);
				}
				else if (i == 0)
				{
					end++;
				}
			}
			else
			{
				int value = rand() % 3 + 3;
				lines[value][i].inMove = true;
				break;
			}
		}
	}

	if (end == 6)
		inRotation = true;
}

void GravityClass::rotate()
{
	if (lines[0][0].position != 135)
	{
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				if ((lines[i][j].position - 3) < 0)
				{
					switch (i)
					{
					case 0:
						lines[i][j].position = 177;
						break;
					case 1:
						lines[i][j].position = 178;
						break;
					case 2:
						lines[i][j].position = 179;
						break;
					case 3:
						lines[i][j].position = 179;
						break;
					case 4:
						lines[i][j].position = 178;
						break;
					case 5:
						lines[i][j].position = 177;
						break;
					default:
						break;
					}
				}
				else
				{
					if (i >= 3)
						lines[i][j].position -= lines[i][j].position % 2 == 0 ? 1 + 2 * (i % 3) : 5 - 2 * (i % 3);
					else
						lines[i][j].position -= lines[i][j].position % 2 == 0 ? 5 - 2 * (i % 3) : 1 + 2 * (i % 3);
				}
			}
		}
	}
	else
	{
		init();
	}
}

void GravityClass::init()
{
	for (int i = 0; i < 15; i++)
	{
		lines[0][i].position = LED.lines[2][i];
		lines[1][i].position = LED.lines[1][i];
		lines[2][i].position = LED.lines[0][i];
		lines[3][i].position = LED.lines[0][59 - i];
		lines[4][i].position = LED.lines[1][59 - i];
		lines[5][i].position = LED.lines[2][59 - i];

		lines[0][i].inMove = false;
		lines[1][i].inMove = false;
		lines[2][i].inMove = false;
		lines[3][i].inMove = false;
		lines[4][i].inMove = false;
		lines[5][i].inMove = false;
	}

	inRotation = false;
}

void GravityClass::update()
{
	LED.clear();

	if (!inRotation)
	{
		changePosition();
	}
	else
	{
		rotate();
	}

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			LED.setColor(lines[i][j].position, 255, 255, 0);
		}
	}

	LED.show();
}

void GravityClass::close()
{
	LED.clear();
}


GravityClass Gravity;

