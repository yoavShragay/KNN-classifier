#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <sstream>

#include "disVector.h"
#include "classifiedVector.h"
#include "vectorsDataStruct.h"

#define ERROR "invalid input"

using namespace std;

/**
 * Exit the program in case of an error
 */
void illegal() {
    cout << "Illegal input";
    exit(1);
}

/**
 * This function frees the memory allocated in disVector object.
 * @param currentVec - disVector object that holds distanceAlgo objects.
*/
void freeMem(const disVector &currentVec) {
    for (auto &element: currentVec.getDistances()) {
        delete element;
    }
}

/**
 * checking if the number have e\E in it
 * @param num the number that going to be checked
 * @param indexE the index where the e is
 * @return true if its a number and false if isn't
 */
bool checkBig(string num, int indexE) {
    int num_len = num.length();
    if (indexE != 0 && indexE < num_len - 2) {
        if (num[indexE + 1] == '+' || num[indexE + 1] == '-') {
            return true;
        }
    }
    return false;
}

/**
 * Checking if the string given is a proper number.
 * @param str the number
 */
bool checkNumber(string str) {
    bool pointFlag = true;
    int strLen = str.length();
    // case - only "." or only "-" or "." at the end or word to long
    if (str == "." || str == "-" || str[str.length() - 1] == '.'
        || str.length() >= 300) {
        return false;
    }
    for (int i = 0; i < strLen; i++) {
        // case - more than one point
        if (str[i] == '.') {
            if (!pointFlag) {
                return false;
            }
            pointFlag = false;
        } else if (i == 0 && str[i] == '-') {
            continue;
        }
            // case - the character isn't a number
        else if (!(isdigit(str[i]))) {
            // case - the number is big
            if (!checkBig(str, i)) {
                return false;
            }
            i++;
        }
    }
    return true;
}

/**
 * checking if the spaces between the numbers are in the correct format
 * @param v the string given from the user
 */
bool checkSpaces(string vec) {

    if (vec.empty()) {
        return false;
    }
    for (int i = 0; i < vec.length(); i++) {
        if (vec[i] == ' ') {
            // case - " " at the beginning
            if (i == 0) { return false; }
            // case - too many " "
            if (vec[i - 1] == ' ') { return false; }
            // case - " " at the end
            if (i == vec.length() - 1) { return false; }
        }
    }
    return true;
}

/**
  * Getting the string from the file, filling a vector with the values
 * in the string, and returning that vector
 * @param strVec - the string given from the user represents a vector
 * @param delim - a char that separates the values in the given string
 * @return a new vector with the values that was in the excel
*/
vector<double> fillVectorByDelim(const string &strVec, char delim) {
    string value;
    vector<double> newVec;
    checkSpaces(strVec);
    stringstream str(strVec);
    while (getline(str, value, delim)) {
        if (checkNumber(value)) {
            newVec.push_back(stod(value));
        }
    }
    return newVec;
}

/**
 * This function takes a string of all vectors separated by '@' and returns and vector of all classified vectors
 * Here we make vectors from the classified file and also from the unclassified file (the classification is empty).
 * @param strData - string of all the vectors from the file
 * @param flag - true if the vectors classified, false if unclassified
 * @return - vector<classifiedVector *>
 */
vector<classifiedVector *> stringToVec(string strData, bool flag, bool &valid) {
    int i = 0;
    vector<classifiedVector *> allClassVec;
    vector<double> rowVec;

    // the '$' tells us when it's the end of the data in the file
    while (strData[i] != '$') {
        string newVec;
        // the '@' separates between vectors
        while (strData[i] != '@') {
            newVec += strData[i];
            i++;
        }
        // if true - the vectors are classified.
        if (flag) {
            int index = newVec.find_last_of(',');
            string cls = newVec.substr(index + 1, newVec.length() - (index + 1));
            // create a classification vector for each row
            // and push them into a vector of classified vectors.
            rowVec = fillVectorByDelim(newVec.substr(0, index), ',');
            classifiedVector *classVec = new classifiedVector(rowVec, cls, rowVec.size());
            // check if the vectors in the file have the same size
            if (!allClassVec.empty() && (classVec->getLen() != allClassVec[0]->getLen())) {
                valid = false;
            }
            allClassVec.push_back(classVec);
        }
            // if false - the vectors are unclassified.
        else {
            rowVec = fillVectorByDelim(
                    newVec.substr(0, newVec.length()), ',');
            classifiedVector *classVec = new classifiedVector(rowVec, "", rowVec.size());
            // check if the vectors in the file have the same size
            if (!allClassVec.empty() && (classVec->getLen() != allClassVec[0]->getLen())) {
                valid = false;
            }
            allClassVec.push_back(classVec);
        }
        i++;
    }
    return allClassVec;
}

/**
 * Creating a map 'clsCounts' that contains classification for 'key'
 * and the number of times it appears in the nearestVecs vector for 'value'
 * @param nearestVecs - vector of k nearest vectors
 * @return the most common classification of the k nearest vectors
 */
string getClass(vector<classifiedVector *> nearestVecs) {
    map<string, int> clsCounts;
    int maxVal = 0;
    string cls;
    // running over the k nearest classified vectors in nearestVecs
    // clsVec represents a classified vector
    for (auto &clsVec: nearestVecs) {
        // if the key isn't in the map, add the key with value = 1
        if (clsCounts.count(clsVec->getClass()) == 0) {
            clsCounts.insert({clsVec->getClass(), 1});
        }
        // else - increment the value for this key
        clsCounts[clsVec->getClass()]++;
        if (clsCounts[clsVec->getClass()] > maxVal) {
            // remember the most common classification
            maxVal = clsCounts[clsVec->getClass()];
            cls = clsVec->getClass();
        }
    }
    return cls;
}

/**
 * Getting input from user and printing the classification
 * @param allClassVec - vector that contains all classified vectors
 * @param distance - string that represents the distance function
 * @param neighborsNum - number of neighbors to check from
 * @param newVec - a double vector that represents the user input vector
 * @return the classification according to the user input
 */
string getClassification(vector<classifiedVector *> allClassVec, const string &distance, int neighborsNum,
                         vector<double> newVec) {
    // Check if the input vector is the same length as the file vectors
    vector<classifiedVector *> k_nearest;
    if (newVec.size() != allClassVec[0]->getLen()) {
        return ERROR;
    }
    disVector *currentVec = new disVector(newVec, distance);
    vectorsDataStruct *dataStr = new vectorsDataStruct(*currentVec, allClassVec);
    vector<classifiedVector *> a = (dataStr->getK(neighborsNum));
    for (int i = 0; i < neighborsNum; ++i) {
        k_nearest.push_back(a[i]);
    }
    string k = getClass(k_nearest);
    // free the memory we allocated
    freeMem(*currentVec);
    delete currentVec;
    delete dataStr;
    return k;
}

/**
 * This function checks of the distance is correct
 * @param dis - string that represents a distance function
 * @return - true if the input is valid, false otherwise
 */
bool check_valid_dis(string dis) {
    vector<string> distances = {"AUC", "MAN", "CHB", "CAN", "MIN"};
    for (auto &distance: distances) {
        if (dis == distance) {
            return true;
        }
    }
    return false;
}

/**
 * This function checks the validation of the user input in option 2
 * @param userInput - string that contains K and a metric.
 * @return - 0 if the input is valid, 1 if the k is invalid, 2 if the metric is invalid
 * and 3 if both are invalid.
 */
int checkAlgoSettingsInput(const string &userInput) {
    size_t first_index = userInput.find_first_of(' ');
    string newK = userInput.substr(0, first_index);
    string newDis = userInput.substr(first_index + 1, userInput.length());
    bool flag = true;
    int count = 0;

    // check if 1 of the chars isn't a digit
    for (char const &c: newK) {
        if (isdigit(c) == 0) {
            flag = false;
            break;
        }
    }
    if (flag && ((newK.length() >= 1 && newK[0] == '0') || newK.length() > 10)) {
        flag = false;
    }

    if (flag && !checkNumber(newK)) {
        flag = false;
    }

    // return a different number base on the validation of the input
    if (!flag && !check_valid_dis(newDis)) {
        count = 3;
    } else {
        if (!flag) {
            count = 1;
        }
        if (!check_valid_dis(newDis)) {
            count = 2;
        }
    }
    return count;
}

/**
 * This function gets a string of the user input, and checks the validation of every parameter
 * @param userInput - a string of the user input (vector, distance, k)
 * @return if one of the parameters arent valid return false, return true otherwise
 */
bool check_valid_user_input(string userInput, int read_bytes) {
    bool flag = true;
    int last_index = userInput.find_last_of(' ');
    int first_index;
    // splitting the k parameter from user input
    string k = userInput.substr(last_index + 1, read_bytes - last_index);
    if (k.length() > 10) {
        return false;
    }
    // check if the k parameter is valid
    if (!checkNumber(k)) {
        return false;
    }
    for (int i = last_index - 1; i >= 0; --i) {
        // splitting the distance parameter from user input
        if (userInput[i] == ' ' && flag) {
            first_index = i;
            // splitting the vector parameter from the user input
            string distance = userInput.substr(first_index + 1, last_index - (first_index + 1));
            // check if the distance parameter is valid
            if (!check_valid_dis(distance)) {
                return false;
            }
            flag = false;
        }
    }
    // splitting the vector parameter from the user input
    string vec = userInput.substr(0, first_index);
    // check if the vector is valid
    string value;
    vector<double> newVec;
    if (!checkSpaces(vec)) {
        return false;
    }
    stringstream str(vec);
    while (getline(str, value, ' ')) {
        if (!checkNumber(value)) {
            return false;
        }
    }
    return true;
}
