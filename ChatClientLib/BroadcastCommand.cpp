#include "BroadcastCommand.h"
#include <iostream>
#include <string>

using namespace std;

BroadcastCommand::BroadcastCommand(string message) : m_message(message) {}

BroadcastCommand::~BroadcastCommand() {}

string BroadcastCommand::getMessage() const { return m_message; }

void BroadcastCommand::display() const{
	cout << m_message << endl;
}

string BroadcastCommand::toString() const {
	string data;
	data += BROADCAST;
	data += DELIMITER;
	data += m_message;
	return data;
}