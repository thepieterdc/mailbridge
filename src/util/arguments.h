/**
 * Copyright (c) 2019 - Pieter De Clercq. All rights reserved.
 *
 * https://github.com/thepieterdc/mailbridge/
 */

#ifndef MAILBRIDGE_UTIL_ARGUMENTS_H
#define MAILBRIDGE_UTIL_ARGUMENTS_H

#include <string>

/**
 * Commandline arguments.
 */
class Arguments {
private:
    std::string config_file;
public:
    /**
     * Arguments constructor.
     *
     * @param argc argument count
     * @param argv argument vector
     */
    Arguments(int argc, char **argv);

    /**
     * Arguments destructor.
     */
    ~Arguments() = default;

    /**
     * Gets the configuration file.
     *
     * @return the configuration file
     */
    std::string get_config_file() {
        return this->config_file;
    }
};

#endif /* MAILBRIDGE_UTIL_ARGUMENTS_H */