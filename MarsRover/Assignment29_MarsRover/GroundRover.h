#pragma once

// internal includes
#include "Grid.h"
#include "Dependencies.h"
#include "Rover.h"


class CGroundRover : public CRover
{

public:
	// constructor
	CGroundRover(const SRoverData& data, CGrid& grid);
	CGroundRover(int x, int y, char dir, CGrid& grid);

	// destructor
	~CGroundRover() = default;

	// overridden function
	void TraverseInstructions() override;
	void GoToNextPosition() override;
	void MoveRover(int offsetY, int offsetX) override;
	void CheckIfBlocked() override;
};

