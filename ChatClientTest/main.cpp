#include <iostream>
#include "gtest\gtest.h"
#include "BroadcastCommand.h"
#include "ChatProtocol.h"
#include "ChatMessage.h"

using namespace std;

TEST(BroadcastCommandTest, BroadcastCommandSerialization) {
	// create a broadcast command from a message	
	const char* message = "coucou";	
	BroadcastCommand command(message);
	ChatMessage* chatMessage = ChatProtocol::serialize(command);

	// check that the body length is equal to the message length
	const size_t messageLength = strlen(message);
	EXPECT_EQ(messageLength, chatMessage->getBodyLength());

	// check that deserializing after serializing works as intended		
	BroadcastCommand* deserializedCommand = (BroadcastCommand*) ChatProtocol::deserialize(*chatMessage);
	EXPECT_STREQ(message, deserializedCommand->getMessage().c_str());

	delete chatMessage;
	delete deserializedCommand;
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}