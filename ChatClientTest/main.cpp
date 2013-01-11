#include <iostream>
#include "gtest\gtest.h"
#include "BroadcastCommand.h"


TEST(BroadcastCommandTest, HeaderEncodingAndDecoding) {
	BroadcastCommand command;
	//command.setMessage("coucou");
	EXPECT_EQ(command.getBodyLength(), 0);
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}