#include <sys/socket.h>
#include "smtp_server.h"

/**
 * Receive a line from the client.
 *
 * @param client the client socket
 * @return the data received
 */
inline std::string client_receive(int client) {
    char buffer[1024 + 1] = {0};
    recv(client, &buffer, 1024, 0);
    return std::string(buffer);
}

/**
 * Sends a line to the client.
 *
 * @param client client socket
 * @param data data to send
 */
inline void client_send(int client, const std::string &data) {
    auto length = static_cast<size_t>(data.length());
    send(client, data.c_str(), length, 0);
}

void SmtpServer::accept_client(int socket) {
    this->send_greet(socket);

    std::string data;
    std::string from_addr;
    std::string helo_name;
    std::string to_addr;

    while (true) {
        std::string line = client_receive(socket);
        std::string command = line.substr(0, 4);

//        if (command == "DATA") {
//            client_send(client, "354 Start mail input, finish by sending <CRLF>.<CRLF>\n");
//
//            // read per line
//            char buffer[1024 + 1] = {0};
//            ssize_t buffersize = 0;
//
//            while (true) {
//                if (buffersize == 0) {
//                    buffersize = recv(client, buffer, 1024, 0);
//                }
//
//                if (strcmp(buffer, ".\r\n") == 0) {
//                    break;
//                }
//
//                for (int i = 0; i < buffersize; ++i) {
//                    data += buffer[i];
//                    if (buffer[i] == '\n') {
//                        char remaining[1024 + 1] = {0};
//                        std::copy(buffer + i + 1, buffer + buffersize, remaining);
//                        memcpy(buffer, remaining, 1024);
//                        break;
//                    }
//                }
//            }
//
//            client_send(client, "250 OK\n");
        if (command == "HELO" || command == "EHLO") {
            this->handle_helo()
            helo_name = line.substr(5);
            client_send(client, "250 r2d2.mailbridge.local\n");
        }
//        } else if (command == "MAIL") {
//            size_t startpos = line.find('<');
//            from_addr = line.substr(startpos + 1, line.find('>') - startpos - 1);
//            client_send(client, "250 OK\n");
//        } else if (command == "QUIT") {
//            client_send(client, "221 BYE\n");
//            close(client);
//            break;
//        } else if (command == "RCPT") {
//            size_t startpos = line.find('<');
//            to_addr = line.substr(startpos + 1, line.find('>') - startpos - 1);
//            client_send(client, "250 OK\n");
//        } else {
//            close(client);
//            break;
//        }
    }

//    // 11 is strlen(\r\nSubject: )
//    std::string subject_start(data.substr(data.find("\r\nSubject: ") + 11));
//    std::string subject(subject_start.substr(0, subject_start.find("\r\n")));
//
//    std::string message_start(subject_start.substr(subject_start.find("\r\n\r\n") + 4));
//    std::string message(message_start.substr(0, message_start.length() - 2));
//    std::cout << data << std::endl;
}

void SmtpServer::send_greet(int client) {
    client_send(client, "220" + this->config.get_name() + "\n");
}