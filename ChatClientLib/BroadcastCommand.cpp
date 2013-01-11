#include "BroadcastCommand.h"
#include <iostream>

using namespace std;

BroadcastCommand::~BroadcastCommand() {}

void BroadcastCommand::setMessage(const char* message) {
	const size_t messageLength = strlen(message); 
	const size_t cappedMessageLength = min(messageLength, MAX_BODY_LENGTH - 1);
	setBody(message, cappedMessageLength);
	setBodyLength(cappedMessageLength);
	encodeHeader();
}

const char* BroadcastCommand::getMessage() {
	// will change if we introduce the command code
	return getBody();
}
