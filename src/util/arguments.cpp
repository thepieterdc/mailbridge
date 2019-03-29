/**
 * Copyright (c) 2019 - Pieter De Clercq. All rights reserved.
 *
 * https://github.com/thepieterdc/mailbridge/
 */

#include <getopt.h>
#include "arguments.h"

#define CONFIG_FILE_DEFAULT "conf/configuration.default.json"

const char *const short_opts = "f:";

const option long_opts[] = {
        {"configuration", optional_argument, nullptr, 0}
};

Arguments::Arguments(int argc, char **argv) : config_file(CONFIG_FILE_DEFAULT) {
    while (true) {
        const auto opt = getopt_long(argc, argv, short_opts, long_opts, nullptr);

        if (opt == -1) {
            break;
        }

        switch (opt) {
            case 'f':
                this->config_file = std::string(optarg);
                break;

            default:
                break;
        }
    }
}