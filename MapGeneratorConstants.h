///////////////////////////////////////////////////////////////////////
// Workfile: MapGeneratorConstants.h
// Author: Christoph Dalpiaz
// Date: 19.07.2020
// Description: constants for MapGenerator
// Remarks: -
// Revision: 0
///////////////////////////////////////////////////////////////////////

#ifndef MAPGENERATORCONSTANTS_H
#define MAPGENERATORCONSTANTS_H

namespace GeneratorConstants {
	//constraints for water areas
	size_t const MinNoWaters = 1;
	size_t const MaxNoWaters = 4;

	size_t const MinWaterArea = 4;
	size_t const MaxWaterArea = 36;

	size_t const MinWaterWidth = 3;
	size_t const MaxWaterWidth = 10;

	//denominator for propability that water becomes rounded, 1/4
	size_t const PropabilityWaterRound = 4;

	//constraints for trees
	size_t const MinNoTrees = 8;
	size_t const MaxNoTrees = 20;

	//constraints for buildings
	size_t const MinNoBuildings = 0;
	size_t const MaxNoBuildings = 2;

	size_t const MinBuildingArea = 16;
	size_t const MaxBuildingArea = 36;

	size_t const MinBuildingWidth = 4;
	size_t const MaxBuildingWidth = 12;

	//maximum ratio of longer side / shorter side
	double const BuildingRatio = 3.0 / 2.0;

	//number of generated positions
	size_t const MinNoPositions = 3;
	size_t const MaxNoPositions = 6;

	Map const InitMap = { "####################################",
						  "#----------------------------------#",
						  "#----------------------------------#",
						  "#----------------------------------#",
						  "#----------------------------------#",
						  "#----------------------------------#",
						  "#----------------------------------#",
						  "#----------------------------------#",
						  "#----------------------------------#",
						  "#----------------------------------#",
						  "#----------------------------------#",
						  "#----------------------------------#",
						  "#----------------------------------#",
						  "#----------------------------------#",
						  "#----------------------------------#",
						  "#----------------------------------#",
						  "#----------------------------------#",
						  "#----------------------------------#",
						  "#----------------------------------#",
						  "####################################" };
};

#endif