#include "disVector.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

/**
 * Default constructor
 */
disVector::disVector() {}

/**
 * Constructor - disVector
 * @param currVec - new vector with values
 * @param distance - name of a distance function
 */
disVector::disVector(vector<double> currVec, const string &distance) {
    isDis(distance);
    this->currentVec = move(currVec);
    setDistanceFuncNum(distance);
    this->distances.push_back(new euclideanDis());
    this->distances.push_back(new manhattanDis());
    this->distances.push_back(new chebyshevDis());
    this->distances.push_back(new canberraDis());
    this->distances.push_back(new minkowskiDis());
}

/**
 * Exit the program in case of an error
 */
void disVector::illegal() {
    cout << "illegal input";
    exit(1);
}

/**
 * Setting the right distance function according to the user input
 * @param distance - the name of a distance function
 */
void disVector::setDistanceFuncNum(const string &distance) {
    map<string, int> distanceFuncMap;
    distanceFuncMap.insert({"AUC", 0});
    distanceFuncMap.insert({"MAN", 1});
    distanceFuncMap.insert({"CHB", 2});
    distanceFuncMap.insert({"CAN", 3});
    distanceFuncMap.insert({"MIN", 4});
    if (distanceFuncMap.count(distance) == 0) {
        illegal();
    }
    distanceFuncNum = distanceFuncMap.at(distance);
}

/**
 * Checking the distance from the user vector to a classified vector
 * @param otherVec - classified vector from the file
 * @return the distance from the vectors according to the
 *         corresponding distance function
 */
double disVector::checkVectorDistance(const vector<double> &otherVec) {
    return distances[distanceFuncNum]->checkDistance(currentVec, otherVec);
}

/**
 * Checking if the distance function we got from the user is a valid function
 * @param newDis - the name of a distance function
 */
void disVector::isDis(const string &newDis) {
    bool flag = false;
    vector<string> disVec = {"AUC", "MAN", "CHB", "CAN", "MIN"};
    for (int i = 0; i < disVec.size(); i++) {
        if (newDis == disVec.at(i)) {
            flag = true;
        }
    }
    if (!flag) {
        illegal();
    }
}

/**
 * returning the distances vector
 * @return distances vector
 */
vector<distanceAlgo *> disVector::getDistances() const {
    return this->distances;
}