/**
 * Copyright (c) 2019 - Pieter De Clercq. All rights reserved.
 *
 * https://github.com/thepieterdc/mailbridge/
 */

#ifndef MAILBRIDGE_UTIL_CONFIGURATION_H
#define MAILBRIDGE_UTIL_CONFIGURATION_H

#include <cstdint>
#include <json.hpp>
#include <string>

using json = nlohmann::json;

/**
 * Application configuration.
 */
class Configuration {
private:
    json handler_configuration;
    std::string name;
    std::uint_fast16_t port;
public:
    /**
     * Configuration constructor.
     *
     * @param file the path to the configuration file
     */
    explicit Configuration(const std::string &file);

    /**
     * Configuration destructor.
     */
    ~Configuration() = default;

    /**
     * Gets the handler configuration.
     *
     * @return the handler configuration
     */
    json get_handler_configuration() {
        return this->handler_configuration;
    }

    /**
     * Gets the name of the mailserver.
     *
     * @return the hostname
     */
    std::string get_name() {
        return this->name;
    }

    /**
     * Gets the port the application should listen on.
     *
     * @return the port
     */
    std::uint_fast16_t get_port() {
        return this->port;
    }
};

#endif /* MAILBRIDGE_UTIL_CONFIGURATION_H */