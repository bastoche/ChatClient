#include "ChatCommand.h"
#include <string>

#pragma once

class WhisperCommand : public ChatCommand {
public:		
	WhisperCommand(std::string message, std::string source, std::string dest);
	virtual ~WhisperCommand();
	
	virtual void display() const;
private:
	std::string m_message;
	std::string m_source;
	std::string m_dest;

	virtual std::string toString() const;
};