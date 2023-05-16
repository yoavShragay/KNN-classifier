
#ifndef _CLASSIFIEDVECTOR_H_
#define _CLASSIFIEDVECTOR_H_

#include <vector>
#include <string>

using namespace std;

class classifiedVector {

private:
    vector<double> currentVec;
    string classification;
    double distance;
    int len;

public:
    classifiedVector(vector<double> currentVec, string classification, int len);

    vector<double> getCurrVec() const;

    string getClass() const;

    void setClass(string cls);

    void setDistance(double d);

    double getDistance() const;

    int getLen() const;
};

#endif //_CLASSIFIEDVECTOR_H_
