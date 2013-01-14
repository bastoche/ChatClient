#include <iostream>
#include <string>
#include "gtest\gtest.h"
#include "ChatProtocol.h"
#include "ChatMessage.h"
#include "BroadcastCommand.h"
#include "LoginCommand.h"
#include "LoginReplyCommand.h"

using namespace std;

TEST(BroadcastCommandTest, BroadcastCommandSerialization) {
	// create a broadcast command from a message	
	const string message = "coucou";	
	BroadcastCommand command(message, "bob");

	// serialize it
	ChatMessage* chatMessage = ChatProtocol::serialize(command);

	// check that deserializing after serializing works as intended		
	BroadcastCommand* deserializedCommand = dynamic_cast<BroadcastCommand*>(ChatProtocol::deserialize(*chatMessage));
	EXPECT_EQ(message, deserializedCommand->getMessage());

	delete chatMessage;
	delete deserializedCommand;
}

TEST(LoginCommandTest, LoginCommandSerialization) {
	// create a login command from a message	
	const string login = "Bob";	
	LoginCommand command(login);

	// serialize it
	ChatMessage* chatMessage = ChatProtocol::serialize(command);

	// check that deserializing after serializing works as intended		
	LoginCommand* deserializedCommand = dynamic_cast<LoginCommand*>(ChatProtocol::deserialize(*chatMessage));
	EXPECT_EQ(login, deserializedCommand->getLogin());

	delete chatMessage;
	delete deserializedCommand;
}

TEST(LoginReplyCommandTest, LoginReplyCommandSerialization) {
	// create a login reply command 
	const string success = "true";
	const string login = "Bob";		
	LoginReplyCommand command(success, login);

	// serialize it
	ChatMessage* chatMessage = ChatProtocol::serialize(command);

	// check that deserializing after serializing works as intended		
	LoginReplyCommand* deserializedCommand = dynamic_cast<LoginReplyCommand*>(ChatProtocol::deserialize(*chatMessage));
	EXPECT_TRUE(deserializedCommand->getSuccess());
	EXPECT_EQ(login, deserializedCommand->getLogin());

	delete chatMessage;
	delete deserializedCommand;
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}