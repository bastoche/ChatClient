class ChatCommand {
public:	
	ChatCommand();    
	virtual ~ChatCommand();

	static const size_t HEADER_LENGTH = 4;
	static const size_t LENGTH = 512;
	
	const char* getHeader();
	const char* getBody();
	const char* getData();
	size_t getBodyLength();

	// allows to set the header and deduce the body length from it
	void setHeader(const char* data);
	void decodeHeader();

	// allows to set the body
	void setBody(const char* data, size_t length);
	
protected:		
	void setBodyLength(size_t length);

	// create the header data from the body length
	void encodeHeader();

	//static const int commandLength = 4; TODO
	static const size_t MAX_BODY_LENGTH = LENGTH - HEADER_LENGTH /*- commandLength*/;


private:
	char m_data[HEADER_LENGTH + /*commandLength +*/ MAX_BODY_LENGTH];
	size_t m_bodyLength;

	char* body();

	

	
};