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
#include "Log.h"

using namespace std;

ChatClient::ChatClient() : 
m_socketWrapper(new SocketWrapper), 
	m_chatProtocol(new ChatProtocol(m_socketWrapper)), 
	m_listenFlag(false),
	m_login("") {}

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
				error("Unable to log in.");
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

		// ask the user for his login
		cout << "Please login: ";
		getline(cin, inputLogin);

		if (false == inputLogin.empty()) {

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
							m_login = replyCommand->getLogin();
							tryAgain = false;
						} else {
							// login already used, only case when we try again
							tryAgain = true;
						}
						replyCommand->display();
					} else {
						error("unable to cast response as reply command");
					}
				} else {
					error("unable to receive command after login");
					tryAgain = false;
				}
				delete command;	

			} else {
				error("Error sending login command.");
				tryAgain = false;
			}
		} else {
			cout << "Your login must contain at least one character." << endl;
			tryAgain = true;
		}
	}

	return success;

}

void ChatClient::sendMsgToDest(const std::string& message, const std::string& dest) {
	// TODO
	cout << "send message " << message << " to dest " << dest << endl;
}

void ChatClient::sendMsgToAll(const std::string& message) {	
	BroadcastCommand command(message, m_login);
	m_chatProtocol->sendCommand(command);
}

void ChatClient::listUsers() {
	// TODO
	cout << "list users" << endl;
}

// start a new thread listening to messages from the server
void ChatClient::startListening() {
	log("start listening");
	m_listenFlag = true;
	// TODO : use the new std thread api 
	_beginthreadex(NULL, 0, listeningThreadEntryPoint, this, 0, NULL);		
}

// turn off the listen flag to stop the listening thread
void ChatClient::stopListening() {
	log("stop listening");
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
				error("Error while receiving command.");
			}
		}
		delete command;
	}

	log("end of listening thread");
}

// necessary boilerplate to be able to use _beginthreadex
unsigned __stdcall ChatClient::listeningThreadEntryPoint(void* pThis) {
	ChatClient* chatClient = (ChatClient*) pThis;
	chatClient->listen();
	return 1;
}
