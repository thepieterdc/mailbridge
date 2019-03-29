/**
 * Copyright (c) 2019 - Pieter De Clercq. All rights reserved.
 *
 * https://github.com/thepieterdc/mailbridge/
 */

#ifndef MAILBRIDGE_SERVERS_SERVER_H
#define MAILBRIDGE_SERVERS_SERVER_H

#include "../util/configuration.h"

/**
 * Abstract server.
 */
class Server {
protected:
    Configuration config;
public:
    /**
     * Server constructor.
     *
     * @param config the configuration to use
     */
    explicit Server(const Configuration &config) : config(config) {};

    /**
     * Server destructor.
     */
    virtual ~Server() = default;

    /**
     * Accepts the client at the given socket.
     *
     * @param socket the client socket
     */
    virtual void accept_client(int socket) = 0;

    /**
     * Gets the server configuration.
     *
     * @return the configuration
     */
    Configuration configuration() {
        return this->config;
    }
};

#endif /* MAILBRIDGE_SERVERS_SERVER_H */