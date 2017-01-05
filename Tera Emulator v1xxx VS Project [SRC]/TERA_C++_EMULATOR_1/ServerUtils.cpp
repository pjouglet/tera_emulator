#include "ServerUtils.hpp"
#include "Stream.h"
#include <fstream>

std::string ServerUtils::HexString(byte * data, unsigned int size)
{
	std::stringstream ss;
	ss << std::hex;
	for (int i = 0; i < size; ++i)
		ss << std::setw(2) << std::setfill('0') << (int)data[i];
	return ss.str();

}

inline unsigned char ServerUtils::HexCharToByteChar(const char * s)
{
	return
		(((s[0] >= 'A' && s[0] <= 'Z') ? (10 + s[0] - 'A') :
		(s[0] >= 'a' && s[0] <= 'z') ? (10 + s[0] - 'a') :
			(s[0] >= '0' && s[0] <= '9') ? (s[0] - '0') : 0) << 4) |
			((s[1] >= 'A' && s[1] <= 'Z') ? (10 + s[1] - 'A') :
		(s[1] >= 'a' && s[1] <= 'z') ? (10 + s[1] - 'a') :
				(s[1] >= '0' && s[1] <= '9') ? (s[1] - '0') : 0);
}

byte * ServerUtils::HexStringToByteArray(std::string str)
{
	if (str.length() % 2 != 0)
		return nullptr;

	byte * out_data = new byte[str.length() / 2];
	char* pos = &str[0];

	for (int count = 0; count < str.length() / 2; count++) {
		sscanf(pos, "%2hhx", &out_data[count]);
		pos += 2;
	}

	return out_data;
}

void ServerUtils::UndoEscapedData(byte * _raw, unsigned size)
{

	for (size_t i = 0; i < size; i++)
	{
		
		if (_raw[i] == '\\\\"')
		{
			_raw[i] = '\\';
		}
		else if (_raw[i] == '0')
		{
			_raw[i] = 0x00;
		}
		else if (_raw[i] == 0x5c)
		{
			_raw[i] = 0x27;
		}
		else if (_raw[i] == '\\0')
		{
			_raw[i] = 0x00;
		}
		else if (_raw[i] == '\\n')
		{
			_raw[i] = '\n';
		}
		else if (_raw[i] == '\\r')
		{
			_raw[i] = '\r';
		}
		else if (_raw[i] == '\\t')
		{
			_raw[i] = '\t';
		}
	}

	

	//for (size_t i = 0; i < size; i++)
	//{
	//	if (_raw[i] == '0' || _raw[i] == 0x30)
	//		_raw[i] = 0x00;
	//}


}

void ServerUtils::UndoEscapedData(Stream * s)
{

	std::ofstream sqlDump = std::ofstream("C://users//narcis//desktop//espaceUndoDump.txt");
	sqlDump.write((char*)s->_raw, s->_size);
	for (size_t i = 0; i < s->_size; i++)
	{

		if ((char)s->_raw[i] == '\\\"')
		{
			s->_raw[i] = 0x22;
		}
		else if ((char)s->_raw[i] == '0')
		{
			s->_raw[i] = 0x00;
		}
		else if ((char)s->_raw[i] == 0x5c)
		{
			s->_raw[i] = 0x27;
		}
		else if ((char)s->_raw[i] == '\\0')
		{
			s->_raw[i] = 0x00;
		}
		else if ((char)s->_raw[i] == '\\n')
		{
			s->_raw[i] = '\n';
		}
		else if ((char)s->_raw[i] == '\\r')
		{
			s->_raw[i] = '\r';
		}
		else if ((char)s->_raw[i] == '\\t')
		{
			s->_raw[i] = '\t';
		}
	}

	sqlDump.write("[]", 2);
	sqlDump.write((char*)s->_raw, s->_size);
	sqlDump.close();

}

bool ServerUtils::StringStartsWith(std::string a, std::string with, bool ignoreWhiteSpaces)
{
	if (a.size() < with.size())
		return false;
	if (with.size() == 0)
		return true;

	std::string result;
	if (ignoreWhiteSpaces)
	{
		for (size_t i = 0; i < a.size(); i++)
		{
			if (a[i] != ' ')
				result += a[i];
		}
	}
	else result = a;

	for (size_t i = 0; i < with.size(); i++)
	{
		if (result[i] != with[i])
		{
			return false;
		}
	}

	return true;
}

const int ServerUtils::RemoveBeginingWhiteSpaces(std::string & line)
{
	std::string temp = line;
	line.clear();
	int count = 0;
	for (size_t i = 0; i < temp.size(); i++)
	{

		if (temp[i] == 0x20 || temp[i] == ' ')
			count++;
		else break;
	}

	for (size_t i = 0; i < temp.size() - count; i++)
	{
		line += temp[count + i];
	}

	return count;
}

const int ServerUtils::EscapeXMLLine(std::string & line)
{
	int count = 0;
	std::string temp = line;
	line.clear();


	for (size_t i = 0; i < temp.size(); i++)
	{
		if (temp[i] != '\"')
		{
			line += temp[i];
		}
		else
			count++;
	}

	return count;
}

void ServerUtils::EscapeStream(Stream * s)
{

	std::ofstream sqlDump = std::ofstream("C://users//narcis//desktop//espaceDump.txt");
	sqlDump.write((char*)s->_raw, s->_size);
	for (size_t i = 0; i < s->_size; i++)
	{
		if ((char*)s->_raw[i] == '\0')
		{
			s->_raw[i] = '\\0';
		}
		else if (((char)s->_raw[i]) == '\'')
		{
			s->_raw[i] = (byte)'\\\'';
		}
		else if (((char)s->_raw[i]) == '\"')
		{
			s->_raw[i] = (byte)'\\\"';
		}
		else if (((char)s->_raw[i]) == '\n')
		{
			s->_raw[i] = (byte)'\\n';
		}
		else if (((char)s->_raw[i]) == '\t')
		{
			s->_raw[i] = (byte)'\\t';
		}
		else if (((char)s->_raw[i]) == '\r')
		{
			s->_raw[i] = (byte)'\\r';
		}
		else if (((char)s->_raw[i]) == '\a')
		{
			s->_raw[i] = (byte)'\\a';
		}
		else if (((char)s->_raw[i]) == '\\')
		{
			s->_raw[i] = (byte)'\\\\';
		}

	}
	sqlDump.write("[]", 2);
	sqlDump.write((char*)s->_raw, s->_size);
	sqlDump.close();
}

const wchar_t *ServerUtils::GetWC(const char *c)
{
	const size_t cSize = strlen(c) + 1;
	wchar_t* wc = new wchar_t[cSize];
	mbstowcs(wc, c, cSize);

	return wc;
}

