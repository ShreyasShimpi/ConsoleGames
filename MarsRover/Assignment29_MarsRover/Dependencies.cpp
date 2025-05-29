#include "Dependencies.h"

std::ostream& operator << (std::ostream& os, const SRoverData& roverData)
{
	os << roverData.m_x << ' ' << roverData.m_y << ' ' << roverData.m_dir;
	return os;
}