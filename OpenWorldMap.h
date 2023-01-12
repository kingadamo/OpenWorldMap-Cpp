#pragma once
#include "Util.h"
#include "Coordinate.h"
#include <array>
#include <map>

class OpenWorldMap{
	public:
		OpenWorldMap();
		void addObstacleAtCoord(const Coordinate &target);
		__int8 getValueAtCoord(Coordinate target);
		void updateChunkDirectory(Coordinate target);
		std::map<__int32, std::array<std::array<__int8, CHUNK_DIMENSION>, CHUNK_DIMENSION>> _chunkDirectory;

	private:
		bool isChunkAvailable(__int32 mapKey);
		bool isCoordinateAvailable(Coordinate coord);
		void addChunkToDirectory(__int32 mapKey);
};

