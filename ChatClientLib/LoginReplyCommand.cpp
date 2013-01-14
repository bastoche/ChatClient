#include "LoginReplyCommand.h"
#include <iostream>

using namespace std;

LoginReplyCommand::LoginReplyCommand(std::string success, std::string login) : m_success(success), m_login(login) {}

LoginReplyCommand::~LoginReplyCommand() {}

bool LoginReplyCommand::getSuccess() const { return ("true" == m_success); }

string LoginReplyCommand::getLogin() const { return m_login; }

void LoginReplyCommand::display() const {
	if (getSuccess()) {
		cout << "You are now logged in as " << m_login << "." << endl;
	} else {
		cout << "Unable to log in as " << m_login << ", please try another name." << endl;
	}
}

string LoginReplyCommand::toString() const {
	string data;
	data += LOGIN_REPLY;
	data += DELIMITER;
	data += m_success;
	data += DELIMITER;
	data += m_login;
	return data;
}
