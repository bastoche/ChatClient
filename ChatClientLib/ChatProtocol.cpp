#include "ChatProtocol.h"
#include <iostream>
#include "BroadcastCommand.h"
#include "SocketWrapper.h"

using namespace std;

ChatProtocol::ChatProtocol(SocketWrapper* socketWrapper) : m_socketWrapper(socketWrapper) {}

void ChatProtocol::sendBroadcastCommand(const char* message) {
	BroadcastCommand command;
	command.setMessage(message);
	sendCommand(&command);	
}

ChatMessage* ChatProtocol::receiveCommand(SocketWrapper* socketWrapper) {
	// read the header
	cout << "read header" << endl;
	ChatMessage command;
	if (socketWrapper->receiveData(command.header(), ChatMessage::HEADER_LENGTH)) {
		// read the body
		cout << "read body" << endl;
		command.decodeHeader();		
		if (socketWrapper->receiveData(command.body(), command.getBodyLength())) { 
			// build the true command
			cout << "build command" << endl;
			ChatMessage* result = new BroadcastCommand;
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

void ChatProtocol::sendCommand(ChatMessage* command) {
	m_socketWrapper->sendData(command->getData(), command->getLength());
}

