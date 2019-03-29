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
    SlackConfiguration configuration;
public:
    /**
     * SlackHandler constructor.
     *
     * @param configuration the Slack configuration
     */
    explicit SlackHandler(const SlackConfiguration &configuration) : configuration(configuration) {};

    /**
     * SlackHandler destructor.
     */
    ~SlackHandler() override = default;

    void handle(SmtpMessage message) override;
};

#endif /* MAILBRIDGE_HANDLERS_SLACK_HANDLER_H */