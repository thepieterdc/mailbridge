/**
 * Copyright (c) 2019 - Pieter De Clercq. All rights reserved.
 *
 * https://github.com/thepieterdc/mailbridge/
 */

#ifndef MAILBRIDGE_CONFIGURATIONS_SLACK_CONFIGURATION_H
#define MAILBRIDGE_CONFIGURATIONS_SLACK_CONFIGURATION_H

#include <cstdint>
#include <json.hpp>
#include <string>
#include <utility>

using json = nlohmann::json;

/**
 * Configuration for a Slack handler.
 */
class SlackConfiguration {
private:
    std::string channel;
    std::string team;
    std::string webhook;
public:
    /**
     * SlackConfiguration constructor.
     *
     * @param channel the channel
     * @param team the team
     * @param webhook the webhook url
     */
    SlackConfiguration(std::string channel, std::string team, std::string webhook) :
            channel(std::move(channel)), team(std::move(team)), webhook(std::move(webhook)) {};

    /**
     * SlackConfiguration destructor.
     */
    ~SlackConfiguration() = default;

    /**
     * Gets the Slack channel name.
     *
     * @return channel name
     */
    std::string get_channel() {
        return this->channel;
    }

    /**
     * Gets the Slack team name.
     *
     * @return team name
     */
    std::string get_team() {
        return this->team;
    }

    /**
     * Gets the Slack webhook url.
     *
     * @return webhook url
     */
    std::string get_webhook() {
        return this->webhook;
    }

    /**
     * Parses the given json configuration to a SlackConfiguration instance.
     *
     * @param config the configuration to parse
     * @return the parsed configuration
     */
    static SlackConfiguration parse(json config);
};

#endif /* MAILBRIDGE_CONFIGURATIONS_SLACK_CONFIGURATION_H */