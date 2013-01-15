#include "ChatCommandParser.h"
#include <iostream>
#include <regex>
#include <string>
#include "ChatClient.h"

using namespace std;
using namespace std::tr1;

ChatCommandParser::ChatCommandParser(ChatClient* chatClient) : m_chatClient(chatClient) {}

static void displayPrompt() { cout << "> "; }

void ChatCommandParser::run() {
	string inputString;

	const regex quitPattern("/quit");

	const regex listPattern("/list");

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
		} else {
			m_chatClient->sendMsgToAll(inputString);
		}
	}
}

