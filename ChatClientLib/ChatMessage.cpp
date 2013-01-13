#include "ChatMessage.h"
#include <iostream>

using namespace std;

ChatMessage::ChatMessage() : m_bodyLength(0) {}    

ChatMessage::~ChatMessage() {}    

const char* ChatMessage::getHeader() const { return m_data; }

const char* ChatMessage::getBody() const { return m_data + HEADER_LENGTH; }

const char* ChatMessage::getData() const { return m_data; }

size_t ChatMessage::getBodyLength() const { return m_bodyLength; }

size_t ChatMessage::getLength() const { return HEADER_LENGTH + m_bodyLength; }

char* ChatMessage::header() { return m_data; } 

char* ChatMessage::body() { return m_data + HEADER_LENGTH; }

void ChatMessage::setBodyLength(size_t length) {
	m_bodyLength = length;
}

// write the body length in the header, formatted as a 4 character string
void ChatMessage::encodeHeader() {		
	// creates an empty array for the 4 characters and the \0
	char temporaryHeader[HEADER_LENGTH + 1] = "";
	sprintf_s(temporaryHeader, HEADER_LENGTH + 1, "%4d", m_bodyLength);
	// copy the header data in the message header
	memcpy(header(), temporaryHeader, HEADER_LENGTH);
}

void ChatMessage::decodeHeader() {
	// copy the header data in a null terminated byte buffer
	char header[HEADER_LENGTH + 1] = "";
	strncpy_s(header, HEADER_LENGTH + 1, m_data, HEADER_LENGTH);
	// compute the body length from the header
	setBodyLength(atoi(header));
}

