#include <string>

#pragma once

class SocketWrapper;
class ChatProtocol;

class ChatClient {
public:
	ChatClient();	
	~ChatClient();	

	void run();

	void sendMsgToDest(const std::string& message, const std::string& dest);
	void sendMsgToAll(const std::string& message);
	void listUsers();

	static const std::string loginRegex;
private:	
	bool connect();
	bool login();
	void startListening();
	void listen();
	void stopListening();
	static unsigned __stdcall listeningThreadEntryPoint(void* pThis);
	volatile bool m_listenFlag;

	// arbitrary limit on login size
	static const size_t MAX_LOGIN_LENGTH = 20;

	SocketWrapper* m_socketWrapper;
	ChatProtocol* m_chatProtocol;
	std::string m_login;
};