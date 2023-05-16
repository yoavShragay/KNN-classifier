
#include "command.h"
#include "connectionUtil.h"
#include "validations.h"
#include <iostream>

using namespace std;

// constructors for commands

/**
 * This is the constructor for command - the father class
 * @param dio - DefaultIO object
 * @param description - the description of the command
 */
command::command(DefaultIO *dio, string description) {
    this->dio = dio;
    this->description = description;
}

/**
 * @return - the description of the command
 */
string command::getDes() { return this->description; }

/**
 * This is the constructor for update command
 * @param dio - DefaultIO object
 */
update::update(DefaultIO *dio) : command(dio, "1. upload an unclassified csv data file") {}


/**
 * This is the constructor for algoSettings command
 * @param dio - DefaultIO object
 */
algoSettings::algoSettings(DefaultIO *dio) : command(dio, "2. algorithm settings") {}


/**
 * This is the constructor for classify command
 * @param dio - DefaultIO object
 */
classify::classify(DefaultIO *dio) : command(dio, "3. classify data") {}


/**
 * This is the constructor for results command
 * @param dio - DefaultIO object
 */
results::results(DefaultIO *dio) : command(dio, "4. display results") {}


/**
 * This is the constructor for download command
 * @param dio - DefaultIO object
 */
download::download(DefaultIO *dio) : command(dio, "5. download results") {}


/**
 * This is the constructor for exitProg command
 * @param dio - DefaultIO object
 */
exitProg::exitProg(DefaultIO *dio) : command(dio, "8. exit") {}


// execute for each command

/**
 * This is the execution of update command:
 * the user will be given the option to type a path to his local train and test csv file, and after pressing enter,
 * the client will send the contents of the file to the server. At the end of sending, the server will send
 * Back to the client a "complete Upload" message. if the path is invalid will be printed "input invalid" and return
 * to the main menu.
 * @param data - ShareData object
 */
void update::execute(ShareData *data) {
    string userInput;

    if (data->getOptions()[0] == 1) {
        data->setOptions(2, 0);
    }
    bool valid = true;
    dio->write("Please upload your local train CSV file.");
    userInput = dio->read();
    if (userInput == "invalid path") {
        return;
    }
    data->setClassifiedData(userInput + '$');
    data->setAllClassVec(stringToVec(data->getClassifiedData(), true, valid));
    if (!valid) {
        dio->write("%%%");
        return;
    }
    dio->write("Upload complete.");
    dio->write("Please upload your local test CSV file.");
    userInput = dio->read();
    if (userInput == "invalid path") {
        return;
    }
    data->setUnClassifiedData(userInput + '$');
    data->setAllUnClassVec(stringToVec(data->getUnClassifiedData(), false, valid));
    if (!valid) {
        dio->write("%%%");
        return;
    }
    dio->write("Upload complete.");
    data->setOptions(0, 1);
}

/**
 * This is the execution of algoSettings command:
 * The server will send the current classifier parameter values which is the K parameter value
 * and the current distance meter. If the user presses enter, the parameters must be left unchanged.
 * Otherwise, the user can enter new values separated by a space.
 * @param data - ShareData object
 */
void algoSettings::execute(ShareData *data) {
    dio->write("The current KNN parameters are: K = " + to_string(data->getK()) + ", distance metric = " +
               data->getMetric() + ".");
    int result;
    dio->write("");
    const string userInput = dio->read();

    if (!userInput.empty()) {
        size_t first_index = userInput.find_first_of(' ');
        result = checkAlgoSettingsInput(userInput);
        if (result == 1) {
            dio->write("invalid value for K");
        } else if (result == 2) {
            dio->write("invalid value for metric");
        } else if (result == 3) {
            dio->write("invalid value for K and invalid value for metric");
        } else {
            data->setK(stoi(userInput.substr(0, first_index)));
            data->setMetric(userInput.substr(first_index + 1, userInput.length() - (first_index + 1)));
            data->setOptions(2, 0);
        }
    }
    data->setOptions(1, 1);
}

/**
 * This is the execution of classify command:
 * The server will run the algorithm on the CSV files uploaded earlier. at the end, the server will write
 * "classifying data complete" and we will return to the main menu.
 * If no files have been uploaded yet, print "please upload data."
 * @param data - ShareData object
 */
void classify::execute(ShareData *data) {

    bool valid = true;
    if (data->getOptions()[0] == 0) {
        dio->write("please upload data.");
    } else {
        data->setAllClassVec(stringToVec(data->getClassifiedData(), true, valid));
        data->setAllUnClassVec(stringToVec(data->getUnClassifiedData(), false, valid));
        if (data->getAllClassVec().size() < data->getK()) {
            dio->write("invalid input - k is greater than the number of classified vectors.");
        } else {
            for (int i = 0; i < data->getAllUnClassVec().size(); ++i) {
                data->getAllUnClassVec()[i]->setClass(
                        getClassification(data->getAllClassVec(),
                                          data->getMetric(),
                                          data->getK(),
                                          data->getAllUnClassVec()[i]->getCurrVec()));
            }
            dio->write("classifying data complete.");
            data->setOptions(2, 1);
        }
    }
}

/**
 * This is the execution of results command:
 * The server will return the list of classifications. For all classifications, the printing will be as follows:
 * the number of the line in the test file, tab, the classification and then a line drop.
 * Finally, "Done." will be printed after the user's enter to return to the main menu.
 * @param data - ShareData object
 */
void results::execute(ShareData *data) {

    if (data->getOptions()[0] == 0) {
        dio->write("please upload data.");
    } else if (data->getOptions()[2] == 0) {
        dio->write("please classify the data.");
    } else {
        int i = 1;
        for (auto &clsVec: data->getAllUnClassVec()) {
            dio->write(to_string(i) + "\t" + clsVec->getClass());
            i++;
        }
        dio->write("Done.");
        data->setOptions(3, 1);
    }
}

/**
 * This is the execution of download command:
 * The user will enter a path to create the file locally and there the client will save the results,
 * exactly the same format (without Done).
 * @param data - ShareData object
 */
void download::execute(ShareData *data) {

    if (data->getOptions()[0] == 0) {
        dio->write("please upload data.");
    } else if (data->getOptions()[2] == 0) {
        dio->write("please classify the data.");
    } else {
        int i = 1;
        for (auto &clsVec: data->getAllUnClassVec()) {
            dio->write(to_string(i) + "\t" + clsVec->getClass());
            i++;
        }
        dio->write("");
        data->setOptions(4, 1);
    }
}

/**
 * This is the execution of exit command:
 * The interaction between the server and the client will end
 * @param data - ShareData object
 */
void exitProg::execute(ShareData *data) {}
