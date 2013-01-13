class ChatClient;

// allow to parse the user input according to predefined regexes, delegate handling to the chat client
class ChatCommandParser {
public:
	ChatCommandParser(ChatClient* chatClient);
	void run();
private:
	ChatClient* m_chatClient;
};