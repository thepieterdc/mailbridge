/**
 * Copyright (c) 2018 - Pieter De Clercq. All rights reserved.
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

/**
 * Receive a line from the client.
 *
 * @param client the client socket
 * @return the data received
 */
std::string client_receive(int client) {
	char buffer[1024 + 1] = {0};

	recv(client, &buffer, 1024, 0);

	return std::string(buffer);
}

void client_send(int client, const std::string &data) {
	auto length = static_cast<size_t>(data.length());

	char buffer[length + 1] = {0};
	strcpy(buffer, data.c_str());
	send(client, buffer, length, 0);
}

/**
 * SMTP thread.
 *
 * @param client client socket
 */
void smtp_thread(int client) {
	// Greet
	client_send(client, "220 r2d2.mailbridge.local\n");

	std::string data;
	std::string from_addr;
	std::string helo_name;
	std::string to_addr;

	while (true) {
		std::string line = client_receive(client);
		std::string command = line.substr(0, 4);

		if (command == "DATA") {
			client_send(client, "354 Start mail input, finish by sending <CRLF>.<CRLF>\n");

			// read per line
			char buffer[1024 + 1] = {0};
			ssize_t buffersize = 0;

			while (true) {
				if (buffersize == 0) {
					buffersize = recv(client, buffer, 1024, 0);
				}

				if (strcmp(buffer, ".\r\n") == 0) {
					break;
				}

				for (int i = 0; i < buffersize; ++i) {
					data += buffer[i];
					if (buffer[i] == '\n') {
						char remaining[1024 + 1] = {0};
						std::copy(buffer + i + 1, buffer + buffersize, remaining);
						memcpy(buffer, remaining, 1024);
						break;
					}
				}
			}

			client_send(client, "250 OK\n");
		} else if (command == "HELO" || command == "EHLO") {
			helo_name = line.substr(5);
			client_send(client, "250 r2d2.mailbridge.local\n");
		} else if (command == "MAIL") {
			size_t startpos = line.find('<');
			from_addr = line.substr(startpos + 1, line.find('>') - startpos - 1);
			client_send(client, "250 OK\n");
		} else if (command == "QUIT") {
			client_send(client, "221 BYE\n");
			close(client);
			break;
		} else if (command == "RCPT") {
			size_t startpos = line.find('<');
			to_addr = line.substr(startpos + 1, line.find('>') - startpos - 1);
			client_send(client, "250 OK\n");
		} else {
			close(client);
			break;
		}
	}

	// 11 is strlen(\r\nSubject: )
	std::string subject_start(data.substr(data.find("\r\nSubject: ") + 11));
	std::string subject(subject_start.substr(0, subject_start.find("\r\n")));

	std::string message_start(subject_start.substr(subject_start.find("\r\n\r\n") + 4));
	std::string message(message_start.substr(0, message_start.length() - 2));
	std::cout << data << std::endl;
}

/**
 * Main entry point.
 *
 * @return 0 on success
 */
int main() {
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
	server_addr.sin_port = htons(1025);

	if (bind(server, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
		throw_error("Binding socket failed.");
		exit(EXIT_FAILURE);
	}

	if (listen(server, 0) < 0) {
		throw_error("Listening socket failed.");
		exit(EXIT_FAILURE);
	}

	log_info("SMTP server accepting connections at port 1025.");

	struct sockaddr_in client_addr = {};
	socklen_t client_addr_len = sizeof(client_addr);

	while (true) {
		int client = accept(server, (struct sockaddr *) &client_addr, &client_addr_len);

		log_info("Accepted connection.");

		std::thread client_thread(smtp_thread, client);
		client_thread.detach();
	}
	return EXIT_SUCCESS;
}