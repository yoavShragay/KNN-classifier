#include <iostream>
#include <vector>
#include <string>
#include "vectorData.h"
using namespace std;

/**
 * Constructor - creates an object that contains the user input parameters
 * @param distance - distance
 * @param vec - vector
 * @param k - k
 */
vectorData::vectorData(string vec, string distance, int k) {
    this->vec = vec;
    this->distance = distance;
    this->k = k;
}

/**
 * Getter for Distance
 */
string vectorData::getDistance() {
    return this->distance;
}

/**
 * Getter for the vector
 */
string vectorData::getVec(){
    return vec;
}

/**
 * Getter for the k
 */
int vectorData::getK(){
    return k;
}

/**
 * Setter for the distance
 */
void vectorData::setDistance( string distance){
    this->distance = distance;
}

/**
 * Setter for vector
 */
void vectorData::setVec(string vec){
    this->vec = vec;
}

/**
 * Setter for the k
 */
void vectorData::setK(int k){
    this->k = k;
}
