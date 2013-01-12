#include "ChatCommand.h"
#include <iostream>

using namespace std;

ChatCommand::ChatCommand() : m_bodyLength(0) {}    

ChatCommand::~ChatCommand() {}    

const char* ChatCommand::getHeader() { return header(); }

const char* ChatCommand::getBody() { return body(); }

const char* ChatCommand::getData() { return m_data; }

size_t ChatCommand::getBodyLength() { return m_bodyLength; }

size_t ChatCommand::getLength() { return HEADER_LENGTH + m_bodyLength; }

void ChatCommand::setHeader(const char* header) {
	memcpy(m_data, header, HEADER_LENGTH);
}

char* ChatCommand::header() { return m_data; } 


void ChatCommand::setBody(const char* data, size_t length) {
	// using strncpy means that the null termination is put in the body too
	strncpy_s(body(), MAX_BODY_LENGTH, data, length);
}

char* ChatCommand::body() { 
	return m_data + HEADER_LENGTH;
}

void ChatCommand::setBodyLength(size_t length) {
	m_bodyLength = length;
}

// write the body length in the header, formatted as a 4 character string
void ChatCommand::encodeHeader() {		
	// creates an empty array for the 4 characters and the \0
	char header[HEADER_LENGTH + 1] = "";
	sprintf_s(header, HEADER_LENGTH + 1, "%4d", m_bodyLength);
	// copy the header data in our command buffer
	setHeader(header);
}

void ChatCommand::decodeHeader() {
	// copy the header data in a null terminater character buffer
	char header[HEADER_LENGTH + 1] = "";
	strncpy_s(header, HEADER_LENGTH + 1, m_data, HEADER_LENGTH);
	// compute the body length from the header
	setBodyLength(atoi(header));
}

void ChatCommand::display() {
	cout << "unknown command" << endl;
}