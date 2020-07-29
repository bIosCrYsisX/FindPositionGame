///////////////////////////////////////////////////////////////////////
// Workfile: MapGenerator.cpp
// Author: Christoph Dalpiaz
// Date: 19.07.2020
// Description: generate maps for PositionGame
// Remarks: -
// Revision: 0
///////////////////////////////////////////////////////////////////////

#include <fstream>					//include filestream library
#include <cstdlib>					//needed for pseudo random number generator
#include <time.h>					//needed for seed of random numbers
#include <Windows.h>				//needed for Sleep()
#include <vector>					//include std::vector
#include "MapGenerator.h"			//include module header
#include "MapGeneratorConstants.h"	//include constants for generator

#include <iostream>
#include "PositionGame.h"

using namespace std;				//resolve std namespace
using namespace GameConstants;		//resolve namespace for constants
using namespace GeneratorConstants; 

//creates a number of trees on map
void MapGenerator::CreateTree(size_t const noTrees) {
	for (size_t i = 0; i < noTrees; i++) {  //build trees
		size_t posX = 0;
		size_t posY = 0;

		FindOpenPosition(posX, posY);  

		while (mMap[posY][posX] != GroundChar || IsEntry(posX, posY)) {   //if position is not open or an entry, find a new one
			FindOpenPosition(posX, posY);
		}
		mMap[posY][posX] = TreeChar;  //build tree
	}
}

//creates number of waters on map
void MapGenerator::CreateWater(size_t const noWaters) {
	for (size_t k = 0; k < noWaters; k++) {  //build all waters
		size_t posX = 0;
		size_t posY = 0;
		FindOpenPosition(posX, posY);

		size_t waterWidth = rand() % (MaxWaterWidth - MinWaterWidth) + MinWaterWidth;  //calculate random parameters
		size_t const waterArea = rand() % (MaxWaterArea - MinWaterArea) + MinWaterArea;
		size_t waterHeight = waterArea / waterWidth;

		//if the height would be too big to reach the area
		if (waterHeight < MinWaterWidth) {	//make it minimum size and calculate new width
			waterHeight = MinWaterWidth;
			waterWidth = waterArea / waterHeight;
		}

		while (!EnoughSpace(posX, posY, waterHeight, waterWidth)) { //check if there is enough space
			FindOpenPosition(posX, posY);
		}

		for (size_t i = posY; i < posY + waterHeight; i++) {  //build the water surface
			for (size_t j = posX; j < posX + waterWidth; j++) {
				mMap[i][j] = WaterChar;
			}
			if (i != posY && i != posY + waterHeight && rand() % PropabilityWaterRound == 0) { //there is a chance that water gets rounded
				if (posX + waterWidth < NoColumns - 1) {  //check if there is space to the right
					mMap[i][posX + waterWidth] = WaterChar;
				}
				if (posX > 1) {  //check if there is also space to the left
					mMap[i][posX - 1] = WaterChar;
				}
			}
		}
	}
}

//creates number of buildings on map
void MapGenerator::CreateBuilding(size_t const noBuildings) {
	for (size_t i = 0; i < noBuildings; i++) {
		size_t posX = 0;
		size_t posY = 0; 
		size_t const MaxPositionTries = 20;  //maximum number of tries to find position for building

		size_t BuildWidth = rand() % (MaxBuildingWidth - MinBuildingWidth) + MinBuildingWidth;   //calculate random values for building
		size_t const BuildArea = rand() % (MaxBuildingArea - MinBuildingArea) + MinBuildingArea;
		size_t BuildHeight = BuildArea / BuildWidth;

		//if the height would be too big to reach the area
		if (BuildHeight < MinBuildingWidth) {	//make it minimum size and calculate new width
			BuildHeight = MinBuildingWidth;
			BuildWidth = BuildArea / BuildHeight;
		}

		double ratio = 1.0 * BuildWidth / BuildHeight;  //ratio between building sides
		
		//if one side is too long, just build a minimum sized building
		if (ratio > BuildingRatio || ratio < 1.0 / BuildingRatio) {
			BuildWidth = MinBuildingWidth;
			BuildHeight = MinBuildingWidth;
		}

		FindOpenPosition(posX, posY);  //find an open position for the building
		size_t noTries = 0;				    //count number of tries to find position
		
		while (!EnoughSpace(posX, posY, BuildHeight, BuildWidth) && noTries < MaxPositionTries) { //check if there is enough space
			FindOpenPosition(posX, posY);
			noTries++;
		}
		if (noTries != MaxPositionTries) {  //check if there has been found a position
			for (size_t i = posX; i < posX + BuildWidth; i++) {  //build vertical walls
				mMap[posY][i] = WallChar;
				mMap[posY + BuildHeight - 1][i] = WallChar;
			}
			for (size_t i = posY; i < posY + BuildHeight; i++) {  //build horizontal walls
				mMap[i][posX] = WallChar;
				mMap[i][posX + BuildWidth - 1] = WallChar;
			}

			CreateEntry(posX, posY, BuildHeight, BuildWidth); 	//create an entry to building
		}
	}
}

//creates an entry to building
void MapGenerator::CreateEntry(size_t const posX, size_t const posY, size_t const height, size_t const width) {
	if (rand() % 2 == 0) {  //50% chance that entry is on horizontal
		size_t wallX = rand() % (width - 2) + 1;  //find random position for entry
		if (rand() % 2 == 0 && posY > 1) {  //25% chance that entry is on upper wall
			if (mMap[posY - 1][posX + wallX] != GroundChar) {  //if entry is not open
				CreateEntry(posX, posY, height, width);		   //try to create another entry
			}
			else {	//otherwise make the entry
				mMap[posY][posX + wallX] = GroundChar;
			}
		}
		else {  //otherwise lower
			if (mMap[posY + 1][posX + wallX] != GroundChar) {
				CreateEntry(posX, posY, height, width);
			}
			else {
				mMap[posY + height - 1][posX + wallX] = GroundChar;
			}
		}
	}
	else {			//otherwise vertical wall
		size_t wallY = rand() % (height - 2) + 1;
		if (rand() % 2 == 0 && posX > 1) {  //25% chance that the entry is on left wall
			if (mMap[posY + wallY][posX - 1] != GroundChar) {
				CreateEntry(posX, posY, height, width);
			}
			else {
				mMap[posY + rand() % (height - 2) + 1][posX] = GroundChar;
			}
		}
		else {		//otherwise right wall
			if (mMap[posY + wallY][posX + 1] != GroundChar) {
				CreateEntry(posX, posY, height, width);
			}
			else {
				mMap[posY + rand() % (height - 2) + 1][posX + width - 1] = GroundChar;
			}
		}
	}
}

//returns true if there is already a position neighboured
bool MapGenerator::NeighbourPosition(size_t const posX, size_t const posY) const {
	if (posX > 0 && posX < NoColumns - 1 && posY > 0 && posY < NoLines - 1) {
		return IsPosition(posX - 1, posY - 1) ||  //if there is a neighboured position, return true, otherwise false
			   IsPosition(posX, posY - 1) ||
			   IsPosition(posX + 1, posY - 1) ||
			   IsPosition(posX - 1, posY) ||
			   IsPosition(posX + 1, posY) ||
			   IsPosition(posX - 1, posY + 1) ||
			   IsPosition(posX, posY + 1) ||
			   IsPosition(posX + 1, posY + 1);

	}
	return false;	//position is on border, cannot be called with
}

//returns true if there is a position (f.e. '1', '2', ...)
bool MapGenerator::IsPosition(size_t const posX, size_t const posY) const {
	return mMap[posY][posX] >= '0' && mMap[posY][posX] <= '9';
}


//checks if there is enough space for the given parameters
bool MapGenerator::EnoughSpace(size_t const posX, size_t const posY, size_t const height, size_t const width) const {
	//check if there is space for the object
	for (size_t i = posY; i < posY + height; i++) {  
		for (size_t j = posX; j < posX + width; j++) {
			if (mMap[i][j] != GroundChar) {  //if anything is in this area, there is no space
				return false;
			}
		}
	}

	return true;   //enough space for the wall
}

//returns true if position is an entry of building
bool MapGenerator::IsEntry(size_t const posX, size_t const posY) const {
	if (posX > 0 && posX < NoColumns - 1 && posY > 0 && posY < NoLines - 1) {
		return (mMap[posY][posX - 1] == WallChar && mMap[posY][posX + 1] == WallChar) ||   //check if position is between two wall characters
			   (mMap[posY - 1][posX] == WallChar && mMap[posY + 1][posX] == WallChar);
	}
	return false;	//position is on border, cannot be an entry
}

//returns an ascii char representing the integer value (0 to 9) f.e.: 1 -> '1'
char MapGenerator::IntToAscii(int const val) const {
	return val + '0';
}

//creates positions on map and returns string for winning position
string MapGenerator::CreatePositions(size_t const noPositions) {
	std::vector<Position> positions;  //vector for saving generated positions
	for (size_t i = 1; i <= noPositions; i++) {

		positions.push_back(Position{ i, 0, 0 });
		size_t posX = 0;
		size_t posY = 0;

		FindOpenPosition(posX, posY);

		while (NeighbourPosition(posX, posY)) {  //find a position without a neighboured position
			FindOpenPosition(posX, posY);
		}

		positions[positions.size() - 1].PosX = posX;
		positions[positions.size() - 1].PosY = posY;

		mMap[positions[positions.size() - 1].PosY][positions[positions.size() - 1].PosX] = IntToAscii(i);
	}
	size_t const winPos = rand() % positions.size();

	//return string containing position and coordinates
	return to_string(positions[winPos].winningPos) + " " + to_string(positions[winPos].PosX) + " " + to_string(positions[winPos].PosY);
}

//finds a random open position on map
void MapGenerator::FindOpenPosition(size_t& posX, size_t& posY) const {
	posX = rand() % (NoColumns - 1) + 1;   //get random position on map
	posY = rand() % (NoLines - 1) + 1;

	while (mMap[posY][posX] != GroundChar) {  //check if position is open, if not - find another one
		posX = rand() % (NoColumns - 1) + 1;
		posY = rand() % (NoLines - 1) + 1;
	}
}

//generate the maps and save them to indexed files
void MapGenerator::Generate(std::string const& fileName, size_t const noMaps) {
	for (size_t i = 0; i < noMaps; i++) {
		mMap = InitMap;

		srand(time(nullptr));  //set seed for random numbers

		CreateWater(rand() % (MaxNoWaters - MinNoWaters) + MinNoWaters);
		CreateBuilding(rand() % (MaxNoBuildings + 1));
		CreateTree(rand() % (MaxNoTrees - MinNoTrees) + MinNoTrees);
		string posLine = CreatePositions(rand() % (MaxNoPositions - MinNoPositions) + MinNoPositions);

		ofstream writeFile{ MapDirectory + fileName + to_string(i) + ".txt" };

		if (!writeFile.is_open()) {
			throw WriteFileError;
		}

		writeFile << posLine << endl;

		copy(mMap.cbegin(), mMap.cend(), ostream_iterator<string>{writeFile, "\n"});
		cout << mMap << endl;

		writeFile.close();

		Sleep(1000);
	}
}