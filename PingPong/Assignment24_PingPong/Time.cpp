// external includes
#include "Time.h"

CTime::CTime()
{
	m_startTime = std::chrono::high_resolution_clock::now();
	m_endTime = std::chrono::high_resolution_clock::now();
	m_deltaTime = 0.0f;
}

void CTime::Tick()
{
	m_endTime = std::chrono::high_resolution_clock::now();
	// Delta time saves long double in milliseconds
	m_deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(m_endTime - m_startTime).count();
	m_startTime = std::chrono::high_resolution_clock::now();
}