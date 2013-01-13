#include "ChatClient.h"
#include <iostream>
#include <process.h>
#include "SocketWrapper.h"
#include "ChatCommandParser.h"
#include "ChatProtocol.h"
#include "ChatMessage.h"
#include "BroadcastCommand.h"
#include "LoginCommand.h"
#include "LoginReplyCommand.h"

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
			if (login()) {

				// start the listening thread that displays messages from the server
				startListening();

				// instantiate and run the command parser
				ChatCommandParser chatCommandParser(this);
				chatCommandParser.run();

				// clean up
				stopListening();	

			} else {
				cerr << "Unable to log in." << endl;
			}

			m_socketWrapper->close();
		}
	}
}

bool ChatClient::connect() {
	return m_socketWrapper->connectToServer();
}

bool ChatClient::login() {	
	string inputLogin;
	bool success = false;
	bool tryAgain = true;	

	while (tryAgain) {
		// default case : do not try again
		tryAgain = false;

		// ask the user for his login
		cout << "Login as: ";
		getline(cin, inputLogin);
		LoginCommand command(inputLogin);
		command.display();

		// send the login command to the server
		if (m_chatProtocol->sendCommand(command)) {		

			// try to deserialize the next command as a login reply
			ChatCommand* command = m_chatProtocol->receiveCommand();
			if (command) {
				LoginReplyCommand* replyCommand = dynamic_cast<LoginReplyCommand*>(command);
				if (replyCommand) {					
					if (replyCommand->getSuccess()) {		
						// success case
						success = true;					
					} else {
						// login already used, only case when we try again
						tryAgain = true;
					}
					replyCommand->display();
				} 
			} 
			delete command;	

		} else {
			cerr << "error sending login command" << endl;		
		}	
	}

	return success;

}

void ChatClient::sendMsgToDest(const std::string& message, const std::string& dest) {
	// TODO
	cout << "send message " << message << " to dest " << dest << endl;
}

void ChatClient::sendMsgToAll(const std::string& message) {	
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
				cerr << "error receiving command" << endl;
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
