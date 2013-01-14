#include "ReplyUsersCommand.h"
#include <iostream>
#include <string>

using namespace std;

ReplyUsersCommand::ReplyUsersCommand(string users) : m_users(users) {}

ReplyUsersCommand::~ReplyUsersCommand() {}

void ReplyUsersCommand::display() const{
	cout << "Connected users: " << m_users << "." << endl;
}

string ReplyUsersCommand::toString() const {
	string data;
	data += REPLY_USERS;
	data += DELIMITER;
	data += m_users;
	return data;
}