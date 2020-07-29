///////////////////////////////////////////////////////////////////////
// Workfile: PositionGame.cpp
// Author: Christoph Dalpiaz
// Date: 17.07.2020
// Description: player has to guess the position
// Remarks: -
// Revision: 0
///////////////////////////////////////////////////////////////////////

#include <iostream>					//include IO library
#include <array>					//include std::array
#include <string>					//include std::string
#include <conio.h>					//needed for _getch()
#include <cstdlib>					//needed for pseudo random number generator
#include <time.h>					//needed for seed of random numbers
#include <filesystem>				//needed for reading files contained in folder
#include <fstream>					//include filestream library
#include <sstream>					//include stringstream library
#include "PositionGame.h"			//include module header
#include "PositionGameConstants.h"	//include needed constants

using namespace std;			//resolve std namespace
using namespace GameConstants;  //resolve constant namespace for PositionGame

//overloaded << operator for Map
ostream& operator<<(ostream& o, Map const& map) {
	if (o.good()) {  //check if ostream is valid
		//write each line to o, if there is ground, print a space instead
		for_each(map.cbegin(), map.cend(), [&](string const& line) {		
			for_each(line.cbegin(), line.cend(), [&](char const c) { c == GroundChar ? (o << Space) : (o << c); }); o << endl; });
	}
	return o;	 //return manipulated ostream
}

//default Ctor, initializing filename with random file from maps folder
PositionGame::PositionGame() : mFileName{ GetFileName() } {};

//Ctor with filename as parameter
PositionGame::PositionGame(string const& fileName) : mFileName{ fileName } {};

//selects a random file from dedicated folder
string PositionGame::GetFileName() {
	vector<string> files{};   //vector for filenames
	ostringstream stream{};	  //define an empty ostringstream
	if (stream.good()) {	  //check if defining stream worked
		for (auto const& name : std::filesystem::directory_iterator{ MapDirectory }) {  //iterate over all files in directory
			stream << name.path();			//write name to stringstream
			files.push_back(stream.str());	//insert filename into vector
			files[files.size() - 1].erase(0, 1);                                 //erase " characters
			files[files.size() - 1].erase(files[files.size() - 1].size() - 1);
			stream.str("");  //make stringstream empty
			stream.clear();
		}
	}
	srand(time(nullptr));				  //set a seed
	return files[rand() % files.size()];  //return random filename from directory
}

//player has to move, gets hints and press escape to key in position
void PositionGame::FindPosition() {
	int key = 0;	//variable for saving user typed key

	while ((key = _getch()) != Escape) {  //read keys until user presses Escape, always adapt position
		switch (key) {
			case MoveUp:    ChangePosition(mPos.PosX, mPos.PosY - 1);  break;
			case MoveDown:  ChangePosition(mPos.PosX, mPos.PosY + 1);  break;
			case MoveLeft:  ChangePosition(mPos.PosX - 1, mPos.PosY);  break;
			case MoveRight: ChangePosition(mPos.PosX + 1, mPos.PosY);  break;
		}
	}

	size_t position = 0;		  //variable for saving position typed in by user
	cout << AskPosition << endl;  //ask user for position

	if (!(cin >> position)) {   //check for user input error
		cerr << InputError << endl;
		return;
	}

	if (position == mPos.winningPos) {  //check if user selected correct position
		cout << WinningText << endl;
	}
	else {
		cout << LoosingText << mPos.winningPos << endl;
	}
}

//set new position, prints message if position is out of borders
void PositionGame::ChangePosition(size_t const newX, size_t const newY) {
	if (newX < 0 || newY < 0 || newX >= NoColumns || newY >= NoLines ||
		mMap[newY][newX] == BorderChar) {								//check if new position is in borders
		cout << NoWay << endl;											//if not, print error
	}
	else if (mMap[newY][newX] == TreeChar) {  //print messages for special surroundings
		cout << TreeText << endl;
	}
	else if (mMap[newY][newX] == WaterChar) {
		cout << WaterText << endl;
	}
	else if (mMap[newY][newX] == WallChar) {
		cout << WallText << endl;
	}
	else {
		mPos.PosX = newX;   //set new position
		mPos.PosY = newY;
	}
}

//scanns the map and prints it to console, throws error text if file cannot be read
void PositionGame::StartGame() {
	ifstream inFile{ mFileName };  //define a input filestream to scan map

	if (!inFile.is_open()) {  //check if opening file worked
		throw ReadFileError;  //if not, throw error text
	}

	string positionLine;             //string to save line with winning position
	getline(inFile, positionLine);   //scan the line

	istringstream iStream{ positionLine };  //define a stringstream for the line

	if (iStream.good()) {  //check if defining stream worked
		array<size_t, PosData> winPos;   //array for temporary saving the position data
		copy(istream_iterator<size_t>{iStream}, istream_iterator<size_t>{}, winPos.begin());  //read position data into array
		mPos = { winPos[0], winPos[1], winPos[2] };  //save position data into position member

		copy(istream_iterator<string>{ inFile }, istream_iterator<string>{}, mMap.begin());  //read all lines of map into array

		cout << Introduction << endl << endl << mMap << endl;  //print user instruction text and map

		FindPosition();  //begin finding position

		inFile.close();
	}
}