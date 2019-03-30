/**
 * Copyright (c) 2019 - Pieter De Clercq. All rights reserved.
 *
 * https://github.com/thepieterdc/mailbridge/
 */

#ifndef MAILBRIDGE_HANDLERS_SLACK_HANDLER_H
#define MAILBRIDGE_HANDLERS_SLACK_HANDLER_H

#include "handler.h"
#include "../configurations/slack_configuration.h"
#include "../messages/smtp_message.h"

/**
 * Handles received incoming emails by sending them to a Slack channel.
 */
class SlackHandler : public Handler {
private:
    SlackConfiguration *config;
public:
    /**
     * SlackHandler constructor.
     *
     * @param configuration the Slack configuration
     */
    explicit SlackHandler(SlackConfiguration *configuration) : Handler(), config(configuration) {};

    /**
     * SlackHandler destructor.
     */
    ~SlackHandler() override {
        delete this->config;
    }

    void handle(SmtpMessage *message) override;
};

#endif /* MAILBRIDGE_HANDLERS_SLACK_HANDLER_H */