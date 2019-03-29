/**
 * Copyright (c) 2019 - Pieter De Clercq. All rights reserved.
 *
 * https://github.com/thepieterdc/mailbridge/
 */

#include <curl/curl.h>
#include "slack_handler.h"
#include "../util/logging_util.h"

/**
 * Curl writefunction that performs a no-op.
 *
 * @param buffer unused
 * @param size size per member
 * @param nmemb amount of members
 * @param userp unused
 * @return amount of bytes written
 */
size_t write_ignore(void *buffer, size_t size, size_t nmemb, void *userp) {
    return size * nmemb;
}

void SlackHandler::handle(SmtpMessage *message) {
    json data;

    json attachments = json::array();

    json attachment;
    attachment["color"] = "good";
    attachment["fallback"] = "You've got mail!";
    attachment["text"] = "Mail received";

    json fields = json::array();

    json fieldFrom;
    fieldFrom["title"] = "From";
    fieldFrom["value"] = message->get_sender();

    json fieldTo;
    fieldTo["title"] = "To";
    fieldTo["value"] = message->get_receiver();

    json fieldSubject;
    fieldSubject["title"] = "Subject";
    fieldSubject["value"] = message->get_subject();

    json fieldMessage;
    fieldMessage["title"] = "Message";
    fieldMessage["value"] = message->get_message();

    fields.push_back(fieldFrom);
    fields.push_back(fieldTo);
    fields.push_back(fieldSubject);
    fields.push_back(fieldMessage);

    attachment["fields"] = fields;

    attachments.push_back(attachment);

    data["attachments"] = attachments;
    data["channel"] = this->config->get_channel();

    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if (curl != nullptr) {
        res = curl_easy_setopt(curl, CURLOPT_URL, this->config->get_webhook().c_str());
        if (res != CURLE_OK) {
            curl_easy_cleanup(curl);
            throw_error("CURL: Could not set url.");
            exit(1);
        }

        std::string postdata(data.dump());

        res = curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, postdata.length());
        if (res != CURLE_OK) {
            curl_easy_cleanup(curl);
            throw_error("CURL: Could not set post data length.");
            exit(1);
        }

        res = curl_easy_setopt(curl, CURLOPT_COPYPOSTFIELDS, postdata.c_str());
        if (res != CURLE_OK) {
            curl_easy_cleanup(curl);
            throw_error("CURL: Could not set post data.");
            exit(1);
        }

        res = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_ignore);
        if (res != CURLE_OK) {
            curl_easy_cleanup(curl);
            throw_error("CURL: Could not set write function.");
            exit(1);
        }

        struct curl_slist *headers = nullptr;

        headers = curl_slist_append(headers, "Accept: application/json");
        headers = curl_slist_append(headers, "Content-Type: application/json");

        res = curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        if (res != CURLE_OK) {
            curl_slist_free_all(headers);
            curl_easy_cleanup(curl);
            throw_error("CURL: Could not set HTTP headers.");
            exit(1);
        }

        res = curl_easy_perform(curl);

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);

        if (res != CURLE_OK) {
            throw_error("CURL: Could not execute cURL request. Host might be down.");
            exit(1);
        }
    }

    log_info("Handled message using Slack.");
}