/**
 * Copyright (c) 2019 - Pieter De Clercq. All rights reserved.
 *
 * https://github.com/thepieterdc/mailbridge/
 */

#ifndef MAILBRIDGE_SERVERS_SMTP_SERVER_H
#define MAILBRIDGE_SERVERS_SMTP_SERVER_H

#include "server.h"
#include "../messages/smtp_message.h"
#include "../handlers/handler.h"

/**
 * SMTP server.
 */
class SmtpServer : public Server {
public:
    /**
     * SmtpServer constructor.
     *
     * @param config the configuration to use
     */
    explicit SmtpServer(Configuration *config) : Server(config) {};

    /**
     * SmtpServer destructor.
     */
    ~SmtpServer() override = default;

    void accept_client(int socket) override;
};

#endif /* MAILBRIDGE_SERVERS_SMTP_SERVER_H */