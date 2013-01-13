#include "ChatProtocol.h"
#include <iostream>
#include "BroadcastCommand.h"
#include "ChatMessage.h"
#include "SocketWrapper.h"

using namespace std;

ChatProtocol::ChatProtocol(SocketWrapper* socketWrapper) : m_socketWrapper(socketWrapper) {}

void ChatProtocol::sendCommand(const ChatCommand& command) {	
	ChatMessage* message = serialize(command);
	sendMessage(message);	
	delete message;
}

ChatCommand* ChatProtocol::receiveCommand() {
	// read the header
	cout << "read header" << endl;
	ChatMessage message;
	if (m_socketWrapper->receiveData(message.header(), ChatMessage::HEADER_LENGTH)) {
		// read the body
		cout << "read body" << endl;
		message.decodeHeader();		
		if (m_socketWrapper->receiveData(message.body(), message.getBodyLength())) { 
			// deserialize the message into a command
			ChatCommand* command = deserialize(message);
			return command;
		} else {
			cerr << "unable to read body" << endl;
			return NULL;
		}
	} else {
		cerr << "unable to read header" << endl;
		return NULL;
	}	
}

void ChatProtocol::sendMessage(ChatMessage* message) {
	m_socketWrapper->sendData(message->getData(), message->getLength());
}

ChatMessage* ChatProtocol::serialize(const ChatCommand& command) {
	ChatMessage* message = new ChatMessage;
	// TODO check that the message body is big enough to hold the serialized data
	const size_t length = command.serialize(message->body());
	message->setBodyLength(length);
	message->encodeHeader();
	return message;
}

ChatCommand* ChatProtocol::deserialize(const ChatMessage& message){		
	string broadcastMessage(message.getBody(), message.getBodyLength());
	BroadcastCommand* command = new BroadcastCommand(broadcastMessage);
	return command;
}

