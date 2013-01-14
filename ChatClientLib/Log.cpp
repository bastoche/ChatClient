#include "Log.h"
#include <iostream>

static const bool LOG_ENABLED = false;
static const bool ERROR_ENABLED = true;

void log(const char* message) {	
	if (LOG_ENABLED) {
		std::cout << message << std::endl;
	}
}

void error(const char* message) {
	if (ERROR_ENABLED) {
		std::cerr << message << std::endl;
	}
}

