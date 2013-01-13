#include "ChatCommand.h"
#include <iostream>
#include <sstream>
#include <vector>
#include "LoginCommand.h"
#include "BroadcastCommand.h"

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
	if (tokens.empty() == false) {
		const string commandCode = tokens.at(0);
		if (commandCode == LOGIN) {
			if (tokens.size() >= 2) {
				return new LoginCommand(tokens.at(1));
			} else {
				// TODO : do not allow to send an empty login
				return new LoginCommand("");
			}
		} else if (commandCode == BROADCAST) {
			if (tokens.size() >= 2) {
				return new BroadcastCommand(tokens.at(1));
			} else {
				// TODO : do not allow to send an empty message
				return new BroadcastCommand("");
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
const std::string ChatCommand::BROADCAST = "broadcast";