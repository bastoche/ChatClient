class ChatCommand;
class ChatMessage;
class SocketWrapper;

// allow to serialize/deserialize commands in order to send/receive them through/from the socket wrapper
class ChatProtocol {
public:
	explicit ChatProtocol(SocketWrapper* socketWrapper);
	
	void sendCommand(const ChatCommand& command);
	ChatCommand* receiveCommand();	

	static ChatMessage* serialize(const ChatCommand& command);
	static ChatCommand* deserialize(const ChatMessage& message);

private:
	void sendMessage(ChatMessage* message);
	
	SocketWrapper* m_socketWrapper;
};