#include "EnvironmentMap.h"


EnvironmentMap::EnvironmentMap() {
	this->_openWorldMap = OpenWorldMap();
}

void EnvironmentMap::addObstacleAtCoord(Coordinate target){
	_openWorldMap.addObstacleAtCoord(target);
}


signed char EnvironmentMap::getValueAtCoord(Coordinate target) {
	return _openWorldMap.getValueAtCoord(target);
}

void EnvironmentMap::printWorldMap() {

}