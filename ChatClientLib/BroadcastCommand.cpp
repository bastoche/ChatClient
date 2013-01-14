#include "BroadcastCommand.h"
#include <iostream>
#include <string>

using namespace std;

BroadcastCommand::BroadcastCommand(string message, string source) : m_message(message), m_source(source) {}

BroadcastCommand::~BroadcastCommand() {}

string BroadcastCommand::getMessage() const { return m_message; }

void BroadcastCommand::display() const{
	cout << "<" << m_source << "> says: " << m_message << endl;
}

string BroadcastCommand::toString() const {
	string data;
	data += BROADCAST;
	data += DELIMITER;
	data += m_message;
	data += DELIMITER;
	data += m_source;
	return data;
}