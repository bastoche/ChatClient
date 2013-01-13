#include "ChatCommand.h"
#include <string>

#pragma once

class BroadcastCommand : public ChatCommand {
public:		
	BroadcastCommand(std::string message);
	virtual ~BroadcastCommand();

	std::string getMessage() const;

	virtual size_t serialize(char* buffer) const;

	virtual void display() const;
private:
	std::string m_message;
};