#ifndef _DISTANCEALGO_H_
#define _DISTANCEALGO_H_

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

/**
 * This is a father class that represents a the distance functions
 * All 5 distance classes inherit from the father class
 */
class distanceAlgo {
public:
    virtual double checkDistance(vector<double> v1, vector<double> v2);

    distanceAlgo() = default;

    virtual ~distanceAlgo() = default;
};

/**
 * This is a sub-class that represents the euclidean distance
 */
class euclideanDis : public distanceAlgo {
public:
    double checkDistance(vector<double> v1, vector<double> v2) override;

    ~euclideanDis() override = default;

    euclideanDis() = default;
};

/**
 * This is a sub-class that represents the manhattan distance
 */
class manhattanDis : public distanceAlgo {
public:
    double checkDistance(vector<double> v1, vector<double> v2) override;

    ~manhattanDis() override = default;

    manhattanDis() = default;
};

/**
 * This is a sub-class that represents the chebyshev distance
 */
class chebyshevDis : public distanceAlgo {
public:
    double checkDistance(vector<double> v1, vector<double> v2) override;

    ~chebyshevDis() override = default;

    chebyshevDis() = default;
};

/**
 * This is a sub-class that represents the canberra distance
 */
class canberraDis : public distanceAlgo {
public:
    double checkDistance(vector<double> v1, vector<double> v2) override;

    ~canberraDis() override = default;

    canberraDis() = default;
};

/**
 * This is a sub-class that represents the minkowski distance
 */
class minkowskiDis : public distanceAlgo {
public:
    double checkDistance(vector<double> v1, vector<double> v2) override;

    ~minkowskiDis() override = default;

    minkowskiDis() = default;
};

#endif //_DISTANCEALGO_H_
