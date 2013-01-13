#include <iostream>
#include "gtest\gtest.h"
#include "BroadcastCommand.h"
#include "ChatProtocol.h"
#include "ChatMessage.h"
#include "LoginCommand.h"

using namespace std;

TEST(BroadcastCommandTest, BroadcastCommandSerialization) {
	// create a broadcast command from a message	
	const char* message = "coucou";	
	BroadcastCommand command(message);

	// serialize it
	ChatMessage* chatMessage = ChatProtocol::serialize(command);

	// check that deserializing after serializing works as intended		
	BroadcastCommand* deserializedCommand = dynamic_cast<BroadcastCommand*>(ChatProtocol::deserialize(*chatMessage));
	EXPECT_STREQ(message, deserializedCommand->getMessage().c_str());

	delete chatMessage;
	delete deserializedCommand;
}

TEST(LoginCommandTest, LoginCommandSerialization) {
	// create a login command from a message	
	const char* login = "Bob";	
	LoginCommand command(login);

	// serialize it
	ChatMessage* chatMessage = ChatProtocol::serialize(command);

	// check that deserializing after serializing works as intended		
	LoginCommand* deserializedCommand = dynamic_cast<LoginCommand*>(ChatProtocol::deserialize(*chatMessage));
	EXPECT_STREQ(login, deserializedCommand->getLogin().c_str());

	delete chatMessage;
	delete deserializedCommand;
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}