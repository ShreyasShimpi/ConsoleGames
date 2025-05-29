#include "GroundRover.h"

CGroundRover::CGroundRover(const SRoverData& data, CGrid& grid)
	: CRover(data, grid)
{
	m_grid->AddObstacle(m_currentRoverData.m_y, m_currentRoverData.m_x);
}

CGroundRover::CGroundRover(int x, int y, char dir, CGrid& grid)
	: CRover(x, y, dir, grid)
{
	m_grid->AddObstacle(m_currentRoverData.m_y, m_currentRoverData.m_x);
}

/*
	This function will traverse the instructions depending upon the rover type
	ex. for ground rovers its 1, for flying rovers its 2.
*/
void CGroundRover::TraverseInstructions()
{
	short counter = 0;
	do
	{
		GoToNextPosition();
		counter++;
	} while (counter < g_groundRoverIPS);
}

// traverses direction by using instruction string, containing 
// 'L' : turn left
// 'R' : turn Right
// 'M' : move 1 step in the current direction
void CGroundRover::GoToNextPosition()
{

	if (m_instructionCounter < m_instructions.length())
	{
		switch (m_instructions[m_instructionCounter])
		{
			// If the instruction is 'Left',..
		case 'L':
		case 'l':
		{
			// ...,change the direction anticlockwise
			switch (m_currentRoverData.m_dir)
			{
			case 'N':
			case 'n':
				m_currentRoverData.m_dir = 'W';
				break;
			case 'E':
			case 'e':
				m_currentRoverData.m_dir = 'N';
				break;
			case 'S':
			case 's':
				m_currentRoverData.m_dir = 'E';
				break;
			case 'W':
			case 'w':
				m_currentRoverData.m_dir = 'S';
				break;
			default:
				break;
			}

			// increment the instruction counter
			m_instructionCounter++;
		}
		break;
		// else if the instruction is 'Right',..
		case 'R':
		case 'r':
		{
			// ...,change the direction clockwise
			switch (m_currentRoverData.m_dir)
			{
			case 'N':
			case 'n':
				m_currentRoverData.m_dir = 'E';
				break;
			case 'E':
			case 'e':
				m_currentRoverData.m_dir = 'S';
				break;
			case 'S':
			case 's':
				m_currentRoverData.m_dir = 'W';
				break;
			case 'W':
			case 'w':
				m_currentRoverData.m_dir = 'N';
				break;
			default:
				break;
			}

			// increment the instruction counter
			m_instructionCounter++;
		}
		break;
		case 'M':
		case 'm':
		{
			// if,instruction is 'M', move one step ahead in the facing direction
			switch (m_currentRoverData.m_dir)
			{
			case 'N':
				// if path is valid (within the grid size), move the rover
				if (m_grid->IsWithinGrid(m_currentRoverData.m_y + 1, m_currentRoverData.m_x))
				{
					// if next position is not an obstacle then move the rover.
					if (!m_grid->IsObstacle(m_currentRoverData.m_y + 1, m_currentRoverData.m_x))
					{
						MoveRover(1, 0);
					}
				}
				// if its not in the grid, give error and skip the instruction
				else
				{
					std::cout << "Warning: Rover going out of the grid. Instruction skipped.";

					// increment the instruction counter
					m_instructionCounter++;
				}
				break;
			case 'E':
				// if path is valid (within the grid size), move the rover
				if (m_grid->IsWithinGrid(m_currentRoverData.m_y, m_currentRoverData.m_x + 1))
				{
					if (!m_grid->IsObstacle(m_currentRoverData.m_y, m_currentRoverData.m_x + 1))
					{
						MoveRover(0, 1);
					}
				}
				// if its not in the grid, give error and skip the instruction
				else
				{
					std::cout << "Warning: Rover going out of the grid. Instruction skipped.";

					// increment the instruction counter
					m_instructionCounter++;
				}
				break;
			case 'S':
				// if path is valid (within the grid size), move the rover
				if (m_grid->IsWithinGrid(m_currentRoverData.m_y - 1, m_currentRoverData.m_x))
				{
					if (!m_grid->IsObstacle(m_currentRoverData.m_y - 1, m_currentRoverData.m_x))
					{
						MoveRover(-1, 0);
					}
				}
				// if its not in the grid, give error and skip the instruction
				else
				{
					std::cout << "Warning: Rover going out of the grid. Instruction skipped.";

					// increment the instruction counter
					m_instructionCounter++;
				}
				break;
			case 'W':
				// if path is valid (within the grid size), move the rover
				if (m_grid->IsWithinGrid(m_currentRoverData.m_y, m_currentRoverData.m_x - 1))
				{
					if (!m_grid->IsObstacle(m_currentRoverData.m_y, m_currentRoverData.m_x - 1))
					{
						MoveRover(0, -1);
					}
				}
				// if its not in the grid, give error and skip the instruction
				else
				{
					std::cout << "Warning: Rover going out of the grid. Instruction skipped.";

					// increment the instruction counter
					m_instructionCounter++;
				}
				break;
			default:

				break;
			}
		}
		break;
		default:
			std::cout << "Warning : Invalid Instruction '" << m_instructions[m_instructionCounter] << "'. Skipping to next Instruction\n";
			break;
		}

		// if instructions are done,
		if (m_instructionCounter == m_instructions.length())
		{
			m_areInstructionsOver = true;
		}
	}
	return;
}

void CGroundRover::MoveRover(int offsetY, int offsetX)
{
	m_grid->RemoveObstacle(m_currentRoverData.m_y, m_currentRoverData.m_y);

	m_currentRoverData.m_x += offsetX;
	m_currentRoverData.m_y += offsetY;

	m_grid->AddObstacle(m_currentRoverData.m_y, m_currentRoverData.m_x);

	// increment the instruction counter
	m_instructionCounter++;
}

void CGroundRover::CheckIfBlocked()
{
	if (m_instructions[m_instructionCounter] == 'M')
	{
		switch (m_currentRoverData.m_dir)
		{
		case 'N':
		case 'n':
			if (m_grid->IsObstacle(m_currentRoverData.m_y + 1, m_currentRoverData.m_x))
			{
				m_isBlocked = true;
			}
			else
			{
				m_isBlocked = false;
			}
			break;
		case 'E':
		case 'e':
			if (m_grid->IsObstacle(m_currentRoverData.m_y, m_currentRoverData.m_x + 1))
			{
				m_isBlocked = true;
			}
			else
			{
				m_isBlocked = false;
			}
			break;
		case 'S':
		case 's':
			if (m_grid->IsObstacle(m_currentRoverData.m_y - 1, m_currentRoverData.m_x))
			{
				m_isBlocked = true;
			}
			else
			{
				m_isBlocked = false;
			}
			break;
		case 'W':
		case 'w':
			if (m_grid->IsObstacle(m_currentRoverData.m_y, m_currentRoverData.m_x + 1))
			{
				m_isBlocked = true;
			}
			else
			{
				m_isBlocked = false;
			}
			break;
		default:
			break;
		}
	}
}