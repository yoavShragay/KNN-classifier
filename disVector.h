#ifndef _DISVECTOR_H_
#define _DISVECTOR_H_

#include "distanceAlgo.h"
#include <vector>
#include <string>

using namespace std;

class disVector {

private:
    int distanceFuncNum;
    vector<double> currentVec;
    vector<distanceAlgo *> distances;

public:
    disVector();

    disVector(vector<double> currVec, const string &distance);

    void setDistanceFuncNum(const string &distance);

    double checkVectorDistance(const vector<double> &otherVec);

    void illegal();

    void isDis(const string &newDis);

    vector<distanceAlgo *> getDistances() const;
};

#endif //_DISVECTOR_H_
