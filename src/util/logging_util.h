/**
 * Copyright (c) 2019 - Pieter De Clercq. All rights reserved.
 * 
 * https://github.com/thepieterdc/mailbridge/
 */

#ifndef MAILBRIDGE_UTIL_LOGGING_UTIL_H
#define MAILBRIDGE_UTIL_LOGGING_UTIL_H

#include <string>

/**
 * Logs an informational message.
 *
 * @param msg the message contents
 */
void log_info(const std::string &msg);

/**
 * Throws an error message.
 *
 * @param msg the message contents
 */
void throw_error(const std::string &msg);

#endif /* MAILBRIDGE_UTIL_LOGGING_UTIL_H */
