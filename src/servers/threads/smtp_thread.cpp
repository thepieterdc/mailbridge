/**
 * Copyright (c) 2019 - Pieter De Clercq. All rights reserved.
 *
 * https://github.com/thepieterdc/mailbridge/
 */

#include <string>
#include <sys/socket.h>
#include "smtp_thread.h"

void SmtpThread::client_send(const std::string &data) {
    auto length = static_cast<size_t>(data.length());
    send(this->client_fd, data.c_str(), length, 0);
}

void SmtpThread::greet() {
    client_send("220 " + this->server.configuration().get_name() + "\n");
}

void SmtpThread::handle_auth() {
    // Ignore authentication for now.
    client_send("235 2.7.0  Authentication Succeeded\n");
}

void SmtpThread::handle_helo() {
    this->helo_name = this->last_line.substr(5);
    client_send("250 " + this->server.configuration().get_name() + "\n");
}



std::string SmtpThread::receive() {
    char buffer[1024 + 1] = {0};
    recv(this->client_fd, &buffer, 1024, 0);
    this->last_line = std::string(buffer);
    return this->last_line;
}