#include "ChatCommand.h"
#include <iostream>

using namespace std;

ChatCommand::ChatCommand() : m_bodyLength(0) {}    

size_t ChatCommand::getBodyLength() { return m_bodyLength; }

char* ChatCommand::body() { 
	return m_data + headerLength;
}

void ChatCommand::setBodyLength(size_t length) {
	m_bodyLength = length;
}

void ChatCommand::encodeHeader() {
	// write the body length in the header, formatted as a 4 digit long string
	sprintf_s(m_data, 4, "%4d", m_bodyLength);
}

void ChatCommand::decodeHeader() {
	char header[headerLength + 1] = "";
	strncpy_s(header, headerLength + 1, m_data, headerLength);
	setBodyLength(atoi(header));
}