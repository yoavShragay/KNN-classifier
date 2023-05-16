#include "distances.h"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#define P 2

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

/**
 * Minkowski - Euclidean - Manhattan Distance
 * Since both equations (Euclidean and Manhattan) are a special case
 * of the Minkowski equations, we will use a helper function
 * This function gets 2 vectors and an integer
 * and calculates the distance according to Minkowski distance
 * but with a different integer.
 * @param v1 - vector<double>
 * @param v2 - vector<double>
 * @param p - integer
 * @return - the distance between the vectors given integer p.
 */

double MEM_calculating(vector<double> v1, vector<double> v2, int p) {
    double sum = 0;
    for (int i = 0; i < v1.size(); i++) {
        sum += pow(abs(v1[i] - v2[i]), p);
    }
    return pow(sum, (double) 1 / p);
}

/**
 * This function gets 2 vectors and calculates the absolute value
 * between them. It returns a vector with all the values.
 * @param v1 - vector<double>
 * @param v2 - vector<double>
 * @return - A vector whose members are the subtraction
 * of the vectors values in absolute value
 */
vector<double> absVectorVal(vector<double> v1, vector<double> v2) {
    vector<double> absVec;
    for (int i = 0; i < v1.size(); i++) {
        absVec.push_back(abs(v1[i] - v2[i]));
    }
    return absVec;
}

/**
 * This function calculates the Euclidean distance between 2 vectors
 * and prints the result.
 * @param v1 - vector<double>
 * @param v2 - vector<double>
 */
double Euclidean_Distance(vector<double> v1, vector<double> v2) {
    return MEM_calculating(v1, v2, 2);
}

/**
 * This function calculates the Manhattan distance between 2 vectors
 * and prints the result.
 * @param v1 - vector<double>
 * @param v2 - vector<double>
 */
double Manhattan_Distance(vector<double> v1, vector<double> v2) {
    return MEM_calculating(v1, v2, 1);
}

/**
 * This function calculates the Chebyshev distance between 2 vectors
 * and prints the result.
 * @param v1 - vector<double>
 * @param v2 - vector<double>
 */
double Chebyshev_Distance(vector<double> v1, vector<double> v2) {
    vector<double> absVec;
    absVec = absVectorVal(v1, v2);
    double max = 0;
    for (int i = 0; i < v1.size(); i++) {
        if (absVec[i] > max)
            max = absVec[i];
    }
    return max;
}

/**
 * This function calculates the Canberra distance between 2 vectors
 * and prints the result.
 * @param v1 - vector<double>
 * @param v2 - vector<double>
 */
double Canberra_Distance(vector<double> v1, vector<double> v2) {
    vector<double> absVec;
    absVec = absVectorVal(v1, v2);
    double sum = 0;
    for (int i = 0; i < v1.size(); i++) {
        if (abs(v1[i]) != 0 || abs(v2[i]) != 0) {
            sum += absVec[i] / (abs(v1[i]) + abs(v2[i]));
        }
    }
    return sum;
}

/**
 * This function calculates the Minkowski distance between 2 vectors
 * and prints the result.
 * @param v1 - vector<double>
 * @param v2 - vector<double>
 */
double Minkowski_Distance(vector<double> v1, vector<double> v2) {
    return MEM_calculating(v1, v2, P);
}