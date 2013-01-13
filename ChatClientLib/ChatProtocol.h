#pragma once

class ChatCommand;
class ChatMessage;
class SocketWrapper;

// allow to serialize/deserialize commands in order to send/receive them through/from the socket wrapper
class ChatProtocol {
public:
	explicit ChatProtocol(SocketWrapper* socketWrapper);
	
	void sendCommand(const ChatCommand& command);
	ChatCommand* receiveCommand();	

	// serialize a ChatCommand into a ChatMessage
	static ChatMessage* serialize(const ChatCommand& command);

	// deserialize a ChatMessage into a ChatCommand, return NULL if the message cannot be deserialized
	static ChatCommand* deserialize(const ChatMessage& message);

private:
	void sendMessage(ChatMessage* message);
	
	SocketWrapper* m_socketWrapper;
};