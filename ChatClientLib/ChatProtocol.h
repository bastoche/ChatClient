class ChatCommand;
class SocketWrapper;

class ChatProtocol {
public:
	static ChatCommand* buildBroadcastCommand(const char* message);

	static ChatCommand* unmarshallCommand(SocketWrapper* socketWrapper);	
};