#include "LoginCommand.h"
#include <iostream>

using namespace std;

LoginCommand::LoginCommand(string login) : m_login(login) {}

LoginCommand::~LoginCommand() {}

string LoginCommand::getLogin() const { return m_login; }

size_t LoginCommand::serialize(char* buffer) const {
	string data;
	data += LOGIN;
	data += DELIMITER;
	data += m_login;
	const size_t length = data.length();
	memcpy(buffer, data.c_str(), length);
	return length;
}

void LoginCommand::display() const {
	cout << getLogin() << " vient de se connecter." << endl;
}