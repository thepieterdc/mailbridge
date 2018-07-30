/**
 * Copyright (c) 2018 - Pieter De Clercq. All rights reserved.
 *
 * https://github.com/thepieterdc/mailbridge/
 */

#include <cstdlib>
#include <netinet/in.h>
#include "util/logging_util.h"

/**
 * Main entry point.
 *
 * @return 0 on success
 */
int main() {
	log_info("Test info");
	throw_error("Test info");
	return EXIT_SUCCESS;
}