
#ifndef SERVER_CPP_CLI_H
#define SERVER_CPP_CLI_H

#include <string>
#include "connectionUtil.h"
#include "command.h"

using namespace std;

class CLI {
private:
    vector<command *> commands;
    DefaultIO *dio;

public:
    explicit CLI(DefaultIO *dio);

    virtual ~CLI();

    void start();

};


#endif //SERVER_CPP_CLI_H
