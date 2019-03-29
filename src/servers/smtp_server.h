/**
 * Copyright (c) 2019 - Pieter De Clercq. All rights reserved.
 *
 * https://github.com/thepieterdc/mailbridge/
 */

#ifndef MAILBRIDGE_SERVERS_SMTP_SERVER_H
#define MAILBRIDGE_SERVERS_SMTP_SERVER_H

#include "server.h"
#include "../messages/smtp_message.h"

/**
 * SMTP server.
 */
class SmtpServer : public Server {
private:
    /**
     * Handles the HELO/EHLO command.
     *
     * @param client the client socket
     * @return the client helo name
     */
    std::string handle_helo(int client, std::string data);

    /**
     * Greets the client.
     *
     * @param client the client socket
     */
    void send_greet(int client);

public:
    /**
     * SmtpServer constructor.
     *
     * @param config the configuration to use
     */
    explicit SmtpServer(const Configuration &config) : Server(config) {};

    /**
     * SmtpServer destructor.
     */
    ~SmtpServer() override = default;

    void accept_client(int socket) override;
};

#endif /* MAILBRIDGE_SERVERS_SMTP_SERVER_H */