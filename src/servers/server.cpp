#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include "server.h"
#include "../configurations/slack_configuration.h"
#include "../handlers/slack_handler.h"
#include "../handlers/stdout_handler.h"

Server::Server(Configuration *config) : config(config) {
    auto handler_config = config->get_handler_configuration();

    std::string channel = handler_config["channel"].get<std::string>();
    std::string webhook = handler_config["webhook"].get<std::string>();

    auto *slack_configuration = new SlackConfiguration(channel, webhook);

    this->handler = new StdoutHandler();

//    this->handler = new SlackHandler(slack_configuration);
}

void Server::handle(SmtpMessage *message) {
    this->handler->handle(message);
}