// internal includes
#include "Grid.h"
#include "RoverController.h"
#include "Pathfinder.h"

// external includes
#include <memory>
#include <chrono>
#include <vector>
#include <thread>


void Implementation2()
{
	// implementation 2 : A Star
	//CPathfinder* pathfinder = new CPathfinder(1, 2, 'N', *grid);
	//std::cout << pathfinder->GetInstructions(1, 3);
}

int main()
{
	CRoverController roverConstroller;
	roverConstroller.TraverseRoverInstructions();
	
}