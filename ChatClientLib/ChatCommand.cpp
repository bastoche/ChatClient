#include "ChatCommand.h"
#include <iostream>
#include <sstream>
#include <vector>
#include "BroadcastCommand.h"
#include "LoginCommand.h"
#include "LoginReplyCommand.h"

using namespace std;

ChatCommand::~ChatCommand() {}

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
				// TODO : do not allow to send an empty login
				return new LoginCommand("");
			}
		} else if (BROADCAST == commandCode) {
			if (tokens.size() >= 2) {
				return new BroadcastCommand(tokens.at(1));
			} else {
				// TODO : do not allow to send an empty message
				return new BroadcastCommand("");
			}
		} else if (LOGIN_REPLY == commandCode) {
			if (tokens.size() >= 3) {
				return new LoginReplyCommand(tokens.at(1), tokens.at(2));
			} else {
				cerr << "error trying to deserialize login reply" << endl;
				return NULL;
			}
		} else {
			cerr << "unknown command code : " << commandCode << endl;
			return NULL;
		}
	} else {
		cerr << "tried to deserialize empty command" << endl;
		return NULL;
	}
}

const std::string ChatCommand::LOGIN = "login";
const std::string ChatCommand::LOGIN_REPLY = "login_reply";
const std::string ChatCommand::BROADCAST = "broadcast";