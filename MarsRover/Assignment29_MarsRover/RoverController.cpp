// internal includes
#include "RoverController.h"


// Implementation 1 : Iteration 3
CRoverController::CRoverController()
{
}


void CRoverController::TraverseRoverInstructions()
{
	std::cout << "//////////////////////////////////////////////////\n";
	std::cout << "/////////       MARS ROVER PROBLEM     ///////////\n";
	std::cout << "//////////////////////////////////////////////////\n";

	// size of grid
	int sizeX, sizeY;
	std::cout << "\n\nEnter the size of the Grid : ";
	std::cin >> sizeX >> sizeY;
	m_grid = std::make_unique<CGrid>(sizeX, sizeY);

	// populate vector of ground rovers by user input
	for (int count = 1; count <= g_groundRovers; count++)
	{
		// rover data
		SRoverData rover;
		std::cout << "\nEnter Ground Rover " << count << " Data : ";
		std::cin >> rover.m_x >> rover.m_y >> rover.m_dir;
		std::string instructions;
		std::cout << "\nEnter Ground Rover " << count << " Instructions : ";
		std::cin >> instructions;

		m_groundRovers.emplace_back(std::make_unique<CGroundRover>(rover, *m_grid));
		m_groundRovers.back()->AddInstructions(instructions);
	}
	// populate vector of flying rovers by user input
	for (int count = 1; count <= g_flyingRovers; count++)
	{
		// rover data
		SRoverData rover;
		std::cout << "\nEnter Flying Rover " << count << " Data : ";
		std::cin >> rover.m_x >> rover.m_y >> rover.m_dir;
		std::string instructions;
		std::cout << "\nEnter Flying Rover " << count << " Instructions : ";
		std::cin >> instructions;

		m_flyingRovers.emplace_back(std::make_unique<CFlyingRover>(rover, *m_grid));
		m_flyingRovers.back()->AddInstructions(instructions);
	}

	// Used for stopping criteria of instructions.
	// Note: for ground rovers only where collision is taking place
	int blockedRovers = 0;
	int roverWithInstructionsOver = 0;
	int timeCounter = 1;

	/*
		The rover would either be blocked by another rover, not blocked or completed the instructions.
		So the way to stops the instruction traversal for rovers is if blocked rovers and rovers with instructions
		are executed add up to the total rovers.
	*/
	while (!(blockedRovers + roverWithInstructionsOver == g_groundRovers + g_flyingRovers))
	{
		blockedRovers = 0;
		roverWithInstructionsOver = 0;

		// follow the instructions for all the rovers
		std::cout << "Landing +" << timeCounter << " Seconds: \n";
		timeCounter++;

		// traverse ground rovers
		// i = 0 because traversing the vector from starting position
		short count = 0;
		for (count = 0; count < g_groundRovers; count++)
		{
			m_groundRovers[count]->TraverseInstructions();
			std::cout << "Ground Rover " << count + 1 << " : ";
			std::cout << m_groundRovers[count]->GetRoverData();
			std::cout << "\n";
		}
		// traverse flying rovers
		for (count = 0; count < g_flyingRovers; count++)
		{
			m_flyingRovers[count]->TraverseInstructions();
			std::cout << "Flying Rover " << count + 1 << " : ";
			std::cout << m_flyingRovers[count]->GetRoverData();
			std::cout << "\n";
		}
		std::cout << "\n\n";

		/*
			Update the blocked rovers and full executed rovers after every rovers movement is done.
		*/
		for (count = 0; count < g_groundRovers; count++)
		{
			m_groundRovers[count]->CheckIfBlocked();
			if (m_groundRovers[count]->m_isBlocked)
			{
				blockedRovers++;
			}
			else if (m_groundRovers[count]->m_areInstructionsOver)
			{
				roverWithInstructionsOver++;
			}
		}
		for (count = 0; count < g_flyingRovers; count++)
		{
			if (m_flyingRovers[count]->m_areInstructionsOver)
			{
				roverWithInstructionsOver++;
			}
		}

	}

}
