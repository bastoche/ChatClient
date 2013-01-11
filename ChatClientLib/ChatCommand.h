class ChatCommand {
public:
	ChatCommand();    

	void decodeHeader();

	size_t getBodyLength();

protected:
	~ChatCommand() {};
	char* body();
	void setBodyLength(size_t length);
	void encodeHeader();

	static const size_t headerLength = 4;
	//static const int commandLength = 4; TODO
	static const size_t maxBodyLength = 512 - headerLength /*- commandLength*/;


private:
	char m_data[headerLength + /*commandLength +*/ maxBodyLength];
	size_t m_bodyLength;

	
};