#pragma once
#include <chrono>

/*
	Keeps track of the duration of each frame
*/
class CTime
{
private:
	// time points
	std::chrono::high_resolution_clock::time_point m_frameStartTime;
	std::chrono::high_resolution_clock::time_point m_frameStopTime;

	bool m_justStarted;	// flag to check if it calculating for the first frame

	// delta time
	std::chrono::microseconds m_deltaTimeMicro;
	float m_deltaTimeSeconds;

public:
	// Constructor
	CTime();

	// calculates the time taken by the previous frame
	void Tick();

	// return the frame time
	float GetFrameTime();
};