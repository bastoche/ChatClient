#include <winsock2.h>

#pragma once

// wrapper for the underlying winsock socket
// the socket is used in blocking mode
class SocketWrapper {
public:
	SocketWrapper();	
	bool init();
	bool connectToServer(const char* ipAddress);
	bool sendData(const char* data, int length);
	bool receiveData(char* data, int length);
	bool close();	

private:		
	bool shutdownConnection();
	bool closeConnection();	

	SOCKET m_socket;

	// TODO : make these method parameters
	static const char* ipAdress;
	static const int port;
	
};