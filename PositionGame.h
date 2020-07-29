///////////////////////////////////////////////////////////////////////
// Workfile: PositionGame.h
// Author: Christoph Dalpiaz
// Date: 17.07.2020
// Description: player has to guess the position
// Remarks: -
// Revision: 0
///////////////////////////////////////////////////////////////////////

#ifndef POSITIONGAME_H
#define POSITIONGAME_H

#include <array>					//include std::array
#include <string>					//include std::string
#include "PositionGameConstants.h"  //include needed constants

//overloaded << operator for Map
std::ostream& operator<<(std::ostream& o, Map const& map);

class PositionGame {
private:
	std::string mFileName;			//file from which map becomes scanned
	Map mMap;						//map on which becomes played
	Position mPos = { 0, 0, 0 };	//position where player has started

	//overloaded << operator for Map
	friend std::ostream& operator<<(std::ostream& o, Map const& map);

	//player has to move, gets hints and press escape to key in position
	void FindPosition();

	//set new position, prints message if position is out of borders
	void ChangePosition(size_t const newX, size_t const newY);

	//selects a random file from dedicated folder
	std::string GetFileName();

public:

	//default Ctor, initializing filename with random file from maps folder
	PositionGame();

	//Ctor with filename as parameter
	explicit PositionGame(std::string const& fileName);

	//scanns the map and prints it to console, throws error text if file cannot be read
	void StartGame();
};

#endif