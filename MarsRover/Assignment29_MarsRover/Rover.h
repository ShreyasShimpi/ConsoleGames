#pragma once

// internal includes
#include "Grid.h"
#include "Dependencies.h"

// external includes
#include <iostream>
#include <vector>

class CRover
{
protected:
	SRoverData m_currentRoverData;
	CGrid* m_grid;

	// for step by step instruction execution
	std::string m_instructions;
	int m_instructionCounter;

public:
	bool m_isBlocked;
	bool m_areInstructionsOver;

	// constructor
	CRover(const SRoverData& data, CGrid& grid);
	CRover(int x, int y, char dir, CGrid& grid);

	// destructor
	~CRover() = default;

	// setter
	void AddInstructions(const std::string& instructions);

	// traverse direction
	inline const SRoverData& GetRoverData() { return m_currentRoverData; };
	//void TraverseAllInstructions(const std::string& instructions);

	// virtual functions
	virtual void TraverseInstructions() = 0;
	virtual void CheckIfBlocked() = 0;
	virtual void GoToNextPosition() = 0;
	virtual void MoveRover(int offsetY, int offsetX) = 0;
};

