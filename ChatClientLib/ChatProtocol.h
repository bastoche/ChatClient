class ChatCommand;
class SocketWrapper;

class ChatProtocol {
public:
	explicit ChatProtocol(SocketWrapper* socketWrapper);

	void sendBroadcastCommand(const char* message);
	ChatCommand* receiveCommand(SocketWrapper* socketWrapper);	

private:
	void sendCommand(ChatCommand* command);

	SocketWrapper* m_socketWrapper;
};