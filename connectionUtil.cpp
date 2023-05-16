
#include<iostream>
#include <string.h>
#include <utility>
#include <vector>
#include "connectionUtil.h"

#define BUFFERSIZE 4096

using namespace std;

/**
 * This function writes to cout
 * @param s - string to write to cout
 */
void StandardIO::write(string s) {
    cout << s << "\n";
}

/**
 * This function reads from cin
 * @return - the string input
 */
string StandardIO::read() {
    string x;
    getline(cin, x);
    return x;
}

/**
 * Setting the socket number of the client
 * @param client_sock - socket number
 */
void SocketIO::setClientSock(int client_sock) {
    this->client_sock = client_sock;
}

/**
 * This function reads from the socket
 * @return - the string we read
 */
string SocketIO::read() {
    char buffer = '0';
    string s;
    while (true) {
        recv(client_sock, &buffer, sizeof(char), 0);
        if (buffer == '$')
            break;
        s += buffer;
    }
    return s;
}

/**
 * This function writes to the socket
 * @param s - the string to write
 */
void SocketIO::write(string s) {
    char buffer[BUFFERSIZE] = "\0";
    strcpy(buffer, s.c_str());
    send(client_sock, buffer, s.length() + 1, 0);
    usleep(100);
}

/**
 * Getter for the path of the classified vectors file
 * @return - the path of the classified vectors file
 */
string ShareData::getClassifiedData() const {
    return this->classifiedData;
}

/**
 * Setter for the string of all classified vectors from the file
 * @param s - new string of all classified vectors
 */
void ShareData::setClassifiedData(string s) {
    this->classifiedData = std::move(s);
}

/**
 * Getter for the string of all unclassified vectors from the file
 * @return - the string of all unclassified vectors
 */
string ShareData::getUnClassifiedData() const {
    return this->unClassifiedData;
}

/**
 * Setter for the string of all unclassified vectors from the file
 * @param s - new string of all unclassified vectors
 */
void ShareData::setUnClassifiedData(string s) {
    this->unClassifiedData = std::move(s);
}

/**
 * Getter for the number of neighbors (k)
 * @return - the number of neighbors
 */
int ShareData::getK() const {
    return this->k;
}

/**
 * Setter for the number of neighbors (k)
 * @param k - new number of neighbors
 */
void ShareData::setK(int k) {
    this->k = k;
}

/**
 * Getter for the metric
 * @return - the metric
 */
string ShareData::getMetric() const {
    return this->metric;
}

/**
 * Setter for the metric
 * @param met - a new metric
 */
void ShareData::setMetric(string met) {
    this->metric = std::move(met);
}

/**
 * Getter for the classified vectors vector
 * @return vector that holds all the classified vectors
 */
vector<classifiedVector *> ShareData::getAllClassVec() const {
    return this->allClassVec;
}

/**
 * Setter for the classified vectors vector
 * @param allClsVec - vector that holds all the classified vectors
 */
void ShareData::setAllClassVec(vector<classifiedVector *> allClsVec) {
    this->allClassVec = std::move(allClsVec);
}

/**
 * Getter for the unclassified vectors vector
 * @return vector that holds all the unclassified vectors
 */
vector<classifiedVector *> ShareData::getAllUnClassVec() const {
    return this->allUnClassVec;
}

/**
 * Setter for the unclassified vectors vector
 * @param allUnClsVec - vector that holds all the unclassified vectors
 */
void ShareData::setAllUnClassVec(vector<classifiedVector *> allUnClsVec) {
    this->allUnClassVec = std::move(allUnClsVec);
}

/**
 * Getter for a vector for flags of execute commands
 * @return - the vector
 */
vector<int> ShareData::getOptions() const {
    return this->options;
}

/**
 * Setter to turn on and off the flag of execute command
 * @param i - the index in the vector
 * @param n - on and off number (0 or 1)
 */
void ShareData::setOptions(int i, int n) {
    this->options[i] = n;
}

/**
 * This function creates the connection to the client
 * @param sock - socket number
 * @return - return the connection socket number.
 */
int connectToClient(int sock) {
    struct sockaddr_in client_sin;
    unsigned int addr_len = sizeof(client_sin);
    int client_sock = accept(sock, (struct sockaddr *) &client_sin, &addr_len);
    if (client_sock < 0) {
        cout << "error accepting client" << endl;
        exit(1);
    }
    return client_sock;
}