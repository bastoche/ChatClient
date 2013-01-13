#pragma once

// class wrapping the serialized data that will be sent over the network
class ChatMessage {
public:	
	ChatMessage();    
	virtual ~ChatMessage();

	static const size_t HEADER_LENGTH = 4;		
		
	const char* getHeader() const;
	const char* getBody() const;
	const char* getData() const;
	size_t getBodyLength() const;
	size_t getLength() const;

	// allow to set the header and deduce the body length from it (when deserializing)	
	char* header();
	void decodeHeader();

	// allow to set the body and create the header data (when serializing)	
	char* body();	
	void setBodyLength(size_t length);
	void encodeHeader();
	

private:
	static const size_t LENGTH = 512;
	static const size_t MAX_BODY_LENGTH = LENGTH - HEADER_LENGTH;
	char m_data[LENGTH];
	size_t m_bodyLength;

};