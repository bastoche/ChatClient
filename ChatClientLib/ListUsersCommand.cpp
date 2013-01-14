#include "ListUsersCommand.h"
#include <iostream>
#include <string>

using namespace std;

ListUsersCommand::ListUsersCommand() {}

ListUsersCommand::~ListUsersCommand() {}

void ListUsersCommand::display() const {
	cout << "Trying to list users." << endl;
}

string ListUsersCommand::toString() const {
	return LIST_USERS;
}