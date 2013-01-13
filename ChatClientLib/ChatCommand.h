class ChatCommand {
public:	
	ChatCommand();    
	virtual ~ChatCommand();

	static const size_t HEADER_LENGTH = 4;		
	
	const char* getHeader();
	const char* getBody();
	const char* getData();
	size_t getBodyLength();
	size_t getLength();

	// allow to set the header and deduce the body length from it
	void setHeader(const char* data);
	char* header();
	void decodeHeader();

	// allow to set the body
	void setBody(const char* data, size_t length);
	char* body();

	virtual void display();
	
protected:		
	static const size_t LENGTH = 512;
	static const size_t MAX_BODY_LENGTH = LENGTH - HEADER_LENGTH;

	void setBodyLength(size_t length);

	// create the header data from the body length
	void encodeHeader();


private:	
	
	char m_data[LENGTH];
	size_t m_bodyLength;

	

};