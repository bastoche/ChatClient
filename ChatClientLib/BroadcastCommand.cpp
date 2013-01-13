#include "BroadcastCommand.h"
#include <iostream>
#include <string>

using namespace std;

BroadcastCommand::BroadcastCommand(string message) : m_message(message) {}

BroadcastCommand::~BroadcastCommand() {}

string BroadcastCommand::getMessage() const { return m_message; }

size_t BroadcastCommand::serialize(char* buffer) const {
	string data;
	data += BROADCAST;
	data += DELIMITER;
	data += m_message;
	const size_t length = data.length();
	memcpy(buffer, data.c_str(), length);
	return length;
}

void BroadcastCommand::display() const{
	cout << m_message << endl;
}