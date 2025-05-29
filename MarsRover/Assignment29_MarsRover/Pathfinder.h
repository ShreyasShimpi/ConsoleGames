#pragma once

// internal includes
#include "Grid.h"

// external includes
#include <vector>
#include <string>
#include <map>


class CNode
{
public:
	CNode* m_parentGridNode;
	SGridCoordinates m_coordinates;

	float m_distanceFromSource;
	float m_heuristicsFromTarget;
	float m_approximateDistanceToTarget;

public:
	// variable
	bool m_isVisited;

	CNode();
	CNode(int row, int column);

	bool operator < (const CNode& rhs) const // must be const-correct
	{
		return this->m_approximateDistanceToTarget < rhs.m_approximateDistanceToTarget; // ordered on ascending value 
	}

	bool operator > (const CNode& rhs) const // must be const-correct
	{
		return this->m_approximateDistanceToTarget > rhs.m_approximateDistanceToTarget; // ordered on ascending value 
	}
};


class CPathfinder
{
private:

	CGrid* m_grid;
	bool m_pathFound;
	std::vector<SGridCoordinates> m_path;
	std::unordered_map<SGridCoordinates, CNode, CCoordinatesHashFunction> m_nodeMap;
	std::string m_requiredInstructions;
	SRoverData m_roverData;

	// utility functions
	float CalculateHeuristic(SGridCoordinates souce, SGridCoordinates target);
	bool IsDestination(SGridCoordinates current, SGridCoordinates target);
	void CalculateRequiredPath(SGridCoordinates target);

public:
	// constructor
	CPathfinder(SRoverData data, CGrid& grid);
	CPathfinder(int x, int y, char dir, CGrid& grid);

	void GetShortestPath(SGridCoordinates souce, SGridCoordinates target);
	std::string GetInstructions(int targetX, int targetY);
};

