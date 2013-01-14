#include "ChatCommand.h"
#include <string>

#pragma once

class BroadcastCommand : public ChatCommand {
public:		
	BroadcastCommand(std::string message, std::string sender);
	virtual ~BroadcastCommand();

	std::string getMessage() const;	

	virtual void display() const;
private:
	std::string m_message;
	std::string m_sender;

	virtual std::string toString() const;
};