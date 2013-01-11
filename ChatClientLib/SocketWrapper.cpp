#include "SocketWrapper.h"
#include <iostream>

using namespace std;

SocketWrapper::SocketWrapper() : m_socket(INVALID_SOCKET) {}

// instantiate the wrapped socket
bool SocketWrapper::init() {
	m_socket = socket(AF_INET, SOCK_STREAM, 0); 

	if (INVALID_SOCKET == m_socket) {
		cerr << "error creating socket" << endl;		
		return false;
	} else {
		cout << "socket created" << endl;		
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
		cerr << "unable to connect to server" << endl;				
		return false;
	} else {
		cout << "connection established" << endl;		
		return true;
	}
}


bool SocketWrapper::sendData(const char* data, int length) {
	const int sendResult = send(m_socket, data, length, 0);
	if ( SOCKET_ERROR == sendResult ) {
		cerr << "error sending message" << endl;		
		return false;
	} else {
		cout << "message sent" << endl;		
	}
	return true;
}

bool SocketWrapper::receiveData(char* data, int length) {
	int readBytes = 0;
	while (readBytes < length) {
		const int recvResult = recv(m_socket, data + readBytes, length - readBytes, 0);
		if (recvResult > 0) {
			cout << "received something" << endl;					
			readBytes += recvResult;
		} else if (0 == recvResult) {
			cout << "received nothing (maybe because we asked for a shutdown)" << endl;
			return false;
		} else {
			cerr << "recv failed" << endl;
			return false;
		}
	}
	cout << "receiving successful" << endl;
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
		cerr << "shutdown error" << endl;
		return false;
	} else {
		cout << "shutdown sent" << endl;	
		return true;
	}	

	// wait for confirmation from peer
	// in fact this may be intercepted by the listening thread, and we don't really care about this anyway
	/*const int readBufferLength = 1024; 
	char readBuffer[readBufferLength];		
	while (true) {
		const int recvResult = recv(m_socket, readBuffer, readBufferLength, 0);
		if (SOCKET_ERROR == recvResult) {
			cerr << "error reading after shutdown" << endl;					
			return false;
		} else if (recvResult != 0) {
			cout << "received something after shutdown, discarding" << endl;						
		} else {
			cout << "shutdown confirmed" << endl;		
			return true;
		}
	}*/


}

// close the socket
bool SocketWrapper::closeConnection(){
	const int closeResult = closesocket(m_socket);
	if (SOCKET_ERROR == closeResult) {
		cerr << "error closing socket" << endl;			
		return false;
	} else {		
		cout << "socket closed" << endl;						
		return true;
	}

}