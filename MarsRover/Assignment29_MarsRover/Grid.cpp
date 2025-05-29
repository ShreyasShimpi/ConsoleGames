#include "Grid.h"

CGrid::CGrid(int rows, int columns)
	:m_rows(rows + 1), m_columns(columns + 1)
{
	// construct navigation grid
	for (int i = 0; i < m_rows; i++)
	{
		for (int j = 0; j < m_columns; j++)
		{
			m_obstacles.emplace(std::make_pair<SGridCoordinates, bool>({ i, j }, false));
		}
	}
}

void CGrid::AddObstacle(int row, int column)
{
	// if input coordinates are valid, then add obstacle 
	if(row >= 0 && row < m_rows && column >= 0 && column < m_columns)
	{
		m_obstacles.at({ row, column }) = true;
	}
	return;
}

void CGrid::RemoveObstacle(int row, int column)
{
	// if input coordinates are valid, then remove obstacle 
	if (row >= 0 && row < m_rows && column >= 0 && column < m_columns)
	{
		m_obstacles.at({ row, column }) = false;
	}
	return;
}

bool CGrid::IsObstacle(int row, int column)
{
	// if input coordinates are valid, then remove obstacle 
	if (row >= 0 && row < m_rows && column >= 0 && column < m_columns)
	{
		return m_obstacles.at({ row, column });
	}
	
}

bool CGrid::IsWithinGrid(int row, int column)
{
	return row >= 0 && row < m_rows && column >= 0 && column < m_columns;
}

bool CGrid::IsWithinGrid(SGridCoordinates gridCoord)
{
	return gridCoord.m_row >= 0 && gridCoord.m_row < m_rows && gridCoord.m_column >= 0 && gridCoord.m_column < m_columns;
}
