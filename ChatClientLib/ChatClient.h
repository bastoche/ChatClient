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

	SocketWrapper* m_socketWrapper;
	ChatProtocol* m_chatProtocol;
	std::string m_login;
};