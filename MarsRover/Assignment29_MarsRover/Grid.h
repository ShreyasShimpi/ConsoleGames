#pragma once
// internal includes
#include "Dependencies.h"

// external includes
#include <unordered_map>

class CGrid
{
private:
	int m_rows;
	int m_columns;

	// navigation grid will contain the boolean values, 1 for walkable, 0 for obstacle
	std::unordered_map<SGridCoordinates, bool, CCoordinatesHashFunction> m_obstacles;

public:
	// constructor
	CGrid(int rows, int columns);

	// getters
	inline const int& GetRows() { return m_rows; };
	inline const int& GetColumns() { return m_columns; };
	
	bool IsWithinGrid(int row, int column);
	bool IsWithinGrid(SGridCoordinates gridCoord);

	void AddObstacle(int row, int column);
	void RemoveObstacle(int row, int column);

	bool IsObstacle(int row, int column);
};


