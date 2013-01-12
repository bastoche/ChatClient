#include "ChatCommandParser.h"
#include <iostream>
#include <regex>
#include "ChatClient.h"

using namespace std;
using namespace std::tr1;

ChatCommandParser::ChatCommandParser(ChatClient* chatClient) : m_chatClient(chatClient) {}

void ChatCommandParser::run() {

	const int inputBufferLength = 1024;
	char inputBuffer[inputBufferLength];

	const regex quitPattern("/quit");

	const regex listPattern("/list");

	cmatch whisperResult;
	const regex whisperPattern("/w (\\w*) (\\w*)");

	// if the entered text is longer than inputBufferLength, it will be splitted into several messages
	while(true) {		
		cin.getline(inputBuffer, inputBufferLength);
		if (regex_match(inputBuffer, quitPattern)) {			
			break;
		} else if (regex_match(inputBuffer, listPattern)) {
			m_chatClient->listUsers();
		} else if (regex_match(inputBuffer, whisperResult, whisperPattern)) {
			const string dest = whisperResult[1];
			const string message = whisperResult[2];
			m_chatClient->sendMsgToDest(message.c_str(), dest.c_str());
		} else {
			m_chatClient->sendMsgToAll(inputBuffer);
		}
	}
}

