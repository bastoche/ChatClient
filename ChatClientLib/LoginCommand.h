#include "ChatCommand.h"
#include <string>

#pragma once

class LoginCommand : public ChatCommand {
public:		
	LoginCommand(std::string login);
	virtual ~LoginCommand();

	std::string getLogin() const;

	virtual void display() const;
private:
	std::string m_login;

	virtual std::string toString() const;
};