#include <iostream>
#include "gtest\gtest.h"
#include "BroadcastCommand.h"

using namespace std;

TEST(BroadcastCommandTest, BroadcastCommandSerialization) {
	// create a broadcast command from a message
	BroadcastCommand command;
	const char* message = "coucou";	
	command.setMessage(message);

	// check that the body length is equal to the message length
	const size_t messageLength = strlen(message);
	EXPECT_EQ(messageLength, command.getBodyLength());

	// check that decoding the header gives the right body length
	BroadcastCommand otherCommand;
	otherCommand.setHeader(command.getHeader());
	otherCommand.decodeHeader();
	EXPECT_EQ(messageLength, otherCommand.getBodyLength());

	// check that extracting the message from the body works as intended
	otherCommand.setBody(command.getBody(), command.getBodyLength());
	EXPECT_STREQ(message, otherCommand.getMessage());

}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}