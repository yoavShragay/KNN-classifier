
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <vector>
#include <sstream>
#include <fstream>
#include <thread>
#include "client.h"

#define DELIM "."
#define ERROR "invalid input"

using namespace std;

/**
 * This function converts to string
 * @param a - char* type
 * @param size - int number
 * @return - string
 */
string convertChar(char *a, int size) {
    int i;
    string s = "";
    for (i = 0; i < size; i++) {
        s = s + a[i];
    }
    return s;
}

/**
 * parsing strings with null, and print every part in a new line
 * @param s
 */
void printWithoutNull(string &s) {
    string str = s, word;
    s = "\0";
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == NULL) {
            if (s != "") {
                cout << s << "\n";
            }
            s = "\0";
        } else {
            s += str[i];
        }
    }
    if (s != "") {
        cout << s << "\n";
    }
    if (str[str.length() - 1] == NULL) {
        s = "";
    }
}

/**
 * This function checks if the string contains NULL
 * @param s - string
 * @return - true if contains NULL, false otherwise
 */
bool checkNull(string s) {
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == NULL) {
            return true;
        }
    }
    return false;
}

/**
 * Check if every part of the ip (separated by a dot) is valid (e.g. 192.68.24.1)
 * @param partIp - a part of the full ip number
 * @return true of its a valid number, and false otherwise.
 */
bool check_valid_part_ip(char *partIp) {
    size_t len = strlen(partIp);
    // if the length is bigger than 3, invalid input.
    // if the length is 2 or 3 but the first char is 0 (e.g. 001 / 00), invalid input.
    if (len > 3 || (len > 1 && partIp[0] == '0')) {
        return false;
    }
    // if the char in ascii is less than 0 or more than 9, invalid input
    for (int i = 0; i < len; i++) {
        if (partIp[i] < '0' || partIp[i] > '9') {
            return false;
        }
    }
    int num = stoi(partIp);
    // if the number is between 0 and 255, it's a valid input
    if (num >= 0 && num <= 255) {
        return true;
    }
    return false;
}

/**
 * Check if the given ip number is valid
 * @param ip - ip number
 * @return true of its a valid ip number, and false otherwise.
 */
bool check_valid_ip(char *ip) {
    // if the string is empty, invalid input
    if (ip == nullptr) {
        return false;
    }
    int count_dot = 0;
    for (int i = 0; i < strlen(ip); ++i) {
        if (ip[i] == '.') {
            count_dot++;
        }
    }
    // if there are more than 3 dots, invalid input
    if (count_dot != 3) {
        return false;
    }
    // parse the ip
    char *ipSplit = strtok(ip, DELIM);
    if (ipSplit == nullptr) {
        return false;
    }
    while (ipSplit) {
        // check if the number is valid
        if (check_valid_part_ip(ipSplit)) {
            // if so, continue to the next part - parse the remaining ip
            ipSplit = strtok(nullptr, DELIM);
        } else {
            return false;
        }
    }
    return true;
}

/**
 * Check if the port is a valid number
 * @param port - port number
 * @return true if this is a valid port number, false otherwise.
 */
bool check_valid_port(char *port) {
    // if the string is empty, invalid input
    if (port == nullptr) {
        return false;
    }
    size_t len = strlen(port);
    // if the port is 0 or starting with a 0, invalid input
    if (port[0] == '0') {
        return false;
    }
    // if the char in ascii is less than 0 or more than 9, invalid input
    for (int i = 0; i < len; ++i) {
        if (port[i] < '0' || port[i] > '9') {
            return false;
        }
    }
    int numPort = stoi(port);

    // if the port not between 0 and 65535, invalid input
    if (numPort < 0 || numPort > 65535) {
        return false;
    }
    return true;
}

/**
 * This function prints "connection problem"
 */
void connectionProblem() {
    cout << "connection problem" << endl;
}

/**
 * This function reads the information in the file and creates a string of the information
 * @param file_name - a files path
 * @param s - string of the information
 * @return - string of information
 */
bool fileToString(string &file_name, string &s) {
    string line;
    fstream file(file_name, ios::in);
    if (file.is_open()) {
        while (getline(file, line,'\r')) {
            s += line;
        }
        for(int i=0;i<s.length();i++){
            if(s[i]=='\n'){
                s[i]='@';
            }
        }
        s.append("@");
    } else {
        return false;
    }
    return true;
}

/**
 * This function handles the update command
 * @param sock - number of socket
 */
void case1(int sock) {
    int flag = 0;
    string userInput = "1";
    string s, tempInput;
    while (true) {
        // getting the input from the user
        if (flag == 1 || flag == 3) {
            tempInput = "\0";
            getline(cin, userInput);
            bool isPath = fileToString(userInput, tempInput);
            if (isPath) {
                if (!sendToServer(sock, tempInput)) {
                    connectionProblem();
                    break;
                }
            } else {
                cout << "invalid path\n";
                userInput = "invalid path";
                if (!sendToServer(sock, userInput)) {
                    connectionProblem();
                    break;
                }
                return;
            }
            userInput = tempInput;
        } else if (flag != 2) {
            if (!sendToServer(sock, userInput)) {
                connectionProblem();
                break;
            }
        }

        s = "\0";
        // receive
        if (!receiveFromServer(sock, s)) {
            connectionProblem();
            break;
        }
        if (checkNull(s)) {
            if (s.length() >= 3) {
                if (s[0] == '%') {
                    cout << "The lengths of the vectors is not equal" << "\n";
                    return;
                }
            }
            flag++;
            printWithoutNull(s);
        } else {
            if (s == "%%%") {
                cout << "The lengths of the vectors is not equal" << "\n";
                return;
            }
            cout << s << endl;
        }
        flag++;
        if (flag >= 4) {
            return;
        }
    }
}

/**
 * sending to server the data
 * @param sock
 * @param userInput
 * @return true if the sendnig was succsecfull
 */
bool sendToServer(int sock, string userInput) {
    userInput += '$';
    size_t data_len = userInput.length();
    char vectorArr[userInput.length() + 1];
    strcpy(vectorArr, userInput.c_str());
    int sent_bytes = send(sock, vectorArr, data_len, 0);
    if (sent_bytes < 0) {
        return false;
    }
    return true;
}


/**
 * recive the data from the server
 * @param sock
 * @param s
 * @return
 */
bool receiveFromServer(int sock, string &s) {
    char buffer[4096] = "\0";
    int expected_data_len = sizeof(buffer);
    int read_bytes = recv(sock, buffer, expected_data_len, 0);
    if (read_bytes == 0) {
        return false;
    } else if (read_bytes < 0) {
        return false;
    }
    s = convertChar(buffer, read_bytes - 1);
    return true;
}

/**
 * This function takes a string and puts the information in a new file
 * @param allData - string of information
 * @param path - path of a new file
 */
void uploadToFile(string allData, string path) {
    int i = 0;
    allData += "$";
    // Create and open a text file
    ofstream MyFile(path);
    while (allData[i] != '$') {
        string newLine;
        while (allData[i] != '@') {
            newLine += allData[i];
            i++;
        }
        // Write to the file
        MyFile << newLine << endl;
        i++;
    }
    MyFile.close();
}

/**
 * This function handles the download command
 * @param sock - number of socket
 */
void case5(int sock) {
    string s, allData;
    sendToServer(sock, "5");
    while (true) {
        // receive
        s = "\0";
        if (!receiveFromServer(sock, s)) {
            connectionProblem();
            break;
        }
        if (s == "please upload data." || s == "please classify the data.") {
            cout << s << endl;
            return;
        }
        if (s == "") {
            string path;
            getline(cin, path);
            thread t = thread(uploadToFile, allData, path);
            t.detach();
            return;
        }
        if (checkNull(s)) {
            string str = s, word;
            s = "\0";
            for (int i = 0; i < str.length(); i++) {
                if (str[i] == NULL) {
                    allData += s;
                    allData += "@";
                    s = "\0";
                } else {
                    s += str[i];
                }
            }
            if (s != "") {
                allData += s;
                allData += "@";
            }

            if (str[str.length() - 1] == NULL) {
                s = "";
            }

        } else {
            if (s != "") {
                allData += s;
                allData += "@";
            }
        }
    }
}

/**
 * This function connects between the server and the client
 * Sends the user input to the server and getting the classification
 * @param ip - the ip string
 * @param port - the port number
 */
void sendVector(string ip, int port) {
    char ipArr[ip.length()];
    strcpy(ipArr, ip.c_str());
    bool flag = false;
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("error creating socket");
    }
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(ipArr);
    sin.sin_port = htons(port);
    if (connect(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error connecting to server");
    }
    string s;
    while (true) {
        // receive
        s = "\0";
        if (!receiveFromServer(sock, s)) {
            connectionProblem();
            break;
        }
        if (checkNull(s)) {
            printWithoutNull(s);
        } else {
            if (s != "") {
                cout << s << endl;
            }
        }
        if (s == "") {
            // getting the input from the user
            string userInput;
            getline(cin, userInput);
            if (userInput == "1") {
                case1(sock);
            } else if (userInput == "5") {
                case5(sock);
            } else if (userInput == "8") {
                break;
            } else if (!sendToServer(sock, userInput)) {
                connectionProblem();
                break;
            }
        }
    }
    close(sock);
    return;
}

///**
// * This function is the main function in client
// */
int main(int argc, char *argv[]) {
   const string ip = argv[1];
   if (!check_valid_ip(argv[1])) {
       cout << "Invalid Input" << endl;
       exit(1);
   }
   if (!check_valid_port(argv[2])) {
       cout << "Invalid Input" << endl;
       exit(1);
   }
   const int port_no = stoi(argv[2]);
   sendVector(ip, port_no);
   return 0;
}

// int main(int argc, char *argv[]) {
//     const string ip = "127.0.0.1";
//     const int port = 12347;
//     sendVector(ip, port);
//     return 0;
// }


