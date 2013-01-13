class ChatMessage;
class SocketWrapper;

class ChatProtocol {
public:
	explicit ChatProtocol(SocketWrapper* socketWrapper);

	void sendBroadcastCommand(const char* message);
	ChatMessage* receiveCommand(SocketWrapper* socketWrapper);	

private:
	void sendCommand(ChatMessage* command);

	SocketWrapper* m_socketWrapper;
};