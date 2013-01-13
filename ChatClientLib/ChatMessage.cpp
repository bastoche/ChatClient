#include "ChatMessage.h"
#include <iostream>

using namespace std;

ChatMessage::ChatMessage() : m_bodyLength(0) {}    

ChatMessage::~ChatMessage() {}    

const char* ChatMessage::getHeader() { return header(); }

const char* ChatMessage::getBody() { return body(); }

const char* ChatMessage::getData() { return m_data; }

size_t ChatMessage::getBodyLength() { return m_bodyLength; }

size_t ChatMessage::getLength() { return HEADER_LENGTH + m_bodyLength; }

void ChatMessage::setHeader(const char* header) {
	memcpy(m_data, header, HEADER_LENGTH);
}

char* ChatMessage::header() { return m_data; } 


void ChatMessage::setBody(const char* data, size_t length) {
	// using strncpy means that the null termination is put in the body too
	strncpy_s(body(), MAX_BODY_LENGTH, data, length);
}

char* ChatMessage::body() { 
	return m_data + HEADER_LENGTH;
}

void ChatMessage::setBodyLength(size_t length) {
	m_bodyLength = length;
}

// write the body length in the header, formatted as a 4 character string
void ChatMessage::encodeHeader() {		
	// creates an empty array for the 4 characters and the \0
	char header[HEADER_LENGTH + 1] = "";
	sprintf_s(header, HEADER_LENGTH + 1, "%4d", m_bodyLength);
	// copy the header data in our command buffer
	setHeader(header);
}

void ChatMessage::decodeHeader() {
	// copy the header data in a null terminater character buffer
	char header[HEADER_LENGTH + 1] = "";
	strncpy_s(header, HEADER_LENGTH + 1, m_data, HEADER_LENGTH);
	// compute the body length from the header
	setBodyLength(atoi(header));
}

void ChatMessage::display() {
	cout << "unknown command" << endl;
}