#include "ChatMessage.h"

class BroadcastCommand : public ChatMessage {
public:	
	void setMessage(const char* message);
	const char* getMessage();
	void display();
};