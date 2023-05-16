
#ifndef YOAV_ROY_ASS3_REPO_VALIDATIONS_H
#define YOAV_ROY_ASS3_REPO_VALIDATIONS_H

#include <string>
#include "classifiedVector.h"
#include "disVector.h"

using namespace std;

void illegal();

void freeMem(const disVector &currentVec);

bool checkBig(string num, int indexE);

bool checkNumber(string str);

bool checkSpaces(string vec);

vector<double> fillVectorByDelim(const string &strVec, char delim);

vector<classifiedVector *> stringToVec(string file_name, bool flag, bool &valid);

string getClass(vector<classifiedVector> nearestVecs);

bool check_valid_dis(string dis);

int checkAlgoSettingsInput(const string &userInput);

bool check_valid_user_input(string userInput, int read_bytes);

string getClassification(vector<classifiedVector *> allClassVec,
                         const string &distance, int neighborsNum, vector<double> newVec);

#endif //YOAV_ROY_ASS3_REPO_VALIDATIONS_H
