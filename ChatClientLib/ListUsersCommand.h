#include "ChatCommand.h"
#include <string>

#pragma once

class ListUsersCommand : public ChatCommand {
public:		
	ListUsersCommand();
	virtual ~ListUsersCommand();

	virtual void display() const;
private:
	virtual std::string toString() const;
};