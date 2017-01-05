#ifndef SERVERUTILS_H
#define SERVERUTILS_H

#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdio.h>

#include "Crypt\data_type.hpp"

class Stream;
class ServerUtils
{
public:

	static std::string HexString(byte* data, unsigned int size);
	static unsigned char HexCharToByteChar(const char *s);
	static byte* HexStringToByteArray(std::string str);
	static void UndoEscapedData(byte* data, unsigned size);
	static void UndoEscapedData(Stream* raw);
	static bool StringStartsWith(std::string a, std::string with, bool ignoreWhiteSpaces = false);
	static const int RemoveBeginingWhiteSpaces(std::string &line);
	static const int EscapeXMLLine(std::string& line);
	static void EscapeStream(Stream * s);
	static const wchar_t *GetWC(const char *c);
};
#endif
