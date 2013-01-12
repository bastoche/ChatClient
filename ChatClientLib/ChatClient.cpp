#include "ChatClient.h"
#include <iostream>
#include <process.h>
#include "SocketWrapper.h"
#include "ChatCommandParser.h"
#include "ChatProtocol.h"
#include "ChatCommand.h"

using namespace std;

ChatClient::ChatClient() : m_socketWrapper(NULL), m_listenFlag(false) {}

// main loop of the program
void ChatClient::run() {

	// instantiate and initialize the socket wrapper
	m_socketWrapper = new SocketWrapper;

	if (m_socketWrapper->init()) {
		if (connect()) {
			// TODO 
			// login(...);

			// start the listening thread that displays messages from the server
			startListening();

			// instantiate and run the command parser
			ChatCommandParser chatCommandParser(this);
			chatCommandParser.run();

			// clean up
			stopListening();	

			m_socketWrapper->close();
		}
	}

	delete m_socketWrapper;
}

bool ChatClient::connect() {
	return m_socketWrapper->connectToServer();
}

void ChatClient::login(const char* name) {
	/* TODO */
}

void ChatClient::sendMsgToDest(const char* message, const char* dest) {
	// TODO
	cout << "send message " << message << " to dest " << dest << endl;
}

void ChatClient::sendMsgToAll(const char* message) {	
	ChatCommand* command = ChatProtocol::buildBroadcastCommand(message);
	// TODO : use getLength instead of LENGTH, needs work server side
	m_socketWrapper->sendData(command->getData(), ChatCommand::LENGTH);
	delete command;
}

void ChatClient::listUsers() {
	// TODO
	cout << "list users" << endl;
}

// start a new thread listening to messages from the server
void ChatClient::startListening() {
	cout << "start listening" << endl;
	m_listenFlag = true;
	// TODO : use the new std thread api 
	_beginthreadex(NULL, 0, listeningThreadEntryPoint, this, 0, NULL);		
}

// turn off the listen flag to stop the listening thread
void ChatClient::stopListening() {
	cout << "stop listening" << endl;
	m_listenFlag = false;	
}

// listening thread main loop
void ChatClient::listen() {

	// TODO : decode data using chat protocol

	while (m_listenFlag) {		
		ChatCommand* command = ChatProtocol::unmarshallCommand(m_socketWrapper);
		// if m_listenFlag is false, we might receive the shutdown message from the server
		if (m_listenFlag) { 
			if (command) {
				command->display();
			} else {
				cerr << "error unmarshalling command" << endl;
			}
		}
	}

	cout << "end of listening thread" << endl;
}

// necessary boilerplate to be able to use _beginthreadex
unsigned __stdcall ChatClient::listeningThreadEntryPoint(void* pThis) {
	ChatClient* chatClient = (ChatClient*) pThis;
	chatClient->listen();
	return 1;
}
