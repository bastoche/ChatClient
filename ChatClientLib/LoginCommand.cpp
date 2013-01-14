#include "LoginCommand.h"
#include <iostream>

using namespace std;

LoginCommand::LoginCommand(string login) : m_login(login) {}

LoginCommand::~LoginCommand() {}

string LoginCommand::getLogin() const { return m_login; }

void LoginCommand::display() const {
	cout << "Trying to log in as : " << m_login << endl;
}

string LoginCommand::toString() const {
	string data;
	data += LOGIN;
	data += DELIMITER;
	data += m_login;
	return data;
}