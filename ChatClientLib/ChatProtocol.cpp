#include "ChatProtocol.h"
#include "BroadcastCommand.h"
#include "SocketWrapper.h"

ChatCommand* ChatProtocol::buildBroadcastCommand(const char* message) {
	BroadcastCommand* command = new BroadcastCommand();
	command->setMessage(message);
	return command;
}

ChatCommand* ChatProtocol::unmarshallCommand(SocketWrapper* socketWrapper) {
	// read the header

	// read the body

	//	recompose the command
	return new ChatCommand();
}

