///////////////////////////////////////////////////////////////////////
// Workfile: Main.cpp
// Author: Christoph Dalpiaz
// Date: 17.07.2020
// Description: test driver for PositionGame
// Remarks: -
// Revision: 0
///////////////////////////////////////////////////////////////////////

#include <iostream>
#include "MapGenerator.h"
#include "PositionGame.h"

using namespace std;

int main()
{
	try {

		//------------tests for the generator-------------

		//MapGenerator mapGen;
		//
		//mapGen.Generate("map", 1000);

		//----------tests for the game------------------
		
		//PositionGame game{ "F://testFarm.txt" };
		PositionGame game{};
		
		game.StartGame();
	}
	catch (bad_alloc const& ex) {
		cerr << ex.what() << endl;
		return 1;
	}
	catch(exception const& ex){
		cerr << ex.what() << endl;
		return 1;
	}
	catch (string const& errorText) {
		cerr << errorText << endl;
		return 1;
	}
	catch (...) {
		cerr << "Unhandled exception!" << endl;
		return 1;
	}

	return 0;
}