#include "ChatCommand.h"

class BroadcastCommand : public ChatCommand {
public:	
	virtual ~BroadcastCommand();
	void setMessage(const char* message);
	const char* getMessage();
};