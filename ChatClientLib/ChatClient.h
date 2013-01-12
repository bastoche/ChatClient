class SocketWrapper;
class ChatProtocol;

class ChatClient {
public:
	ChatClient();	
	virtual ~ChatClient();	

	void run();

	void sendMsgToDest(const char* message, const char* dest);
	void sendMsgToAll(const char* message);
	void listUsers();
private:	
	bool connect();
	void login(const char* name);
	void startListening();
	void listen();
	void stopListening();
	static unsigned __stdcall listeningThreadEntryPoint(void* pThis);
	volatile bool m_listenFlag;

	SocketWrapper* m_socketWrapper;
	ChatProtocol* m_chatProtocol;
};