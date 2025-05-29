#include "Rover.h"
// internal includes
#include "RoverController.h"

CRover::CRover(const SRoverData& data, CGrid& grid)
	: m_currentRoverData(data), m_grid(&grid)
{
	m_isBlocked = false;
	m_areInstructionsOver = false;
	m_instructionCounter = 0;
}

CRover::CRover(int x, int y, char dir, CGrid& grid)
	: m_grid(&grid)
{
	m_isBlocked = false;
	m_areInstructionsOver = false;
	m_instructionCounter = 0;

	m_currentRoverData.m_x = x;
	m_currentRoverData.m_y = y;
	m_currentRoverData.m_dir = dir;
}


void CRover::AddInstructions(const std::string& instructions)
{
	m_instructions += instructions;
}

//void CRover::TraverseAllInstructions(const std::string& instructions)
//{
//	// store the new instructions
//	m_instructions += instructions;
//
//	// traverse through the instructions
//	while (m_instructionCounter < m_instructions.length())
//	{
//		GoToNextPosition();
//	}
//}
