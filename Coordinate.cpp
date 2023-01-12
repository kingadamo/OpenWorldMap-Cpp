#include "Coordinate.h"
#include "Util.h"
#include <cmath>

/**
 * Base Constructor.
 */
Coordinate::Coordinate() {
}


/**
 * Constructor of Coordinate.
 *
 * @param[in] y the y value of the coordinate in the world.
 * @param[in] x the x value of the coordinate in the world.
 */
Coordinate::Coordinate(int y, int x): _yValue(y), _xValue(x) {
    this->_yQuadrant = floorDiv(_yValue, CHUNK_DIMENSION);
    this->_xQuadrant = floorDiv(_xValue, CHUNK_DIMENSION);
    this->_yQuadrantValue = floorMod(_yValue, CHUNK_DIMENSION);
    this->_xQuadrantValue = floorMod(_xValue, CHUNK_DIMENSION);
    this->_coordKey = this->getCoordKey();
    this->_quadrantKey = this->getQuadrantKey();
    this->_quadrantValueKey = this->getQuadrantValueKey();

}


/**
 * Constructor of Coordinate.
 *
 * @param[in] key the key associated to a coordinate.
 * @param[in] type the KeyType of the provided key.
 */
Coordinate::Coordinate(const __int32 &key, const KeyType &type) {
    
    switch (type) {
        case KeyType::CoordinateKey:
            this->_yValue = (__int16) (key >> 16);
            this->_xValue = (__int16) key;
            *this = Coordinate(_yValue, _xValue);
            break;
        case KeyType::QuadrantKey:
            this->_yQuadrant = (__int16) (key >> 16);
            this->_xQuadrant = (__int16) key;
            this->_quadrantKey = key;
            break;
        case KeyType::QuadrantValueKey:
            this->_yQuadrantValue = (__int16) (key >> 16);
            this->_xQuadrantValue = (__int16) key;
            this->_quadrantValueKey = key;
            break;
        default:
            break;
    }
    
    
    
    
    /*char* keyChar = new char[key.length() + 1];
    strcpy(keyChar, key.c_str());

    switch (type) {
        case QuadrantKey:
            char* ptrQuadrantKeySplit = strtok(keyChar, ",");
            this->_yQuadrant = std::stoi(ptrQuadrantKeySplit);
            ptrQuadrantKeySplit = strtok(NULL, ",");
            this->_xQuadrant = std::stoi(ptrQuadrantKeySplit);
            this->_quadrantKey = this->getQuadrantKey();
            break;
        default:
            break;
    }
    delete[] keyChar;*/
}


/**
 * Generates a Coordinate key.
 *
 * @param[in] _yValue the y coordinate.
 * @param[in] _xValue the x coordinate.
 * @return Key of the coordinate values.
 */
__int32 Coordinate::getCoordKey() {
    return ( (__int32)_yValue << 16) + _xValue;
}


/**
 * Generates a Coordinate quadrant key.
 *
 * @param[in] _yQuadrant the y quadrant coordinate.
 * @param[in] _xQuadrant the x quadrant coordinate.
 * @return Key of the coordinate quadrant values.
 */
__int32 Coordinate::getQuadrantKey() {
    return ( (__int32)_yQuadrant << 16) + _xQuadrant;
}


/**
 * Generates a Coordinate quadrant value key.
 *
 * @param[in] _yQuadrantValue the y value in the quadrant coordinate.
 * @param[in] _xQuadrantValue the x value in the quadrant coordinate.
 * @return Key of the coordinate value in the quadrant values.
 */
__int32 Coordinate::getQuadrantValueKey() {
    return ( (__int32)_yQuadrantValue << 16) + _xQuadrantValue;
}



//int Coordinate::getyQuadrant() {
//    return _yQuadrant;
//}
//int Coordinate::getxQuadrant() {
//    return _xQuadrant;
//}
//int Coordinate::getyQuadrantValue() {
//    return _yQuadrantValue;
//}
//int Coordinate::getxQuadrantValue() {
//    return _xQuadrantValue;
//}

