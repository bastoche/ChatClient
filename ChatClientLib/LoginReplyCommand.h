#include "ChatCommand.h"
#include <string>

#pragma once

class LoginReplyCommand : public ChatCommand {
public:		
	LoginReplyCommand(std::string success, std::string login);
	virtual ~LoginReplyCommand();

	bool getSuccess() const;
	std::string getLogin() const;

	virtual void display() const;
private:
	std::string m_success;
	std::string m_login;

	virtual std::string toString() const;
};