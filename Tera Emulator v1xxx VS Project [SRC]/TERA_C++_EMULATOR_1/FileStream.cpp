#include "FileStream.h"



FileStream::FileStream(FileStream &)
{
	_size = 0;
	_pos = 0;
	_raw = 0;
}

FileStream::FileStream(const char * fileStream)
{
	_file = std::ifstream(fileStream, std::ifstream::binary | std::ifstream::ate);
	if (!_file.is_open())
		return;

	_size = _file.tellg();
	_file.seekg(0, std::ifstream::beg);
	_raw = new byte[_size];
	_file.read((char*)_raw, _size);
	_file.seekg(0, std::ifstream::beg);
	_pos = 0;
}


FileStream::~FileStream()
{
	Close();

	if (_raw)
	{
		delete[] _raw;
		_raw = 0;
	}
	_size = 0;
	_pos = 0;
}

void FileStream::Resize(unsigned int size)
{
	if (_size + size > (unsigned int)FILE_STREAM_MAX_SIZE)
		return;


	if (!_raw)
	{
		_raw = new byte[size];
		_size = size;
		memset((void*)_raw, 0, _size);
	}
	else
	{
		unsigned int newSize = _size + size;
		byte * newRaw = (byte*)realloc((void*)_raw, newSize);

		memset((void*)&newRaw[_size], 0, size);
		_size = newSize;
		_raw = newRaw;
	}



}

void FileStream::Write(byte * data, unsigned int size)
{
	if (_size + size > (unsigned int)FILE_STREAM_MAX_SIZE)
		return;

	int allocSzie = size - _size + _pos;

	if (allocSzie > 0)
		Resize(allocSzie);

	if (memcpy_s((void*)&_raw[_pos], size, (const void*)data, size) != 0) return;


	if (allocSzie > 0)
	{
		_pos = _size;
	}
	else {
		_pos += size;
	}
}

void FileStream::Read(byte * out_buffer, unsigned int size)
{
	if (size > _size - _pos)
		return;
	memcpy_s((void*)out_buffer, size, (const void*)&_raw[_pos], size);
	_pos += size;
}

std::string FileStream::ReadASCIIString()
{
	if (_size - _pos < 1)
		return "-1";

	std::string out;
	int kk = 0;
	for (size_t i = _pos; i < _size; i++)
	{
		if (_raw[i] != 0x00)
		{
			out += (char)_raw[i];
			kk++;
		}
		else
			break;
	}
	_pos += kk;
	return out;
}

std::string FileStream::ReadUnicodeString()
{
	std::string out;
	for (size_t i = _pos; i < _size; i += 2)
	{
		if (_raw[i] == 0x00 && _raw[i + 1] == 0x00)
			break;
		out +=_raw[i];
	}
	_pos += (out.size() * 2) + 2;

	return out;
}

short FileStream::ReadInt16()
{
	if (_pos > _size - 2)
		return -1;

	short out = (_raw[_pos + 1] << 8) | _raw[_pos];
	_pos += 2;
	return out;
}

int FileStream::ReadInt32()
{
	if (_size - 4 < _pos)
		return 0xffffffff;

	int out = ((_raw[_pos + 3] << 24) | (_raw[_pos + 2] << 16) | (_raw[_pos + 1] << 8) | _raw[_pos]);
	_pos += 4;

	return out;
}

float FileStream::ReadFloat()
{
	if (_size < _pos + 4)
		return FLT_MAX;

	float out = *(float*)(&_raw[_pos]);
	_pos += 4;
	return out;
}

byte FileStream::ReadByte()
{
	short temp = (short)_pos;
	_pos++;
	return _raw[temp];
}

void FileStream::Clear()
{
	if (_raw)
	{
		delete[] _raw;
		_raw = 0;
	}
	_size = 0;
	_pos = 0;
}

void FileStream::ClearFile()
{
	if (IsOpen())
	{
		_file.clear();
	}
}

void FileStream::Close()
{
	_file.close();
}

bool FileStream::IsOpen()
{
	return _file.is_open();
}

void FileStream::SetEnd()
{
	_pos = _size;
}

void FileStream::SetFront()
{
	_pos = 0;
}

void FileStream::MoveForward(unsigned int val)
{
	if (_size < (val + _pos))
		return;

	_pos += val;
}

void FileStream::MoveBackwards(unsigned int val)
{
	if (_size - (_pos + val) < 0)
		return;

	_pos -= val;
}