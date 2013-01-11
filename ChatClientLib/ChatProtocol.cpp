#include "ChatProtocol.h"
#include <iostream>
#include "BroadcastCommand.h"
#include "SocketWrapper.h"

using namespace std;

ChatCommand* ChatProtocol::buildBroadcastCommand(const char* message) {
	BroadcastCommand* command = new BroadcastCommand();
	command->setMessage(message);
	return command;
}

ChatCommand* ChatProtocol::unmarshallCommand(SocketWrapper* socketWrapper) {
	// read the header
	cout << "read header" << endl;
	ChatCommand command;
	if (socketWrapper->receiveData(command.header(), ChatCommand::HEADER_LENGTH)) {
		// read the body
		cout << "read body" << endl;
		command.decodeHeader();
		if (socketWrapper->receiveData(command.body(), ChatCommand::MAX_BODY_LENGTH)) { // TODO : do not use MAX_BODY_LENGTH
			// build the true command
			cout << "build command" << endl;
			ChatCommand* result = new BroadcastCommand;
			result->setHeader(command.getHeader());
			result->decodeHeader();
			result->setBody(command.getBody(), command.getBodyLength());
			return result;
		} else {
			cerr << "unable to read body" << endl;
			return NULL;
		}
	} else {
		cerr << "unable to read header" << endl;
		return NULL;
	}
	
}

