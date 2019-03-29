/**
 * Copyright (c) 2019 - Pieter De Clercq. All rights reserved.
 *
 * https://github.com/thepieterdc/mailbridge/
 */

#include <cstdlib>
#include <netinet/in.h>
#include <iostream>
#include <thread>
#include <vector>
#include <cstring>
#include <sstream>
#include <unistd.h>
#include "util/logging_util.h"
#include "util/arguments.h"
#include "configurations/configuration.h"
#include "servers/smtp_server.h"

/**
 * Handles an incoming client.
 *
 * @param srv the server to handle the client on
 * @param client the client socket
 */
void handle_client(Server& srv, int client) {
    log_info("Accepted connection.");
    srv.accept_client(client);
}

/**
 * Main entry point.
 *
 * @param argc argument count
 * @param argv argument vector
 * @return 0 on success
 */
int main(int argc, char **argv) {
    Arguments arguments(argc, argv);

    log_info("Mailbridge version " MAILBRIDGE_VERSION ".");

    Configuration configuration(arguments.get_config_file());

    log_info("Using configuration: " + arguments.get_config_file() + ".");

    int server = socket(AF_INET, SOCK_STREAM, 0);
    if (server < 0) {
        throw_error("Socket initialisation failed.");
        exit(EXIT_FAILURE);
    }

    int reuseaddr_opt = 1;
    if (setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &reuseaddr_opt, sizeof(reuseaddr_opt)) < 0) {
        throw_error("Setting socket option (reuseaddr) failed.");
        exit(EXIT_FAILURE);
    }

    int reuseport_opt = 1;
    if (setsockopt(server, SOL_SOCKET, SO_REUSEPORT, &reuseport_opt, sizeof(reuseport_opt)) < 0) {
        throw_error("Setting socket option (reuseport) failed.");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr = {};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(configuration.get_port());

    if (bind(server, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        throw_error("Binding socket failed.");
        exit(EXIT_FAILURE);
    }

    if (listen(server, 0) < 0) {
        throw_error("Listening socket failed.");
        exit(EXIT_FAILURE);
    }

    log_info("Accepting connections at port " + std::to_string(configuration.get_port()) + ".");

    struct sockaddr_in client_addr = {};
    socklen_t client_addr_len = sizeof(client_addr);

    SmtpServer srv(&configuration);

    while (true) {
        int client = accept(server, (struct sockaddr *) &client_addr, &client_addr_len);
        std::thread client_thread(handle_client, std::ref(srv), client);
        client_thread.detach();
    }
    return EXIT_SUCCESS;
}