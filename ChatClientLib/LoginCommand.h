#include "ChatCommand.h"
#include <string>

#pragma once

class LoginCommand : public ChatCommand {
public:		
	LoginCommand(std::string login);
	virtual ~LoginCommand();

	std::string getLogin() const;

	virtual size_t serialize(char* buffer) const;

	virtual void display() const;
private:
	std::string m_login;
};