/**
 * Copyright (c) 2019 - Pieter De Clercq. All rights reserved.
 * 
 * https://github.com/thepieterdc/mailbridge/
 */

#include <sstream>
#include "string_util.h"

std::vector<std::string> *split_string(const std::string& input) {
    auto *ret = new std::vector<std::string>();
    std::string buf;
    std::stringstream ss(input);

    while (ss >> buf) {
        ret->push_back(buf);
    }

    return ret;
}