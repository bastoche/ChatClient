class ChatClient;

class ChatCommandParser {
public:
	ChatCommandParser(ChatClient* chatClient);
	void run();
private:
	ChatClient* m_chatClient;
};