#ifndef _VECCOMPARATOR_H_
#define _VECCOMPARATOR_H_

#include "vectorsDataStruct.h"
#include "disVector.h"
#include "classifiedVector.h"
#include <vector>
#include <string>

class vecComparator {
public:
    bool operator()(classifiedVector *v1, classifiedVector *v2);
};

#endif //_VECCOMPARATOR_H_
