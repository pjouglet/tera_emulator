#pragma once

#include "Crypt\data_type.hpp"
#include "Crypt\utils.hpp"
#include "ServerUtils.hpp"

#include <fstream>
#include <vector>
#include <string>

#ifndef FILE_STREAM_MAX_SIZE
#define FILE_STREAM_MAX_SIZE 0xffffffff //max size of tera packet
#endif


class FileStream
{
public:
	FileStream(FileStream&);
	FileStream(const char * fileStream);
	~FileStream();

private:
	void Resize(unsigned int size);
public:
	void Write(byte* data, unsigned int size);
	void Read(byte* out_buffer, unsigned int size);
	short ReadInt16();
	int  ReadInt32();
	float ReadFloat();
	byte ReadByte();
	std::string ReadASCIIString();
	std::string ReadUnicodeString();
	void Clear();
	void ClearFile();
	void Close();
	bool IsOpen();
	void SetEnd();
	void SetFront();
	void MoveForward(unsigned int val);
	void MoveBackwards(unsigned int val);

	std::ifstream _file;
	byte* _raw;
	unsigned int _size;
	unsigned int _pos;
};

