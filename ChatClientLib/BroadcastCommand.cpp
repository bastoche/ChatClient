#include "BroadcastCommand.h"
#include <iostream>

using namespace std;

void BroadcastCommand::setMessage(const char* message) {
	const int cappedMessageLength = min(strlen(message), maxBodyLength);
	strncpy_s(body(), maxBodyLength, message, cappedMessageLength);
	setBodyLength(cappedMessageLength);
	encodeHeader();
}
