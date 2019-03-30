/**
 * Copyright (c) 2019 - Pieter De Clercq. All rights reserved.
 *
 * https://github.com/thepieterdc/mailbridge/
 */

#ifndef MAILBRIDGE_HANDLERS_STDOUT_HANDLER_H
#define MAILBRIDGE_HANDLERS_STDOUT_HANDLER_H

#include "handler.h"
#include "../configurations/slack_configuration.h"
#include "../messages/smtp_message.h"

/**
 * Handles received incoming emails by posting them to stdout.
 */
class StdoutHandler : public Handler {
public:
    /**
     * StdoutHandler constructor.
     */
    StdoutHandler() : Handler() {};

    /**
     * StdoutHandler destructor.
     */
    ~StdoutHandler() override = default;

    void handle(SmtpMessage *message) override;
};

#endif /* MAILBRIDGE_HANDLERS_STDOUT_HANDLER_H */