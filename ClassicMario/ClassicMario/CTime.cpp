#include "CTime.h"
#include <cmath>
#include <iostream>

CTime::CTime()
{
	m_frameStartTime = std::chrono::high_resolution_clock::now();
	m_frameStopTime = m_frameStartTime;
	m_justStarted = true;
	m_deltaTimeMicro = std::chrono::microseconds(0);
	m_deltaTimeSeconds = 0;
}

void CTime::Tick()
{
	// time point for the previous frame ending
	m_frameStopTime = std::chrono::high_resolution_clock::now();
	if (m_justStarted)
	{
		// we cannot calculate the delta time during the first frame is running, setting it to '0'
		m_frameStartTime = std::chrono::high_resolution_clock::now();
		m_deltaTimeMicro = std::chrono::microseconds(0);
		m_justStarted = false;
		return;
	}

	m_deltaTimeMicro = std::chrono::duration_cast<std::chrono::microseconds>(m_frameStopTime - m_frameStartTime);

	// starting time of the current frame
	m_frameStartTime = std::chrono::high_resolution_clock::now();

	// converting to seconds
	m_deltaTimeSeconds = float(m_deltaTimeMicro.count()) / std::pow(10, 6);	
}

float CTime::GetFrameTime()
{
	return m_deltaTimeSeconds;
}
