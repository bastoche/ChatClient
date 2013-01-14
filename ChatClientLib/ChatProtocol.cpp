#include "ChatProtocol.h"
#include <iostream>
#include "ChatCommand.h"
#include "ChatMessage.h"
#include "SocketWrapper.h"
#include "Log.h"

using namespace std;

ChatProtocol::ChatProtocol(SocketWrapper* socketWrapper) : m_socketWrapper(socketWrapper) {}

bool ChatProtocol::sendCommand(const ChatCommand& command) {	
	ChatMessage* message = serialize(command);
	const bool result = sendMessage(message);	
	delete message;
	return result;
}

ChatCommand* ChatProtocol::receiveCommand() {
	// read the header
	log("read header");
	ChatMessage message;
	if (m_socketWrapper->receiveData(message.header(), ChatMessage::HEADER_LENGTH)) {
		// read the body
		log("read body");
		message.decodeHeader();		
		if (m_socketWrapper->receiveData(message.body(), message.getBodyLength())) { 
			// deserialize the message into a command
			return deserialize(message);			
		} else {
			error("Unable to read command body.");
			return NULL;
		}
	} else {
		error("Unable to read command header.");
		return NULL;
	}	
}

bool ChatProtocol::sendMessage(ChatMessage* message) {
	return m_socketWrapper->sendData(message->getData(), message->getLength());
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
	return ChatCommand::deserialize(message.getBody(), message.getBodyLength());
}

