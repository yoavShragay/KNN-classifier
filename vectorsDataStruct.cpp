#include "vectorsDataStruct.h"
#include "vecComparator.h"
#include <vector>
#include <algorithm>

using namespace std;

/**
 *constructor for vectorsDataStruct
 * @param structureVector the vector i use to calculate the distances
 * @param vectorsHeap all the classified vectors for the data structure
 */
vectorsDataStruct::vectorsDataStruct(disVector &structureVector,
                                     vector<classifiedVector *> vectorsHeap) {
    this->structureVector = structureVector;
    updateDistances(vectorsHeap);
    make_heap(vectorsHeap.begin(), vectorsHeap.end(), vecComparator());
    this->vectorsHeap = vectorsHeap;
}

/**
 * updates the distances from the user vector of all the vectors in the heap
 * @param vectorsHeap the vectors in the data
 */
void vectorsDataStruct::updateDistances(vector<classifiedVector *> &vectorsHeap) {
    for (auto &i: vectorsHeap) {
        // get the current vector
        // get the distance
        double currentDistance =
                structureVector.checkVectorDistance(i->getCurrVec());
        // setting the distance
        i->setDistance(currentDistance);
    }
}

/**
 *get the vector at the requested index
 * @param index the requested index
 * @return the vector at the requested index
 */
classifiedVector vectorsDataStruct::at(int index) {
    return *vectorsHeap.at(index);
}

/**
 *get the k smallest vectors
 * @param k the amount of vectors
 * @return k smallest vectors
 */
vector<classifiedVector *> vectorsDataStruct::getK(int k) {
    vector<classifiedVector *> kSmallestVectors;
    for (int i = 0; i < k; i++) {
        kSmallestVectors.push_back(vectorsHeap.at(0));
        pop_heap(vectorsHeap.begin(),
                 vectorsHeap.end() - i, vecComparator());
    }
    return kSmallestVectors;
}