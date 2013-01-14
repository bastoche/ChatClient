#include <winsock2.h>
#include "ChatClient.h"
#include "Log.h"

using namespace std;

int main()
{
	int mainResult = 0;

	// initialize the winsock library
	WSADATA wsaData;
	const int startup_result = WSAStartup(MAKEWORD(2, 0), &wsaData);
	if ( 0 != startup_result ) {		
		error("Unable to initialize winsock library.");
		mainResult = 1;
	} else {
		log("WSAStartup success");


		// instantiate and run the chat client
		ChatClient chatClient;
		chatClient.run();

		// clean up the winsock library
		WSACleanup();

	}

	// pause at the end so the console does not close
	system("PAUSE");

	return mainResult;
}

