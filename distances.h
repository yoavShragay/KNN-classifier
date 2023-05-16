#ifndef _DISTANCES_H_
#define _DISTANCES_H_

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

double MEM_calculating(vector<double> v1, vector<double> v2, int p);

double Euclidean_Distance(vector<double> v1, vector<double> v2);

double Manhattan_Distance(vector<double> v1, vector<double> v2);

vector<double> absVectorVal(vector<double> v1, vector<double> v2);

double Chebyshev_Distance(vector<double> v1, vector<double> v2);

double Canberra_Distance(vector<double> v1, vector<double> v2);

double Minkowski_Distance(vector<double> v1, vector<double> v2);

#endif //_DISTANCES_H_
