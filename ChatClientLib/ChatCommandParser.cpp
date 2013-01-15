#include "ChatCommandParser.h"
#include <iostream>
#include <regex>
#include <string>
#include "ChatClient.h"

using namespace std;
using namespace std::tr1;

ChatCommandParser::ChatCommandParser(ChatClient* chatClient) : m_chatClient(chatClient) {}

static void displayHelp() {
	cout << "How to speak : write some text then press enter." << endl;
	cout << "How to see who is online : /list" << endl;
	cout << "How to whisper to someone : /w name message" << endl;
	cout << "How to leave : /quit" << endl;
}

void ChatCommandParser::run() {

	cout << "Type '/help' to display the available commands." << endl;
	
	string inputString;
		
	const regex helpPattern("/help");
	const regex listPattern("/list");
	const regex quitPattern("/quit");

	smatch whisperResult;
	const regex whisperPattern("/w (" + ChatClient::loginRegex + ") (.*)");
	
	while(getline(cin, inputString)) {						
		if (regex_match(inputString, quitPattern)) {			
			break;
		} else if (regex_match(inputString, listPattern)) {
			m_chatClient->listUsers();
		} else if (regex_match(inputString, whisperResult, whisperPattern)) {
			const string dest = whisperResult[1];
			const string message = whisperResult[2];
			m_chatClient->sendMsgToDest(message.c_str(), dest.c_str());
		} else if (regex_match(inputString, helpPattern)) {
			displayHelp();
		} else {
			m_chatClient->sendMsgToAll(inputString);
		}
	}
}

