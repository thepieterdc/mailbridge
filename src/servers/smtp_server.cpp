#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include "smtp_server.h"
#include "threads/smtp_thread.h"

void SmtpServer::accept_client(int socket) {
    SmtpThread client(*this, socket);
    client.greet();

    while (client.is_active()) {
        std::string line = client.receive();
        std::string command = line.substr(0, 4);

        if (command == "AUTH") {
            client.handle_auth();
        }

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
        else if (command == "HELO" || command == "EHLO") {
            client.handle_helo();
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
        else {
            std::cerr << "Unknown command: " << command << std::endl;
            close(socket);
            break;
        }
    }

//    // 11 is strlen(\r\nSubject: )
//    std::string subject_start(data.substr(data.find("\r\nSubject: ") + 11));
//    std::string subject(subject_start.substr(0, subject_start.find("\r\n")));
//
//    std::string message_start(subject_start.substr(subject_start.find("\r\n\r\n") + 4));
//    std::string message(message_start.substr(0, message_start.length() - 2));
//    std::cout << data << std::endl;
}