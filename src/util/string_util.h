/**
 * Copyright (c) 2019 - Pieter De Clercq. All rights reserved.
 * 
 * https://github.com/thepieterdc/mailbridge/
 */

#ifndef MAILBRIDGE_UTIL_STRING_UTIL_H
#define MAILBRIDGE_UTIL_STRING_UTIL_H

#include <string>
#include <vector>

/**
 * Splits a string by spaces.
 *
 * @param input the input string to split
 * @return the parts of the string
 */
std::vector<std::string> *split_string(const std::string& input);

#endif /* MAILBRIDGE_UTIL_STRING_UTIL_H */
