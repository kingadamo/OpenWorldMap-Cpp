#pragma once
#include "OpenWorldMap.h"
#include "Coordinate.h"

class EnvironmentMap {
private:
	OpenWorldMap _openWorldMap;

public:
	EnvironmentMap();
	void addObstacleAtCoord(Coordinate target);
	void printWorldMap();
	signed char getValueAtCoord(Coordinate target);
};

