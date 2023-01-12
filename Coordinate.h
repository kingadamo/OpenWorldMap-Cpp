#pragma once



enum class KeyType {
	CoordinateKey = 1,
	QuadrantKey = 2,
	QuadrantValueKey = 3
};

class Coordinate {
	public:
		Coordinate();
		Coordinate(int y, int x);
		Coordinate(const __int32 &key,const  KeyType &type);

		__int32 getCoordKey();
		__int32 getQuadrantKey();
		__int32 getQuadrantValueKey();

		/*int getyQuadrant();
		int getxQuadrant();
		int getyQuadrantValue();
		int getxQuadrantValue();*/

		__int16 _yValue = 0;
		__int16 _xValue = 0;
		__int16 _yQuadrant = 0;
		__int16 _xQuadrant = 0;
		__int16 _yQuadrantValue = 0;
		__int16 _xQuadrantValue = 0;

		__int32 _coordKey = 0;
		__int32 _quadrantKey = 0;
		__int32 _quadrantValueKey = 0;

	private:
};

