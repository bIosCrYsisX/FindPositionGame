///////////////////////////////////////////////////////////////////////
// Workfile: MapGenerator.h
// Author: Christoph Dalpiaz
// Date: 19.07.2020
// Description: generate maps for PositionGame
// Remarks: -
// Revision: 0
///////////////////////////////////////////////////////////////////////

#ifndef MAPGENERATOR_H
#define MAPGENERATOR_H

#include <string>		//include std::string
#include <array>		//include std::array
#include "PositionGameConstants.h"

class MapGenerator {
private:

	Map mMap;  //actual generated map
	//creates a number of trees on map
	void CreateTree(size_t const noTrees);

	//creates number of waters on map
	void CreateWater(size_t const noWaters);

	//creates number of buildings on map
	void CreateBuilding(size_t const noBuildings);

	//creates positions on map and returns string for winning position
	std::string CreatePositions(size_t const noPositions);

	//finds a random open position on map
	void FindOpenPosition(size_t& posX, size_t& posY) const;

	//checks if there is enough space for the given parameters
	bool EnoughSpace(size_t const posX, size_t const posY, size_t const height, size_t const width) const;

	//creates an entry to building
	void CreateEntry(size_t const posX, size_t const posY, size_t const height, size_t const width);

	//returns true if there is already a position neighboured
	bool NeighbourPosition(size_t const posX, size_t const posY) const;

	//returns true if there is a position (f.e. '1', '2', ...)
	bool IsPosition(size_t const posX, size_t const posY) const;

	//returns true if position is an entry of building
	bool IsEntry(size_t const posX, size_t const posY) const;

	//returns an ascii char representing the integer value (0 to 9) f.e.: 1 -> '1'
	char IntToAscii(int const val) const;
public:
	//generate the maps and save them to indexed files
	void Generate(std::string const& fileName, size_t const noMaps);
};

#endif