#pragma once

// internal includes
#include "GroundRover.h"
#include "FlyingRover.h"
#include "Dependencies.h"

// external includes
#include <iostream>
#include <vector>


class CRoverController
{
private:
	// creating grid
	std::unique_ptr<CGrid> m_grid;

	std::vector<std::unique_ptr<CGroundRover>> m_groundRovers;
	std::vector<std::unique_ptr<CFlyingRover>> m_flyingRovers;

public:
	// constructor
	CRoverController();

	// all rover instructions are executed here
	void TraverseRoverInstructions();
};


