
#include "CLI.h"

/**
 * This is the constructor of CLI
 * We fill the vector with all the commands
 * @param dio - DefaultIO object
 */
CLI::CLI(DefaultIO *dio) {
    this->dio = dio;
    commands.push_back(new update(dio));
    commands.push_back(new algoSettings(dio));
    commands.push_back(new classify(dio));
    commands.push_back(new results(dio));
    commands.push_back(new download(dio));
    commands.push_back(new exitProg(dio));
}

/**
 * This is the destructor
 */
CLI::~CLI() {
    for (auto &command: commands) {
        delete command;
    }
}

/**
 * This function starts prints the menu and execute the command based on user input
 */
void CLI::start() {
    string strInput;
    int intInput;
    ShareData data;
    size_t i = 1;
    while (commands[i - 1]->getDes()[0] != '8') {
        dio->write("Welcome to the KNN Classifier Server. Please choose an option:");
        for (auto &command: commands) {
            dio->write(command->getDes());
        }
        dio->write("");
        strInput = dio->read();
        if (strInput[0] >= '1' && strInput[0] <= '5' && strInput.size() == 1) {
            intInput = stoi(strInput);
            commands[intInput - 1]->execute(&data);
            i = intInput;
        } else if (strInput[0] == '8' && strInput.size() == 1) {
            commands[commands.size() - 1]->execute(&data);
            i = commands.size();
        } else {
            dio->write("Invalid input");
        }
    }
}