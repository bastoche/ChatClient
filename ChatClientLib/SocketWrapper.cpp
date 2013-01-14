#include "SocketWrapper.h"
#include <iostream>
#include "Log.h"

using namespace std;

SocketWrapper::SocketWrapper() : m_socket(INVALID_SOCKET) {}

// instantiate the wrapped socket
bool SocketWrapper::init() {
	m_socket = socket(AF_INET, SOCK_STREAM, 0); 

	if (INVALID_SOCKET == m_socket) {
		error("Error creating socket.");
		return false;
	} else {
		log("socket created");
		return true;
	}
}

// TODO : make these method parameters
const char* SocketWrapper::ipAdress = "127.0.0.1";
const int SocketWrapper::port = 5555;

// connect the socket to the server using the above defined configuration
bool SocketWrapper::connectToServer() {

	// initialize a socketAdress structure
	SOCKADDR_IN socketAdress = { 0 }; 
	socketAdress.sin_addr.s_addr = inet_addr(ipAdress);
	socketAdress.sin_port = htons(port);
	socketAdress.sin_family = AF_INET;

	// connect the socket to the server
	const int connectResult = connect(m_socket, (SOCKADDR *) &socketAdress, sizeof(socketAdress));
	if ( SOCKET_ERROR == connectResult ) {
		error("Unable to connect to server.");
		return false;
	} else {
		log("connection established");
		return true;
	}
}


bool SocketWrapper::sendData(const char* data, int length) {
	const int sendResult = send(m_socket, data, length, 0);
	if ( SOCKET_ERROR == sendResult ) {
		error("Error while sending data through the socket.");
		return false;
	} else {
		log("send success");
		return true;
	}	
}

bool SocketWrapper::receiveData(char* data, int length) {
	int readBytes = 0;
	while (readBytes < length) {
		const int recvResult = recv(m_socket, data + readBytes, length - readBytes, 0);
		if (recvResult > 0) {
			log("received something");					
			readBytes += recvResult;
		} else if (0 == recvResult) {
			log("received nothing (maybe because we asked for a shutdown)");
			return false;
		} else {
			error("Error while receiving data from the socket.");
			return false;
		}
	}
	log("receive success");
	return true;
}

bool SocketWrapper::close(){
	const bool shutdownResult = shutdownConnection();
	const bool closeResult = closeConnection();
	return (shutdownResult && closeResult);
}

// shutdown the connection gracefully
bool SocketWrapper::shutdownConnection(){
	const int shutdownResult = shutdown(m_socket, SD_SEND);
	if (SOCKET_ERROR == shutdownResult) {
		error("Error while trying to shutdown socket.");
		return false;
	} else {
		log("shutdown sent");
		return true;
	}	
}

// close the socket
bool SocketWrapper::closeConnection(){
	const int closeResult = closesocket(m_socket);
	if (SOCKET_ERROR == closeResult) {
		error("Error while closing socket");
		return false;
	} else {		
		log("socket closed");
		return true;
	}

}