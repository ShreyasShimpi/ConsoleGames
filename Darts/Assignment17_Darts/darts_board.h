#pragma once

#define CIRCLE 360
#define PI 3.14159

extern int g_printHeight;

struct SAimBoundaries
{
	int radiusStart;
	int radiusEnd;
	int thetaStart;
	int thetaEnd;
};

struct SDartPosition
{
	int radiusOfDart;
	int thetaOfDart;
};

void NewLine();

void gotoxy(int x, int y);

double ToRadian(int degree);

int GetArcScore(int theta);

void PrintCircle(int radius, int offset = 0);

void PrintRadius(int radius, int radiusStart, int radiusEnd, int theta, int offset = 5);


void PrintArcNumber(int radius, int theta, int offset, int padding = 2);

void PrintDartBoard(int radius, int offset = 5);
/*
	get the arc angle according to the actual dart board mapping
*/
int GetArcAngle(int choice);

SAimBoundaries& AimDart(int radius);

SDartPosition GetDartPosition(int radius, bool isRandom, int windFactor = 0);

SDartPosition WindAffectedPosition(SDartPosition& currentDartPosition, int windFactor = 0);

int GetScore(SDartPosition& dartPosition, int radius);

bool IsDouble(SDartPosition& dartPosition, int radius);

void ThrowDart(SDartPosition& dartPosition, int radius, int offset = 5);

