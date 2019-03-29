/**
 * Copyright (c) 2019 - Pieter De Clercq. All rights reserved.
 *
 * https://github.com/thepieterdc/mailbridge/
 */

#ifndef MAILBRIDGE_UTIL_CONFIGURATION_H
#define MAILBRIDGE_UTIL_CONFIGURATION_H

#include <cstdint>
#include <string>

/**
 * Application configuration.
 */
class Configuration {
private:
    std::string name;
    std::uint_fast16_t port;
public:
    /**
     * Configuration constructor.
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

#endif /* MAILBRIDGE_UTIL_CONFIGURATION_H */