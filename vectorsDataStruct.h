#ifndef _VECTORSDATASTRUCT_H_
#define _VECTORSDATASTRUCT_H_

#include "vectorsDataStruct.h"
#include "disVector.h"
#include "classifiedVector.h"
#include <vector>
#include <string>

class vectorsDataStruct {

private:
    disVector structureVector;
    vector<classifiedVector *> vectorsHeap;

public:
    vectorsDataStruct(disVector &structureVector,
                      vector<classifiedVector *> vectorsHeap);

    void updateDistances(vector<classifiedVector *> &vectorsHeap);

    classifiedVector at(int index);

    vector<classifiedVector *> getK(int k);

};

#endif //_VECTORSDATASTRUCT_H_
