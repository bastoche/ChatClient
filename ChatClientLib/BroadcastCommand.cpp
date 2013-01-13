#include "BroadcastCommand.h"
#include <iostream>
#include <string>

using namespace std;

BroadcastCommand::BroadcastCommand(string message) : m_message(message) {}

BroadcastCommand::~BroadcastCommand() {}

string BroadcastCommand::getMessage() const { return m_message; }

size_t BroadcastCommand::serialize(char* buffer) const {
	const size_t length = m_message.length();
	memcpy(buffer, m_message.c_str(), length);
	return length;
}

void BroadcastCommand::display() const{
	cout << getMessage() << endl;
}