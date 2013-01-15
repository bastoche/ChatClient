#include <string>

#pragma once

class ChatMessage;

// base class representing a command entered by the user in the chat or received from the server
class ChatCommand {
public:
	virtual ~ChatCommand();

	// serialize this command into a byte buffer, returns the length of the serialized data
	size_t serialize(char* buffer) const;

	// returns the length of this command when it is serialized
	size_t getSerializedLength() const;

	virtual void display() const = 0;

	static ChatCommand* deserialize(const char* bytes, size_t length);

protected:
	// delimiter used when serializing a command into a string
	static const char DELIMITER = '\n';

	// command codes
	static const std::string BROADCAST;
	static const std::string LIST_USERS;	
	static const std::string LOGIN;
	static const std::string LOGIN_REPLY;	
	static const std::string REPLY_USERS;
	static const std::string WHISPER;

private:
	// serialize this command into a string
	virtual std::string toString() const = 0;
};