#include "WhisperCommand.h"
#include <iostream>
#include <string>

using namespace std;

WhisperCommand::WhisperCommand(string message, string source, string dest) : m_message(message), m_source(source), m_dest(dest) {}

WhisperCommand::~WhisperCommand() {}

void WhisperCommand::display() const{
	cout << "<" << m_source << "> whispers: " << m_message << endl;
}

string WhisperCommand::toString() const {
	string data;
	data += WHISPER;
	data += DELIMITER;
	data += m_message;
	data += DELIMITER;
	data += m_source;
	data += DELIMITER;
	data += m_dest;
	return data;
}