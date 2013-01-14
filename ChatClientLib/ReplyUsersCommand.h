#include "ChatCommand.h"
#include <string>

#pragma once

class ReplyUsersCommand : public ChatCommand {
public:		
	ReplyUsersCommand(std::string users);
	virtual ~ReplyUsersCommand();
	
	virtual void display() const;
private:
	std::string m_users;

	virtual std::string toString() const;
};