#include "ChatClient.h"
#include <iostream>
#include <process.h>
#include "SocketWrapper.h"
#include "ChatCommandParser.h"
#include "ChatProtocol.h"
#include "ChatMessage.h"
#include "BroadcastCommand.h"

using namespace std;

ChatClient::ChatClient() : m_socketWrapper(new SocketWrapper), m_chatProtocol(new ChatProtocol(m_socketWrapper)), m_listenFlag(false) {}

ChatClient::~ChatClient() { 
	delete m_chatProtocol;
	delete m_socketWrapper;
}

// main loop of the program
void ChatClient::run() {	
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
	BroadcastCommand command(message);
	m_chatProtocol->sendCommand(command);
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

	while (m_listenFlag) {		
		ChatCommand* command = m_chatProtocol->receiveCommand();
		// if m_listenFlag is false, we might receive the shutdown message from the server
		if (m_listenFlag) { 
			if (command) {
				command->display();
			} else {
				cerr << "error unmarshalling command" << endl;
			}
		}
		delete command;
	}

	cout << "end of listening thread" << endl;
}

// necessary boilerplate to be able to use _beginthreadex
unsigned __stdcall ChatClient::listeningThreadEntryPoint(void* pThis) {
	ChatClient* chatClient = (ChatClient*) pThis;
	chatClient->listen();
	return 1;
}
