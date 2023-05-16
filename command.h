
#ifndef SERVER_CPP_COMMAND_H
#define SERVER_CPP_COMMAND_H

#include <string>
#include "connectionUtil.h"

using namespace std;

/**
 * This is the abstract father-class which holds a description and a DefaultIO
 */
class command {
protected:

    string description;
    DefaultIO *dio;

public:
    command(DefaultIO *dio, string description);

    virtual ~command() = default;

    virtual void execute(ShareData *data) = 0;

    string getDes();

};

/**
 * This is the update class - option 1
 */
class update : public command {

public:
    explicit update(DefaultIO *dio);

    ~update() override = default;

    void execute(ShareData *data) override;

};

/**
 * This is the algoSettings class - option 3
 */
class algoSettings : public command {

public:
    explicit algoSettings(DefaultIO *dio);

    ~algoSettings() override = default;

    void execute(ShareData *data) override;

};

/**
 * This is the classify class - option 3
 */
class classify : public command {

public:
    explicit classify(DefaultIO *dio);

    ~classify() override = default;

    void execute(ShareData *data) override;

};

/**
 * This is the results class - option 4
 */
class results : public command {

public:
    explicit results(DefaultIO *dio);

    ~results() override = default;

    void execute(ShareData *data) override;

};

/**
 * This is the download class - option 5
 */
class download : public command {

public:
    explicit download(DefaultIO *dio);

    ~download() override = default;

    void execute(ShareData *data) override;

};

/**
 * This is the exitProg class - option 8
 */
class exitProg : public command {

public:
    explicit exitProg(DefaultIO *dio);

    ~exitProg() override = default;

    void execute(ShareData *data) override;

};

#endif //SERVER_CPP_COMMAND_H
