#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include "server.h"
#include "../configurations/slack_configuration.h"
#include "../handlers/slack_handler.h"
#include "../handlers/stdout_handler.h"

bool Server::authenticate(Authentication *authentication) {
    for (auto &handler : this->configuration()->get_handlers()) {
        auto auth = handler.first;
        if (*auth == *authentication) {
            return true;
        }
    }
    return false;
}

void Server::handle(SmtpMessage *message) {

//    this->handler->handle(message);
}