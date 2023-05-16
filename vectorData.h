
#ifndef YOAV_ROY_ASS3_REPO_VECTORDATA_H
#define YOAV_ROY_ASS3_REPO_VECTORDATA_H

#include "string"

using namespace std;

class vectorData {
private:
    string distance;
    string vec;
    int k;
public:
    vectorData(string vec, string distance, int k);

    string getDistance();

    string getVec();

    int getK();

    void setDistance(string distance);

    void setVec(string vec);

    void setK(int k);
};

#endif //YOAV_ROY_ASS3_REPO_VECTORDATA_H
