#include "OpenWorldMap.h"
#include <iostream>
#include "Util.h"
#include "Coordinate.h"
#include <array>
#include <map>

/**
 * Base Constructor
 */
OpenWorldMap::OpenWorldMap() { }


/**
 * Assures a chunk exists to accomodate the interaction with a Coordinate.
 *
 * @param target Coordinate which has to be accomodated.
 */
void OpenWorldMap::updateChunkDirectory(Coordinate target) {
	if (!isCoordinateAvailable(target))
		addChunkToDirectory(target._quadrantKey);
}


/**
 * Adds a chunk blank to the chunkDirectory with the given mapKey.
 *
 * @param mapKey Key to associate to the new chunk.
 */
void OpenWorldMap::addChunkToDirectory(__int32 mapKey) {
	// Memory Allocation
	std::array<std::array<__int8, CHUNK_DIMENSION>, CHUNK_DIMENSION> newChunk = {0};
	// Insertion
	_chunkDirectory.insert({ mapKey, newChunk });
}


/**
 * Increments the occupancy value at the given coordinate.
 *
 * @param[in] target Coordinate whose cell value is being incremented.
 */
void OpenWorldMap::addObstacleAtCoord(const Coordinate &target) {
	updateChunkDirectory(target);
	
	std::array<std::array<__int8, CHUNK_DIMENSION>, CHUNK_DIMENSION> currentChunk = _chunkDirectory.at(target._quadrantKey);;
	int yQuadrantValue = target._yQuadrantValue;
	int xQuadrantValue = target._xQuadrantValue;

	if (currentChunk[yQuadrantValue][xQuadrantValue] != (INT8_MAX)) {
		++currentChunk[yQuadrantValue][xQuadrantValue];
		_chunkDirectory.at(target._quadrantKey) = currentChunk;
	}
}


/**
 * Gets the occupancy value of a cell with a coordinate.
 *
 * @param target Coordinate whose cell value is being checked.
 * @return occupancy value at the coordinate position.
 */
__int8 OpenWorldMap::getValueAtCoord(Coordinate target) {
	if (!isCoordinateAvailable(target))
		return INT8_MIN;

	//std::array<std::array<__int8, CHUNK_DIMENSION>, CHUNK_DIMENSION> currentChunk = _chunkDirectory.at(target._quadrantKey);
	return _chunkDirectory.at(target._quadrantKey)[target._yQuadrantValue][target._xQuadrantValue];
}


/**
 * Checks if a given coordinate is accessible.
 *
 * @param coord Coordinate whose accessibility is checked.
 * @return bool value depending on accessibility.
 */
bool OpenWorldMap::isCoordinateAvailable(Coordinate coord) {
	return isChunkAvailable(coord._quadrantKey);
}


/**
 * Checks if a given chunk is accessible.
 *
 * @param mapKey Key of the chunk whose accessibility is checked.
 * @return bool value depending on accessibility.
 */
bool OpenWorldMap::isChunkAvailable(__int32 mapKey) {
	return _chunkDirectory.contains(mapKey);
}
