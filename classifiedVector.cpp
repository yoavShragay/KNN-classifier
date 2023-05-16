#include "classifiedVector.h"
#include <vector>
#include <string>

using namespace std;

/**
 * Constructor - creating a new classified vector
 * @param currentVec - holds the values (e.g. (4.3, 1.4, 5, 6.7))
 * @param classification - holds the classification (e.g. Iris-setosa)
 * @param len - number of values in the vector
 */
classifiedVector::classifiedVector(vector<double> currentVec,
                                   string classification, int len) {
    this->currentVec = move(currentVec);
    this->classification = move(classification);
    this->distance = 0;
    this->len = len;
}

/**
 * @return - The vector that holds the values of a classified vector
 */
vector<double> classifiedVector::getCurrVec() const {
    return this->currentVec;
}

/**
 * @return - The classification of a classified vector
 */
string classifiedVector::getClass() const {
    return this->classification;
}

/**
 * Setting the classification of a vector
 * @param cls - new classification
 */
void classifiedVector::setClass(string cls) {
    this->classification = cls;
}

/**
 * Setting the distance of a classified vector
 * @param d - new distance
 */
void classifiedVector::setDistance(double d) {
    this->distance = d;
}

/**
 * @return - The distance of a classified vector
 */
double classifiedVector::getDistance() const {
    return this->distance;
}

/**
 * @return - The length of a classified vector (only values)
 */
int classifiedVector::getLen() const {
    return this->len;
}