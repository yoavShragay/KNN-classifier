#include "distanceAlgo.h"
#include "distances.h"
#include <vector>

/**
 * A father class function of distances calculation (used for polymorphism)
 * @param v1 - first vector
 * @param v2 - second vector
 * @return - the distance between the vectors
 */
double distanceAlgo::checkDistance(vector<double> v1, vector<double> v2) {
    return 0;
}

/**
 * Calculates the euclidean distance between the vectors
 * @param v1 - first vector
 * @param v2 - second vector
 * @return - the euclidean distance between the vectors
 */
double euclideanDis::checkDistance(vector<double> v1, vector<double> v2) {
    return Euclidean_Distance(v1, v2);
}

/**
 * Calculates the manhattan distance between the vectors
 * @param v1 - first vector
 * @param v2 - second vector
 * @return - the manhattan distance between the vectors
 */
double manhattanDis::checkDistance(vector<double> v1, vector<double> v2) {
    return Manhattan_Distance(v1, v2);
}

/**
 * Calculates the chebyshev distance between the vectors
 * @param v1 - first vector
 * @param v2 - second vector
 * @return - the chebyshev distance between the vectors
 */
double chebyshevDis::checkDistance(vector<double> v1, vector<double> v2) {
    return Chebyshev_Distance(v1, v2);
}

/**
 * Calculates the canberra distance between the vectors
 * @param v1 - first vector
 * @param v2 - second vector
 * @return - the canberra distance between the vectors
 */
double canberraDis::checkDistance(vector<double> v1, vector<double> v2) {
    return Canberra_Distance(v1, v2);
}

/**
 * Calculates the minkowski distance between the vectors
 * @param v1 - first vector
 * @param v2 - second vector
 * @return - the minkowski distance between the vectors
 */
double minkowskiDis::checkDistance(vector<double> v1, vector<double> v2) {
    return Minkowski_Distance(v1, v2);
}