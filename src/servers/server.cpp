#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include "server.h"
#include "../configurations/slack_configuration.h"
#include "../handlers/slack_handler.h"
#include "../handlers/stdout_handler.h"

void Server::handle(SmtpMessage *message) {
//    this->handler->handle(message);
}