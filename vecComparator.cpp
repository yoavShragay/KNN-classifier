#include "vecComparator.h"

using namespace std;

/**
 * comparator for the min heap
 * @param v1 first vector
 * @param v2 second vector
 * @return true if v1 bigger then v2, false otherwise
 */
bool vecComparator::operator()(classifiedVector *v1, classifiedVector *v2) {
    return v1->getDistance() > v2->getDistance();
}