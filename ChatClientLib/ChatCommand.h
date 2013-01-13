#include <string>

#pragma once

class ChatMessage;

// base class representing a command entered by the user in the chat or received from the server
class ChatCommand {
public:
	virtual ~ChatCommand();

	// serialize this command into a byte buffer, returns the length of the serialized data
	virtual size_t serialize(char* buffer) const = 0;

	virtual void display() const = 0;

	static ChatCommand* deserialize(const char* bytes, size_t length);

protected:
	static const char DELIMITER = '\n';
	static const std::string LOGIN;
	static const std::string BROADCAST;
};