#pragma once

// internal includes
#include "Grid.h"
#include "Dependencies.h"
#include "Rover.h"


class CFlyingRover : public CRover
{

public:
	// constructor
	CFlyingRover(const SRoverData& data, CGrid& grid);
	CFlyingRover(int x, int y, char dir, CGrid& grid);

	// destructor
	~CFlyingRover() = default;

	// overridden function
	void TraverseInstructions() override;
	void GoToNextPosition() override;
	void MoveRover(int offsetY, int offsetX) override;
	void CheckIfBlocked() override;
};

