/**
 * Copyright (c) 2019 - Pieter De Clercq. All rights reserved.
 *
 * https://github.com/thepieterdc/mailbridge/
 */

#ifndef MAILBRIDGE_SERVERS_SERVER_H
#define MAILBRIDGE_SERVERS_SERVER_H

#include "../configurations/configuration.h"
#include "../handlers/handler.h"

/**
 * Abstract server.
 */
class Server {
protected:
    Configuration config;
    Handler *handler;
public:
    /**
     * Server constructor.
     *
     * @param config the configuration to use
     */
    explicit Server(const Configuration &config);

    /**
     * Server destructor.
     */
    virtual ~Server() {
        delete this->handler;
    }

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

    /**
     * Handles the given message using the configured handler.
     *
     * @param message the message to handle
     */
    void handle(SmtpMessage *message);
};

#endif /* MAILBRIDGE_SERVERS_SERVER_H */