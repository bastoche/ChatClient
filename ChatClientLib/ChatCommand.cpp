#include "ChatCommand.h"
#include <iostream>
#include <sstream>
#include <vector>
#include "BroadcastCommand.h"
#include "LoginCommand.h"
#include "LoginReplyCommand.h"
#include "Log.h"

using namespace std;

ChatCommand::~ChatCommand() {}

size_t ChatCommand::serialize(char* buffer) const {
	string data = toString();
	const size_t length = data.length();
	memcpy(buffer, data.c_str(), length);
	return length;
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

	// read the first token to get the 
	if (false == tokens.empty()) {
		const string commandCode = tokens.at(0);
		if (LOGIN == commandCode) {
			if (tokens.size() >= 2) {
				return new LoginCommand(tokens.at(1));
			} else {
				error("Tried to deserialize login command with empty login.");
				return NULL;
			}
		} else if (BROADCAST == commandCode) {
			if (tokens.size() >= 2) {
				return new BroadcastCommand(tokens.at(1));
			} else {
				error("Tried to deserialize broadcast command with empty message.");
				return NULL;
			}
		} else if (LOGIN_REPLY == commandCode) {
			if (tokens.size() >= 3) {
				return new LoginReplyCommand(tokens.at(1), tokens.at(2));
			} else {
				error("Error trying to deserialize login reply.");
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

const std::string ChatCommand::LOGIN = "login";
const std::string ChatCommand::LOGIN_REPLY = "login_reply";
const std::string ChatCommand::BROADCAST = "broadcast";