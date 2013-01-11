#include <iostream>
#include <winsock2.h>
#include "ChatClient.h"

using namespace std;

int main()
{
	// initialize the winsock library
	WSADATA wsaData;
	const int startup_result = WSAStartup(MAKEWORD(2, 0), &wsaData);
	if ( 0 != startup_result ) {		
		cerr << "WSAStartup failure" << endl;
		system("PAUSE");
		exit(EXIT_FAILURE);
	} else {
		cout << "WSAStartup success" << endl;
	}

	// instantiate and run the chat client
	ChatClient chatClient;
	chatClient.run();

	// clean up the winsock library
	WSACleanup();

	// pause at the end so the console does not close
	system("PAUSE");

	return 0;
}

