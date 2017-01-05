#include "SQLStream.h"
#include <stdio.h>
#include <string.h>
#include <string>
#include <mysql_connection.h>
#include <cppconn\connection.h>
#include <cppconn\datatype.h>
#include "../Stream.h"
#include "../ServerUtils.hpp"

SQLStream::SQLStream()
{
	prepared = false;
}


SQLStream::~SQLStream()
{
}

void SQLStream::WriteString(const char * s)
{
	_raw += s;
	_size = _raw.size();
}

void SQLStream::Write(const char * data, unsigned int size)
{
	_raw.insert(_raw.size(), data, size);
	_size = _raw.size();
}

void SQLStream::WriteAndQuoteString(const char * s)
{
	WriteString("'");
	WriteString((char*)s);
	WriteString("'");
}
void SQLStream::EscapeString()
{
	for (size_t i = 0; i < _size; i++)
	{
		if (_raw[i] == 0)
			_raw[i] = '\\0';
	}

	_raw[_size] = 0;
}

void SQLStream::UndoEscape()
{
	for (size_t i = 0; i < _size; i++)
	{
		if (_raw[i] == '0')
			memset(&_raw[i], 0, 1);
	}
}

const char* SQLStream::EscapeData(const char * _data, unsigned int s)
{
	char* _raw = new char[s];
	memcpy_s((void*)_raw, s, (const void*)_data, s);

	for (size_t i = 0; i < s; i++)
	{
		if (_raw[i] == 0x00)
			_raw[i] = '\\0';
		else if (_raw[i] == '\n')
			_raw[i] = '\\n';
		else if (_raw[i] == '\r')
			_raw[i] = '\\r';
		else if (_raw[i] == '\'')
			_raw[i] = '\\\'';
		else if (_raw[i] == '\"')
			_raw[i] = '\\"';
	}

	/*for (size_t i = 0; i < s; i++)
	{
		if (_raw[i] == '\0')
		{
			_raw[i] = '\\0';
		}
		else if (_raw[i] == '\t')
		{
			_raw[i] = '\\t';
		}
		else if (_raw[i] == '\v')
		{
			_raw[i] = '\\v';
		}
		else if (_raw[i] == '\b')
		{
			_raw[i] = '\\b';
		}
		else if (_raw[i] == '\r')
		{
			_raw[i] = '\\r';
		}
		else if (_raw[i] == '\f')
		{
			_raw[i] = '\\f';
		}
		else if (_raw[i] == '\a')
		{
			_raw[i] = '\\a';
		}
		else if (_raw[i] == '\\')
		{
			_raw[i] = '\\\\';
		}
		else if (_raw[i] == '\"')
		{
			_raw[i] = '\\\"';
		}
		else if (_raw[i] == '\'')
		{
			_raw[i] = '\\\'';
		}
	}*/
	
	return _raw;
}

const char* SQLStream::UndoEscapeData(const char * _data, unsigned int s)
{
	char* data = new char[s];
	memcpy_s((void*)data, s, (const void*)_data, s);
	for (size_t i = 0; i < s; i++)
	{
		if (data[i] == '0')
			memset(&data[i], 0, 1);
	}
	return data;
}



void SQLStream::Clear()
{
	_raw.clear();
	_size = 0;
	prepared = false;
}

void SQLStream::operator[](char c)
{
	WriteString(&c);
}

void SQLStream::operator[](int i)
{
	WriteString((char*)std::to_string(i).c_str());
}

void SQLStream::operator[](short s)
{
	WriteString((char*)std::to_string(s).c_str());
}

void SQLStream::operator[](double d)
{
	WriteString((char*)std::to_string(d).c_str());
}

void SQLStream::operator[](float f)
{
	WriteString((char*)std::to_string(f).c_str());
}

void SQLStream::operator[](long long l)
{
	WriteString((char*)std::to_string(l).c_str());
}

void SQLStream::PrepareStatement(std::string line)
{
	Clear();
	prepared = true;
	_raw = line;
	erased = 0;
}

void SQLStream::PutInt32(int index, int value)
{
	if (!prepared)
		return;
	int count = 0;
	for (size_t i = 0; i < _raw.size(); i++)
	{
		if (_raw[i] == '?')
		{
			count++;
		}
		if (count == 1)
		{
			_raw.erase(_raw.begin() + i);//remove ?
			erased++;
			std::string toInsert = std::to_string(value);
			for (size_t j = 0; j < toInsert.size(); j++)
			{
				_raw.insert(_raw.begin() + i + j, toInsert[j]); //insert value
			}
			break;
		}
	}

}

void SQLStream::PutInt64(int index, long long value)
{
	if (!prepared)
		return;
	int count = 0;
	for (size_t i = 0; i < _raw.size(); i++)
	{
		if (_raw[i] == '?')
		{
			count++;
		}
		if (count == 1)
		{
			_raw.erase(_raw.begin() + i);//remove ?
			erased++;
			std::string toInsert = std::to_string(value);
			for (size_t j = 0; j < toInsert.size(); j++)
			{
				_raw.insert(_raw.begin() + i + j, toInsert[j]); //insert value
			}
			break;
		}
	}
}

void SQLStream::PutString(int index, std::string s)
{

	if (!prepared)
		return;
	int count = 0;
	for (size_t i = 0; i < _raw.size(); i++)
	{
		if (_raw[i] == '?')
		{
			count++;
		}
		if (count == 1)
		{
			_raw.erase(_raw.begin() + i);//remove ? 
			erased++;

			for (size_t j = 0; j < s.size(); j++)
			{
				_raw.insert(_raw.begin() + i + j, s[j]); //insert value
			}
			break;
		}
	}
}

void SQLStream::PutQuotedString(int index, std::string s)
{
	if (!prepared)
		return;
	int count = 0;
	for (size_t i = 0; i < _raw.size(); i++)
	{
		if (_raw[i] == '?')
		{
			count++;
		}
		if (count == 1)
		{
			_raw.erase(_raw.begin() + i);//remove ?
			erased++;
			std::string toInsert = ""; toInsert += '\''; toInsert += s; toInsert += '\'';
			for (size_t j = 0; j < toInsert.size(); j++)
			{
				_raw.insert(_raw.begin() + i + j, toInsert[j]); //insert value
			}
			break;
		}
	}
}

void SQLStream::PutFloat(int index, float value)
{
	if (!prepared)
		return;
	int count = 0;
	for (size_t i = 0; i < _raw.size(); i++)
	{
		if (_raw[i] == '?')
		{
			count++;
		}
		if (count == 1)
		{
			_raw.erase(_raw.begin() + i);//remove ?
			erased++;
			std::string toInsert = std::to_string(value);
			for (size_t j = 0; j < toInsert.size(); j++)
			{
				_raw.insert(_raw.begin() + i + j, toInsert[j]); //insert value
			}
			break;
		}
	}
}

void SQLStream::PutBoolean(int index, bool value)
{
	if (!prepared)
		return;
	int count = 0;
	for (size_t i = 0; i < _raw.size(); i++)
	{
		if (_raw[i] == '?')
		{
			count++;
		}
		if (count == 1)
		{
			_raw.erase(_raw.begin() + i);//remove ?
			erased++;
			std::string toInsert = value == true ? "TRUE" : "FALSE";
			for (size_t j = 0; j < toInsert.size(); j++)
			{
				_raw.insert(_raw.begin() + i + j, toInsert[j]); //insert value
			}
			break;
		}
	}
}

void SQLStream::PutDouble(int index, double value)
{
	if (!prepared)
		return;
	int count = 0;
	for (size_t i = 0; i < _raw.size(); i++)
	{
		if (_raw[i] == '?')
		{
			count++;
		}
		if (count == 1)
		{
			_raw.erase(_raw.begin() + i);//remove ?
			erased++;
			std::string toInsert = std::to_string(value);
			for (size_t j = 0; j < toInsert.size(); j++)
			{
				_raw.insert(_raw.begin() + i + j, toInsert[j]); //insert value
			}
			break;
		}
	}
}

void SQLStream::PutNull(int index)
{
	PutString(index, "NULL");
}

void SQLStream::PutAndEscapeQuotedBlob(int index, byte * blob, unsigned int size)
{
	if (!prepared)
		return;

	int count = 0;
	for (size_t i = 0; i < _raw.size(); i++)
	{
		if (_raw[i] == '?')
		{
			count++;
		}
		if (count == 1)
		{
			_raw.erase(_raw.begin() + i);//remove ?
			erased++;
			std::string toInsert = std::string(EscapeData((const char*)blob, size), size);
			toInsert.insert(toInsert.begin(), '\'');
			toInsert.insert(toInsert.end(), '\'');
			for (size_t j = 0; j < toInsert.size(); j++)
			{
				_raw.insert(_raw.begin() + i + j, toInsert[j]); //insert value
			}
			break;
		}
	}
}

void SQLStream::PutAndEscapeQuotedBlob(int index, Stream * s)
{
	if (!prepared)
		return;

	int count = 0;
	for (size_t i = 0; i < _raw.size(); i++)
	{
		if (_raw[i] == '?')
		{
			count++;
		}
		if (count == 1)
		{
			_raw.erase(_raw.begin() + i);//remove ?
			erased++;

			ServerUtils::EscapeStream(s);
			std::string toInsert = std::string((char*)s->_raw, s->_size);
			toInsert.insert(toInsert.begin(), '\'');
			toInsert.insert(toInsert.end(), '\'');
			for (size_t j = 0; j < toInsert.size(); j++)
			{
				_raw.insert(_raw.begin() + i + j, toInsert[j]); //insert value
			}
			break;
		}
	}
}

SQLStream::operator const char*()
{
	return _raw.c_str();
}

