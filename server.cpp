#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include "validations.h"
#include "vectorData.h"
#include <thread>
#include "CLI.h"
#include "connectionUtil.h"

#define BUFFERSIZE 4096
#define ERROR "invalid input"

using namespace std;

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
 * making the connection with the server
 * @param port
 * @return the socket
 */
int makeConnection(int port) {
    bool flag = false;
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        cout << "error creating socket" << endl;
        exit(1);
    }
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(port);
    //bind
    if (bind(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        cout << "error binding socket" << endl;
        exit(1);
    }
    if (listen(sock, 5) < 0) {
        cout << "error listening to a socket" << endl;
        exit(1);
    }
    return sock;
}

/**
 * handle a specific thread
 * @param client_sock
 */
void handleThread(int client_sock) {
    SocketIO newSock;
    newSock.setClientSock(client_sock);
    CLI currentCli(&newSock);
    currentCli.start();
    int x = 0;

}

/**
 * sending the clients to threads
 * @param sock
 */
void handleClients(int sock) {
    vector<thread> threadsVector;
    while (true) {
        int client_sock = connectToClient(sock);
        threadsVector.emplace_back(handleThread, client_sock);
        threadsVector.at(threadsVector.size() - 1).detach();
    }
}

/**
 * This is the main function of server
 */
int main(int argc, char *argv[]) {
    //const string file_name = argv[1];
    if (!check_valid_port(argv[1])) {
        cout << "Invalid Input" << endl;
        exit(1);
    }
    const int server_port = stoi(argv[1]);
    int sock = makeConnection(server_port);
    handleClients(sock);
    return 0;
}
