// internal includes
#include "Pathfinder.h"

// external includes
#include <iostream>
#include <queue>
#include <cmath>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////                   GRID NODE                     /////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

CNode::CNode()
{
	m_coordinates = { 0,0 };

	m_distanceFromSource = FLT_MAX;
	m_heuristicsFromTarget = FLT_MAX;
	m_approximateDistanceToTarget = FLT_MAX;
	m_isVisited = false;
	m_parentGridNode = nullptr;
}

CNode::CNode(int row, int column)
	:m_coordinates({ row, column })
{
	m_distanceFromSource = FLT_MAX;
	m_heuristicsFromTarget = FLT_MAX;
	m_approximateDistanceToTarget = FLT_MAX;
	m_isVisited = false;
	m_parentGridNode = nullptr;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////                 UTILITY FUNCTIONS               /////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

// A Utility Function to check whether destination cell has
// been reached or not
float CPathfinder::CalculateHeuristic(SGridCoordinates current, SGridCoordinates target)
{
	return ((float)sqrt((current.m_row - target.m_row) * (current.m_row - target.m_row) + (current.m_column - target.m_column) * (current.m_column - target.m_column)));
}

// A Utility Function to check whether destination cell has
// been reached or not
bool CPathfinder::IsDestination(SGridCoordinates current, SGridCoordinates target)
{
	return (current.m_row == target.m_row && current.m_column == target.m_column);
}


void CPathfinder::CalculateRequiredPath(SGridCoordinates target)
{
	SGridCoordinates currentCoord = target;

	while (!(m_nodeMap[currentCoord].m_parentGridNode == nullptr))
	{
		m_path.emplace_back(currentCoord);
		currentCoord = m_nodeMap[currentCoord].m_parentGridNode->m_coordinates;
	}

	//DEBUG PATH
	/*while (!m_path.empty())
	{
		SGridCoordinates coord = m_path.back();
		m_path.pop();
		printf("-> (%d,%d) ", coord.m_row, coord.m_column);
	}
	std::cout << "\n";
	*/

	return;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////                   PATH FINDER                   /////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

CPathfinder::CPathfinder(SRoverData data, CGrid& grid)
	: m_roverData(data), m_grid(&grid)
{
	m_pathFound = false;
}

CPathfinder::CPathfinder(int x, int y, char dir, CGrid& grid)
	: m_grid(&grid)
{
	m_roverData.m_x = x;
	m_roverData.m_y = y;
	m_roverData.m_dir = dir;
	m_pathFound = false;
}

void CPathfinder::GetShortestPath(SGridCoordinates souce, SGridCoordinates target)
{
	// Check if source and target are valid
	if (!m_grid->IsWithinGrid(souce) || !m_grid->IsWithinGrid(target))
	{
		m_pathFound = false;
		return;
	}

	// Check if source is at the target
	if (IsDestination(souce, target))
	{
		m_pathFound = true;
		return;
	}


	// construct navigation grid
	m_nodeMap.clear();
	for (int i = 0; i < m_grid->GetRows(); i++)
	{
		for (int j = 0; j < m_grid->GetColumns(); j++)
		{
			m_nodeMap.emplace(SGridCoordinates{ i, j }, CNode(i, j));
		}
	}

	// set source parameters
	m_nodeMap[souce].m_distanceFromSource = 0.0f;
	m_nodeMap[souce].m_heuristicsFromTarget = 0.0f;
	m_nodeMap[souce].m_approximateDistanceToTarget = 0.0f;

	// open list - priority queue
	std::priority_queue<CNode, std::vector<CNode>, std::greater<CNode>> openNodesPQueue;
	openNodesPQueue.emplace(m_nodeMap[souce]);
	
	while (!openNodesPQueue.empty())
	{
		CNode currentNode = openNodesPQueue.top();

		int i = currentNode.m_coordinates.m_row;
		int j = currentNode.m_coordinates.m_column;

		// mark visited
		m_nodeMap[currentNode.m_coordinates].m_isVisited = true;

		// Remove this vertex from the open list
		openNodesPQueue.pop();

		// To store the 'g', 'h' and 'f' of the 8 successors
		float distanceFromSourceNew;
		float heuristiclFromTargetNew;
		float approximateDistanceToTargetNew;

		//  ----------------------- EAST ---------------------------
		// Only process this cell if this is a valid one
		if (m_grid->IsWithinGrid(i, j + 1))
		{
			SGridCoordinates tempEastCoord = { i, j + 1 };
			// If the destination cell is the same as the current successor
			if (IsDestination(tempEastCoord, target))
			{
				// Set the Parent of the destination cell
				m_nodeMap[tempEastCoord].m_parentGridNode = &m_nodeMap[currentNode.m_coordinates];
				CalculateRequiredPath(target);
				m_pathFound = true;
				return;
			}

			// If the successor is already on the closed, list or if it is blocked, then ignore it, Else do the following
			// TO DO for blocked
			else if (!m_nodeMap[tempEastCoord].m_isVisited)
			{
				distanceFromSourceNew = currentNode.m_distanceFromSource + 1.0f;
				heuristiclFromTargetNew = CalculateHeuristic(tempEastCoord, target);
				approximateDistanceToTargetNew = distanceFromSourceNew + heuristiclFromTargetNew;

				if (m_nodeMap[tempEastCoord].m_approximateDistanceToTarget == FLT_MAX ||
					m_nodeMap[tempEastCoord].m_approximateDistanceToTarget > approximateDistanceToTargetNew)
				{
					// Update the details of this cell
					m_nodeMap[tempEastCoord].m_distanceFromSource = distanceFromSourceNew;
					m_nodeMap[tempEastCoord].m_heuristicsFromTarget = heuristiclFromTargetNew;
					m_nodeMap[tempEastCoord].m_approximateDistanceToTarget = approximateDistanceToTargetNew;

					m_nodeMap[tempEastCoord].m_parentGridNode = &m_nodeMap[currentNode.m_coordinates];

					openNodesPQueue.emplace(m_nodeMap[tempEastCoord]);
				}
			}
		}

		//  ----------------------- WEST ---------------------------
		// Only process this cell if this is a valid one
		if (m_grid->IsWithinGrid(i, j - 1))
		{
			SGridCoordinates tempWestCoord = { i, j - 1 };
			// If the destination cell is the same as the current successor
			if (IsDestination(tempWestCoord, target))
			{
				// Set the Parent of the destination cell
				m_nodeMap[tempWestCoord].m_parentGridNode = &m_nodeMap[currentNode.m_coordinates];
				CalculateRequiredPath(target);
				m_pathFound = true;
				return;
			}

			// If the successor is already on the closed, list or if it is blocked, then ignore it, Else do the following
			else if (!m_nodeMap[tempWestCoord].m_isVisited)
			{
				distanceFromSourceNew = currentNode.m_distanceFromSource + 1.0f;
				heuristiclFromTargetNew = CalculateHeuristic(tempWestCoord, target);
				approximateDistanceToTargetNew = distanceFromSourceNew + heuristiclFromTargetNew;

				if (m_nodeMap[tempWestCoord].m_approximateDistanceToTarget == FLT_MAX ||
					m_nodeMap[tempWestCoord].m_approximateDistanceToTarget > approximateDistanceToTargetNew)
				{
					// Update the details of this cell
					m_nodeMap[tempWestCoord].m_distanceFromSource = distanceFromSourceNew;
					m_nodeMap[tempWestCoord].m_heuristicsFromTarget = heuristiclFromTargetNew;
					m_nodeMap[tempWestCoord].m_approximateDistanceToTarget = approximateDistanceToTargetNew;

					m_nodeMap[tempWestCoord].m_parentGridNode = &m_nodeMap[currentNode.m_coordinates];

					openNodesPQueue.emplace(m_nodeMap[tempWestCoord]);
				}
			}
		}

		//  ----------------------- NORTH ---------------------------
		// Only process this cell if this is a valid one
		if (m_grid->IsWithinGrid(i - 1, j))
		{
			SGridCoordinates tempNorthCoord = { i - 1, j };
			// If the destination cell is the same as the current successor
			if (IsDestination(tempNorthCoord, target))
			{
				// Set the Parent of the destination cell
				m_nodeMap[tempNorthCoord].m_parentGridNode = &m_nodeMap[currentNode.m_coordinates];
				CalculateRequiredPath(target);
				m_pathFound = true;
				return;
			}

			// If the successor is already on the closed, list or if it is blocked, then ignore it, Else do the following
			else if (!m_nodeMap[tempNorthCoord].m_isVisited)
			{
				distanceFromSourceNew = currentNode.m_distanceFromSource + 1.0f;
				heuristiclFromTargetNew = CalculateHeuristic(tempNorthCoord, target);
				approximateDistanceToTargetNew = distanceFromSourceNew + heuristiclFromTargetNew;

				if (m_nodeMap[tempNorthCoord].m_approximateDistanceToTarget == FLT_MAX ||
					m_nodeMap[tempNorthCoord].m_approximateDistanceToTarget > approximateDistanceToTargetNew)
				{
					// Update the details of this cell
					m_nodeMap[tempNorthCoord].m_distanceFromSource = distanceFromSourceNew;
					m_nodeMap[tempNorthCoord].m_heuristicsFromTarget = heuristiclFromTargetNew;
					m_nodeMap[tempNorthCoord].m_approximateDistanceToTarget = approximateDistanceToTargetNew;

					m_nodeMap[tempNorthCoord].m_parentGridNode = &m_nodeMap[currentNode.m_coordinates];

					openNodesPQueue.emplace(m_nodeMap[tempNorthCoord]);
				}
			}
		}

		//  ----------------------- SOUTH ---------------------------
		// Only process this cell if this is a valid one
		if (m_grid->IsWithinGrid(i + 1, j))
		{
			SGridCoordinates tempSouthCoord = { i + 1, j };
			// If the destination cell is the same as the current successor
			if (IsDestination(tempSouthCoord, target))
			{
				// Set the Parent of the destination cell
				m_nodeMap[tempSouthCoord].m_parentGridNode = &m_nodeMap[currentNode.m_coordinates];
				CalculateRequiredPath(target);
				m_pathFound = true;
				return;

			}

			// If the successor is already on the closed, list or if it is blocked, then ignore it, Else do the following
			else if (!m_nodeMap[tempSouthCoord].m_isVisited)
			{
				distanceFromSourceNew = currentNode.m_distanceFromSource + 1.0f;
				heuristiclFromTargetNew = CalculateHeuristic(tempSouthCoord, target);
				approximateDistanceToTargetNew = distanceFromSourceNew + heuristiclFromTargetNew;

				if (m_nodeMap[tempSouthCoord].m_approximateDistanceToTarget == FLT_MAX ||
					m_nodeMap[tempSouthCoord].m_approximateDistanceToTarget > approximateDistanceToTargetNew)
				{
					// Update the details of this cell
					m_nodeMap[tempSouthCoord].m_distanceFromSource = distanceFromSourceNew;
					m_nodeMap[tempSouthCoord].m_heuristicsFromTarget = heuristiclFromTargetNew;
					m_nodeMap[tempSouthCoord].m_approximateDistanceToTarget = approximateDistanceToTargetNew;

					m_nodeMap[tempSouthCoord].m_parentGridNode = &m_nodeMap[currentNode.m_coordinates];

					openNodesPQueue.emplace(m_nodeMap[tempSouthCoord]);
				}
			}
		}
	}
	m_pathFound = false;
	return;
}

std::string CPathfinder::GetInstructions(int targetX, int targetY)
{
	m_requiredInstructions.clear();

	SGridCoordinates source = { m_roverData.m_x, m_roverData.m_y };
	SGridCoordinates target = { targetX, targetY };

	GetShortestPath(source, target);

	if (m_pathFound)
	{
		// traverse through path coordinates
		SGridCoordinates tempCoord = {m_roverData.m_y, m_roverData.m_x};
		char currentDirection = m_roverData.m_dir;

		// reverse traversal as path beginning is stored last
		for (auto pathCoord = m_path.rbegin(); pathCoord != m_path.rend(); ++pathCoord)
		{
			// North
			if (tempCoord.m_row + 1 == pathCoord->m_column && tempCoord.m_column == pathCoord->m_row)
			{
				tempCoord.m_row = pathCoord->m_column;
				tempCoord.m_column = pathCoord->m_row;

				switch (currentDirection)
				{
				case 'N':
					m_requiredInstructions += "M";
					break;
				case 'E':
					m_requiredInstructions += "LM";
					currentDirection = 'N';
					break;
				case 'W':
					m_requiredInstructions += "RM";
					currentDirection = 'N';
					break;
				case 'S':
					m_requiredInstructions += "LLM";
					currentDirection = 'N';
					break;
				default:
					break;
				}
			}
			// South
			else if (tempCoord.m_row - 1 == pathCoord->m_column && tempCoord.m_column == pathCoord->m_row)
			{
				tempCoord.m_row = pathCoord->m_column;
				tempCoord.m_column = pathCoord->m_row;

				switch (currentDirection)
				{
				case 'S':
					m_requiredInstructions += "M";
				case 'E':
					m_requiredInstructions += "RM";
					currentDirection = 'S';
					break;
				case 'W':
					m_requiredInstructions += "LM";
					currentDirection = 'S';
					break;
				case 'N':
					m_requiredInstructions += "LLM";
					currentDirection = 'S';
					break;
				default:
					break;
				}
			}
			// East
			else if (tempCoord.m_row == pathCoord->m_column && tempCoord.m_column  + 1 == pathCoord->m_row)
			{
				tempCoord.m_row = pathCoord->m_column;
				tempCoord.m_column = pathCoord->m_row;

				switch (currentDirection)
				{
				case 'E':
					m_requiredInstructions += "M";
					break;
				case 'N':
					m_requiredInstructions += "RM";
					currentDirection = 'E';
					break;
				case 'S':
					m_requiredInstructions += "LM";
					currentDirection = 'E';
					break;
				case 'W':
					m_requiredInstructions += "LLM";
					currentDirection = 'E';
					break;
				default:
					break;
				}
			}
			// West
			else if (tempCoord.m_row  == pathCoord->m_column && tempCoord.m_column - 1 == pathCoord->m_row)
			{
				tempCoord.m_row = pathCoord->m_column;
				tempCoord.m_column = pathCoord->m_row;

				switch (currentDirection)
				{
				case 'W':
					m_requiredInstructions += "M";
					break;
				case 'N':
					m_requiredInstructions += "LM";
					currentDirection = 'W';
					break;
				case 'S':
					m_requiredInstructions += "RM";
					currentDirection = 'W';
					break;
				case 'E':
					m_requiredInstructions += "LLM";
					currentDirection = 'W';
					break;
				default:
					break;
				}
			}
		}
		return m_requiredInstructions;
	}
	else 
	{
		std::cout << "No valid path to the destination!\n";
		return m_requiredInstructions;
	}
}


