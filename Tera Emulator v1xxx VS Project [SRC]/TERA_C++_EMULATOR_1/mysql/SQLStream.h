#pragma once

#include <string>
#include "../Crypt/data_type.hpp"
#define SQL_STREAM_MAX_SIZE 0xffffffff
class Stream;
class SQLStream
{
public:
	SQLStream();
	~SQLStream();

private:
	bool prepared;
	int erased;
public:

	void WriteString(const char* s);
	void Write(const char* data, unsigned int size);
	void WriteAndQuoteString(const char* s);
	void EscapeString();
	void UndoEscape();

	static const char* EscapeData(const char* data, unsigned int s);
	static const char* UndoEscapeData(const char* data, unsigned int s);

	void Clear();
	void operator [](char);
	void operator [](int);
	void operator [](short);
	void operator [](double);
	void operator [](float);
	void operator [](long long);

	void PrepareStatement(std::string line);

	void PutInt32(int index, int value);
	void PutInt64(int index, long long value);
	void PutString(int index, std::string s);//+ string
	void PutQuotedString(int index, std::string s);//+ ' + string + '
	void PutFloat(int index, float value);
	void PutBoolean(int index, bool value);
	void PutDouble(int index, double value);
	void PutNull(int index);
	void PutAndEscapeQuotedBlob(int index, byte* blob, unsigned int size);
	void PutAndEscapeQuotedBlob(int index, Stream* s);

	operator const char*();
	std::string _raw;
	unsigned int _size;

};

