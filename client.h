#ifndef YOAV_ROY_ASS3_REPO_CLIENT_H
#define YOAV_ROY_ASS3_REPO_CLIENT_H

#include <string>
#include "validations.h"

using namespace std;

bool check_valid_part_ip(char *partIp);

bool check_valid_ip(char *ip);

bool check_valid_port(char *port);

void sendVector(string ip, int port);

bool sendToServer(int sock, string userInput);

bool receiveFromServer(int sock, string &s);

#endif //YOAV_ROY_ASS3_REPO_CLIENT_H
