#include <iostream>
#include <Windows.h>
#include <cmath>
#include <ctime>

#define CIRCLE 360
#define PI 3.14159

#include "darts_board.h"

// maintained for gotoxy function to land on exact point after dart throw
int g_printHeight = 0;

// this is only used in board and game to maintain height
void NewLine()
{
	std::cout << "\n";
	g_printHeight++;
}

// the famous gotoxy function to go to the perticular position in console
void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

// convert degree to radian
// for sin cos calculation only
double ToRadian(int degree)
{
	double radian = degree * PI / 180;
	return radian;
}

// get the score according to the angle theta
int GetArcScore(int theta)
{
	if (theta > 72 && theta <= 90)
	{
		return 1;
	}
	else if (theta > 306 && theta <= 324)
	{
		return 2;
	}
	else if (theta > 270 && theta <= 288)
	{
		return 3;
	}
	else if (theta > 36 && theta <= 54)
	{
		return 4;
	}
	else if (theta > 108 && theta <= 126)
	{
		return 5;
	}
	else if (theta >= 0 && theta <= 18)
	{
		return 6;
	}
	else if (theta > 234 && theta <= 252)
	{
		return 7;
	}
	else if (theta > 198 && theta <= 216)
	{
		return 8;
	}
	else if (theta > 144 && theta <= 162)
	{
		return 9;
	}
	else if (theta > 342 && theta <= 360)
	{
		return 10;
	}
	else if (theta > 180 && theta <= 198)
	{
		return 11;
	}
	else if (theta > 126 && theta <= 144)
	{
		return 12;
	}
	else if (theta > 18 && theta <= 36)
	{
		return 13;
	}
	else if (theta > 162 && theta <= 180)
	{
		return 14;
	}
	else if (theta > 324 && theta <= 342)
	{
		return 15;
	}
	else if (theta > 216 && theta <= 234)
	{
		return 16;
	}
	else if (theta > 288 && theta <= 306)
	{
		return 17;
	}
	else if (theta > 54 && theta <= 72)
	{
		return 18;
	}
	else if (theta > 252 && theta <= 270)
	{
		return 19;
	}
	else if (theta > 90 && theta <= 108)
	{
		return 20;
	}
	else
	{
		return 0;
	}
}

void PrintCircle(int radius, int offset)
{
	for (int theta = 0; theta < CIRCLE; theta++)
	{
		int x = 2 * (radius * (cos(ToRadian(theta)) + 1) + offset);
		int y = radius * (1 - sin(ToRadian(theta))) + offset;
		gotoxy(x, y);
		std::cout << '.';
	}
}

// prints radii of circles: to make boundaries between arcs 
void PrintRadius(int radius, int radiusStart, int radiusEnd, int theta, int offset)
{
	for (int r = radiusStart; r < radiusEnd; r++)
	{
		int x = 2 * (radius + r * cos(ToRadian(theta)) + offset);
		int y = radius - r * sin(ToRadian(theta)) + offset;
		gotoxy(x, y);
		std::cout << '.';
	}
}

// prints the score numbers outside the board
void PrintArcNumber(int radius, int theta, int offset, int padding)
{
	int x = 2 * (radius + (radius + padding) * cos(ToRadian(theta)) + offset);
	int y = radius - (radius + padding) * sin(ToRadian(theta)) + offset;
	gotoxy(x, y);
	std::cout << GetArcScore(theta);
}

// prints the actual board
void PrintDartBoard(int radius, int offset)
{
	PrintCircle(radius, offset);
	PrintCircle(radius - 3, offset + 3);

	// inner circle with triple
	PrintCircle(radius / 2, offset + radius / 2);
	PrintCircle(radius / 2 - 3, offset + radius / 2 + 3);

	// center circles
	PrintCircle(radius / 5, offset + radius - radius / 5);
	PrintCircle(radius / 10, offset + radius - radius / 10);

	// section radii
	for (int i = 0; i < 20; i++)
	{
		PrintRadius(radius, radius / 5, radius, i * 18, offset);
	}

	// arc numbers
	for (int i = 0; i < 20; i++)
	{
		PrintArcNumber(radius, i * 18 + 9, offset);
	}
	g_printHeight = 2 * (radius + offset);
	gotoxy(0, g_printHeight);
}
/*
	get the arc angle according to the actual dart board mapping
*/
int GetArcAngle(int choice)
{
	switch (choice)
	{
	case 1:
		return 72;
		break;
	case 2:
		return 306;
		break;
	case 3:
		return 270;
		break;
	case 4:
		return 36;
		break;
	case 5:
		return 108;
		break;
	case 6:
		return 0;
		break;
	case 7:
		return 234;
		break;
	case 8:
		return 198;
		break;
	case 9:
		return 144;
		break;
	case 10:
		return 342;
		break;
	case 11:
		return 180;
		break;
	case 12:
		return 126;
		break;
	case 13:
		return 18;
		break;
	case 14:
		return 162;
		break;
	case 15:
		return 324;
		break;
	case 16:
		return 216;
		break;
	case 17:
		return 288;
		break;
	case 18:
		return 54;
		break;
	case 19:
		return 252;
		break;
	case 20:
		return 90;
		break;
	}
}

// manual aiming
SAimBoundaries& AimDart(int radius)
{
	int choice = 0;
	SAimBoundaries temp;
	std::cout << "Aim the Dart : ";
	NewLine();
	do
	{
		std::cout << "\t1. Inner Center";
		NewLine();
		std::cout << "\t2. Outer Center";
		NewLine();
		std::cout << "\t3. Number Arcs";
		NewLine();
		std::cout << "Your Choice : ";
		std::cin >> choice;
	} while (!(choice >= 1 && choice <= 3));
	switch (choice)
	{
	case 1:
		temp.radiusStart = 0;
		temp.radiusEnd = radius / 10;
		temp.thetaStart = 0;
		temp.thetaEnd = 360;
		break;
	case 2:
		temp.radiusStart = radius / 10;
		temp.radiusEnd = radius / 5;
		temp.thetaStart = 0;
		temp.thetaEnd = 360;
		break;
	case 3:
		int numberChoice = 0;
		std::cout << "\nNumebr Arcs: ";
		NewLine();
		do
		{
			std::cout << "\tEnter the Arc Number : ";
			std::cin >> numberChoice;
		} while (!(numberChoice >= 1 && numberChoice <= 20));

		temp.thetaStart = GetArcAngle(numberChoice);
		temp.thetaEnd = temp.thetaStart + 18;

		int sectionChoice = 0;
		do
		{
			std::cout << "\tEnter the Arc Section : ";
			NewLine();
			std::cout << "\t\t1. Double";
			NewLine();
			std::cout << "\t\t2. Outer Single";
			NewLine();
			std::cout << "\t\t3. Triple";
			NewLine();
			std::cout << "\t\t4. Inner Single";
			NewLine();
			std::cout << "\tYour Choice : ";
			std::cin >> sectionChoice;
		} while (!(sectionChoice >= 1 && sectionChoice <= 4));

		switch (sectionChoice)
		{
		case 1: // double
			temp.radiusEnd = radius;
			temp.radiusStart = temp.radiusEnd - 3;
			break;
		case 2: //  Outer Single
			temp.radiusEnd = radius - 3;
			temp.radiusStart = radius / 2;
			break;
		case 3: // triple
			temp.radiusEnd = radius / 2;
			temp.radiusStart = temp.radiusEnd - 3;
			break;
		case 4: // Inner Single
			temp.radiusEnd = radius / 2 - 3;
			temp.radiusStart = radius / 5;
			break;
		}
	}
	std::cout << "Throwing Dart";
	for (int i = 1; i <= 3; i++)
	{
		std::cout << ".";
		Sleep(1000);
	}
	NewLine();
	NewLine();
	return temp;
}

// gets the dart position
SDartPosition GetDartPosition(int radius, bool isRandom, int windFactor)
{
	srand(time(0));
	SDartPosition currentDartPosition;
	if (isRandom)
	{
		// automatic aiming
		std::cout << "Press Any key to Throw a Dart --> ";
		NewLine();

		system("pause>nul");
		std::cout << "Throwing Dart";
		for (int i = 1; i <= 3; i++)
		{
			std::cout << ".";
			Sleep(1000);
		}
		NewLine();
		NewLine();

		currentDartPosition.radiusOfDart = rand() % (radius - 1) + 1;
		// this is to make sure dart doesn't land on edge of any arc
		do
		{
			currentDartPosition.thetaOfDart = rand() % (CIRCLE - 1) + 1;
		} while (currentDartPosition.thetaOfDart % 18 == 0);
	}
	else
	{
		SAimBoundaries aim = AimDart(radius);
		currentDartPosition.radiusOfDart = aim.radiusStart + rand() % (aim.radiusEnd - aim.radiusStart - 1) + 1;
		currentDartPosition.thetaOfDart = aim.thetaStart + rand() % (aim.thetaEnd - aim.thetaStart - 1) + 1;
	}

	if (windFactor)
	{
		currentDartPosition = WindAffectedPosition(currentDartPosition, windFactor);
	}


	return currentDartPosition;
}

// get the wind affected position if there is any
SDartPosition WindAffectedPosition(SDartPosition& currentDartPosition, int windFactor)
{
	SDartPosition finalDartPosition;

	// formula to get radius after wind is incorporated
	double base = currentDartPosition.radiusOfDart * cos(ToRadian(currentDartPosition.thetaOfDart)) + windFactor;
	double height = currentDartPosition.radiusOfDart * sin(ToRadian(currentDartPosition.thetaOfDart));

	finalDartPosition.radiusOfDart = (int)sqrt(base * base + height * height);

	// formula to get theta after wind is incorporated
	if (currentDartPosition.thetaOfDart >= 0 && currentDartPosition.thetaOfDart <= 90)
	{
		finalDartPosition.thetaOfDart = atan(height / base) * 180 / PI;
	}
	else if (currentDartPosition.thetaOfDart > 90 && currentDartPosition.thetaOfDart <= 270)
	{
		finalDartPosition.thetaOfDart = atan(height / base) * 180 / PI + 180;
	}
	else if (currentDartPosition.thetaOfDart > 270 && currentDartPosition.thetaOfDart <= 360)
	{
		finalDartPosition.thetaOfDart = atan(height / base) * 180 / PI + 360;
	}
	return finalDartPosition;
}

// get the score according to the dart position
int GetScore(SDartPosition& dartPosition, int radius)
{
	if (dartPosition.radiusOfDart >= 0 && dartPosition.radiusOfDart <= radius / 10)
	{
		return 50;
	}
	else if (dartPosition.radiusOfDart > radius / 10 && dartPosition.radiusOfDart <= radius / 5)
	{
		return 25;
	}
	else if (dartPosition.radiusOfDart > radius / 5 && dartPosition.radiusOfDart <= (radius / 2 - 3))
	{
		return GetArcScore(dartPosition.thetaOfDart);
	}
	else if (dartPosition.radiusOfDart > (radius / 2 - 3) && dartPosition.radiusOfDart <= radius / 2)
	{
		return 3 * GetArcScore(dartPosition.thetaOfDart);
	}
	else if (dartPosition.radiusOfDart > radius / 2 && dartPosition.radiusOfDart <= (radius - 3))
	{
		return GetArcScore(dartPosition.thetaOfDart);
	}
	else if (dartPosition.radiusOfDart > (radius - 3) && dartPosition.radiusOfDart <= radius)
	{
		return 2 * GetArcScore(dartPosition.thetaOfDart);
	}
	else
	{
		return 0;
	}
}

// checks if the dart is landed on double
bool IsDouble(SDartPosition& dartPosition, int radius)
{
	// 50 point circle
	if (dartPosition.radiusOfDart >= 0 && dartPosition.radiusOfDart <= radius / 10)
	{
		return true;
	}
	// Double section
	else if (dartPosition.radiusOfDart > (radius - 3) && dartPosition.radiusOfDart <= radius)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// throws the dart to the dart position
void ThrowDart(SDartPosition& dartPosition, int radius, int offset)
{
	int x = 2 * (radius + dartPosition.radiusOfDart * cos(ToRadian(dartPosition.thetaOfDart)) + offset);
	int y = radius - dartPosition.radiusOfDart * sin(ToRadian(dartPosition.thetaOfDart)) + offset;
	gotoxy(x, y);
	// adds a sound when dart is thrown
	std::cout << "\a";
	std::cout << 'X';

	// now g_printHeight is useful to get back to the position where we left of while printing
	gotoxy(0, g_printHeight);
}