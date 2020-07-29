///////////////////////////////////////////////////////////////////////
// Workfile: PositionGameConstants.h
// Author: Christoph Dalpiaz
// Date: 17.07.2020
// Description: constants for PositionGame module
// Remarks: -
// Revision: 0
///////////////////////////////////////////////////////////////////////

#ifndef POSITIONGAMECONSTANTS_H
#define POSITIONGAMECONSTANTS_H

#include <string>		//include std::string
#include <array>		//include std::array

namespace GameConstants {
	//dimensions of map of the game
	size_t const NoLines = 20;
	size_t const NoColumns = 37;

	//winning position needs number, X and Y coordinates
	size_t const PosData = 3;

	//characters representing surroundings
	char const GroundChar = '-';		
	char const BorderChar = '#';
	char const WallChar = '\"';
	char const TreeChar = '+';
	char const WaterChar = '~';
	char const Space = 32;  //Ascii space

	size_t const NoElements = 3;

	//control keys for playing
	char const MoveUp = 'w';
	char const MoveDown = 's';
	char const MoveLeft = 'a';
	char const MoveRight = 'd';
	char const Escape = 27;

	//directory from which maps become random selected
	std::string const MapDirectory = "C://maps//";

	//instructions for the player
	std::string const Introduction = "You are somewhere on this map. Move with w,a,s,d and press escape if you know where you started!";
	std::string const NoWay = "There is no way!";
	std::string const WallText = "You are standing in front of a wall.";
	std::string const WaterText = "You are standing in front of a lake.";
	std::string const TreeText = "You are standing in front of a tree.";
	std::string const AskPosition = "On which position did you start?";
	std::string const WinningText = "You got the position!";
	std::string const LoosingText = "Oh no, position was ";


	//error texts
	std::string const ReadFileError = "Error opening file for reading!";
	std::string const WriteFileError = "Error opening file for writing!";
	std::string const InputError = "Input Error! Type in a number!";
}

//type for position on map
struct Position {
	size_t winningPos;  //position which has to become guessed
	size_t PosX;
	size_t PosY;
};

typedef std::array<std::string, GameConstants::NoLines> Map;  //container for saving map

#endif