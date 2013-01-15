#include "ChatCommand.h"
#include <iostream>
#include <sstream>
#include <vector>
#include "Log.h"
#include "BroadcastCommand.h"
#include "ListUsersCommand.h"
#include "LoginCommand.h"
#include "LoginReplyCommand.h"
#include "ReplyUsersCommand.h"
#include "WhisperCommand.h"


using namespace std;

ChatCommand::~ChatCommand() {}

size_t ChatCommand::serialize(char* buffer) const {
	string data = toString();
	const size_t length = data.length();
	memcpy(buffer, data.c_str(), length);
	return length;
}

// returns the length of this command when it is serialized
size_t ChatCommand::getSerializedLength() const {
	return toString().length();
}


ChatCommand* ChatCommand::deserialize(const char* bytes, size_t length) {
	// interpret the bytes as a string sequence, and split it into a string vector
	string data(bytes, length);
	stringstream dataAsStream(data);	
	vector<string> tokens;
	string token;

	while(getline(dataAsStream, token, DELIMITER)) {
		tokens.push_back(token);
	}

	// read the first token to determine the command class to instantiate, interpret the other tokens as constructor parameters
	if (false == tokens.empty()) {
		const string commandCode = tokens.at(0);
		if (BROADCAST == commandCode) {
			if (tokens.size() >= 3) {
				return new BroadcastCommand(tokens.at(1), tokens.at(2));
			} else {
				error("Malformed broadcast command.");
				return NULL;
			}
		} else if (LOGIN_REPLY == commandCode) {
			if (tokens.size() >= 3) {
				return new LoginReplyCommand(tokens.at(1), tokens.at(2));
			} else {
				error("Malformed login reply command.");
				return NULL;
			}
		} else if (REPLY_USERS == commandCode) {
			if (tokens.size() >= 2) {
				return new ReplyUsersCommand(tokens.at(1));
			} else {
				error("Malformed login reply command.");
				return NULL;
			}
		} else if (WHISPER == commandCode) {
			if (tokens.size() >= 3) {
				return new WhisperCommand(tokens.at(1), tokens.at(2), tokens.at(3));
			} else {
				error("Malformed login reply command.");
				return NULL;
			}
		} else {
			error("Unknown command code.");
			return NULL;
		}
	} else {
		error("Tried to deserialize an empty command");
		return NULL;
	}
}

const std::string ChatCommand::BROADCAST = "broadcast";
const std::string ChatCommand::LIST_USERS = "list_users";
const std::string ChatCommand::LOGIN = "login";
const std::string ChatCommand::LOGIN_REPLY = "login_reply";
const std::string ChatCommand::REPLY_USERS = "reply_users";
const std::string ChatCommand::WHISPER = "whisper";
