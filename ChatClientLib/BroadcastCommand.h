#include "ChatCommand.h"
#include <string>

#pragma once

class BroadcastCommand : public ChatCommand {
public:		
	BroadcastCommand(std::string message, std::string source);
	virtual ~BroadcastCommand();

	std::string getMessage() const;	

	virtual void display() const;
private:
	std::string m_message;
	std::string m_source;

	virtual std::string toString() const;
};