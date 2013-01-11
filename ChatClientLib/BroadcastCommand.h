#include "ChatCommand.h"

class BroadcastCommand : public ChatCommand {
public:	
	void setMessage(const char* message);
	const char* getMessage();
	void display();
};