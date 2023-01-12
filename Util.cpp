#include "Util.h"
#include <cmath>

int floorMod(const int& a, const int& b) {
    return (a % b + b) % b;
}

int floorDiv(const int& a, const int& b) {
    return floor(a / (double)b);
}