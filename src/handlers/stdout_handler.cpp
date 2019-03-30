/**
 * Copyright (c) 2019 - Pieter De Clercq. All rights reserved.
 *
 * https://github.com/thepieterdc/mailbridge/
 */

#include <iostream>
#include "stdout_handler.h"
#include "../util/logging_util.h"

void StdoutHandler::handle(SmtpMessage *message) {
    std::cout << "New email message received." << std::endl
              << "From: " << message->get_sender() << std::endl
              << "To: " << message->get_receiver() << std::endl
              << "Subject: " << message->get_subject() << std::endl
              << "Message: " << message->get_message() << std::endl;

    log_info("Handled message using stdout.");
}