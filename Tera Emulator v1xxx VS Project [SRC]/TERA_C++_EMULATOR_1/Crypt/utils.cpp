#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdarg>
#include <ctime>
#include <sstream>

#include <ctype.h>
#include <sys/stat.h>
#include <chrono>
#include <sys\timeb.h>
#include <sys\utime.h>
#include <sys/types.h>



#ifdef WIN32
#include <windows.h>
#endif

#include "data_type.hpp"
#include "utils.hpp"


#ifndef NO_ERROR_FILE
FILE * FError = NULL;
#else
#define FError stderr
#endif


uint l_sizeof(char *src)
{
	if (!src) return 0;
	uint i;
	memcpy(&i, src - sizeof(uint), sizeof(uint));
	return i;
}

char *l_malloc(uint size)
{
	char *out = (char*)malloc(size + sizeof(uint));
	memcpy(out, &size, sizeof(uint));
	return out + sizeof(uint);
}

void l_free(char *src)
{
	free(src - sizeof(uint));
}

char *l_realloc(char *src, uint size)
{
	char *out = (char*)realloc(src ? src - sizeof(uint) : NULL, size + sizeof(uint));
	if (!out) {
		out = l_malloc(size);
		memcpy(out, src, l_sizeof(src));
		l_free(src);
	}
	else out += sizeof(uint);
	memcpy(out - sizeof(uint), &size, sizeof(uint));
	return out;
}

char *l_mem2mem(char *src)
{
	if (!src) return NULL;
	char *out = (char*)malloc(l_sizeof(src));
	if (out)
		memcpy(out, src, l_sizeof(src));
	return out;
}

char *bytedump(const char *value)
{
	size_t size = sizeof(value) / sizeof(*value);
	char *dst = (char*)malloc(size);
	memcpy(dst, value, size);
	return dst;
}

char *strdump(const char *value)
{
	char *dst = (char*)malloc(strlen(value) + 1);
	strcpy_s(dst, strlen(value), value);
	return dst;
}

char *strndump(const char *value, int len)
{
	char *dst = (char*)malloc(len + 1);
	memset(dst, 0, len + 1);
	strncpy_s(dst, len, value, len);
	return dst;
}

void strupdate(char **src, const char *value)
{
	if (*src) free(*src);
	*src = strdump(value);
}

int utf8_to_unicode_length(const unsigned char *c)
{
	int i = 0;
	while (c[0]) {
		/*if ((*c & 0x80) == 0)
			NULL;
		else */if ((*c & 0xe0) == 0xc0)
			c += 1;
		else if ((*c & 0xf0) == 0xe0)
			c += 2;
		else if ((*c & 0xf8) == 0xf0)
			c += 3;

	c++;
	i++;
	}
	return i;
}

Wchar utf8_to_unicode(const unsigned char *c, int *pos)
{
	if ((*c & 0x80) == 0)
		return c[0];
	else if ((*c & 0xe0) == 0xc0) {
		*pos += 1;
		return (((c[0] & 0x1f) << 6) | (c[1] & 0x3f));
	}
	else if ((*c & 0xf0) == 0xe0) {
		*pos += 2;
		return (((c[0] & 0x0f) << 12) | ((c[1] & 0x3f) << 6) | (c[2] & 0x3f));
	}
	else if ((*c & 0xf8) == 0xf0) {
		*pos += 3;
		return (((c[0] & 0x07) << 18) | ((c[1] & 0x3f) << 12) | ((c[2] & 0x3f) << 6) | (c[3] & 0x3f));
	}
	else
		return 0xffff;
}

int unicode_to_utf8_length(const Wchar *c)
{
	int i = 0;
	while (c[0]) {
		if (c[0] < (1 << 7))// 7 bit Unicode encoded as plain ascii
		{
			i += 1;
			c += sizeof(Wchar) * 1;
		}
		else if (c[0] < (1 << 11))// 11 bit Unicode encoded in 2 UTF-8 bytes
		{
			i += 2;
			c += sizeof(Wchar) * 2;
		}
		else if (c[0] < (1 << 16))// 16 bit Unicode encoded in 3 UTF-8 bytes
		{
			i += 3;
			c += sizeof(Wchar) * 3;
		}
		else if (c[0] < (1 << 21))// 21 bit Unicode encoded in 4 UTF-8 bytes
		{
			i += 4;
			c += sizeof(Wchar) * 4;
		}
	}
	return i;
}

int unicode_to_utf8(char* b, Wchar c)
{
	int i = 0;
	if (c < (1 << 7))// 7 bit Unicode encoded as plain ascii
	{
		*b++ = c;
		i++;
	}
	else if (c < (1 << 11))// 11 bit Unicode encoded in 2 UTF-8 bytes
	{
		*b++ = (c >> 6) | 0xC0;
		i++;
		*b++ = (c & 0x3F) | 0x80;
		i++;
	}
	else if (c < (1 << 16))// 16 bit Unicode encoded in 3 UTF-8 bytes
	{
		*b++ = (c >> 12) | 0xE0;
		i++;
		*b++ = ((c >> 6) & 0x3F) | 0x80;
		i++;
		*b++ = (c & 0x3F) | 0x80;
		i++;
	}

	else if (c < (1 << 21))// 21 bit Unicode encoded in 4 UTF-8 bytes
	{
		*b++ = (c >> 18) | 0xF0;
		i++;
		*b++ = ((c >> 12) & 0x3F) | 0x80;
		i++;
		*b++ = ((c >> 6) & 0x3F) | 0x80;
		i++;
		*b++ = (c & 0x3F) | 0x80;
		i++;
	}
	*b++ = 0;
	return i;
}

int WCHARlen(const Wchar *wc)
{
	int i = 0;
	while (wc[i]) i++;
	return i;
}

int cpy_WCHAR(Wchar *wc, const char *c, int len)
{
	Wchar b;
	int size = 0;
	wc[size] = 0;
	for (int i = 0; c[i] && size < len - 1; i++) {
		b = utf8_to_unicode((unsigned char *)c + i, &i);
		wc[size] = b;
		size++;
		wc[size] = 0;
	}
	return size;
}

int cpy_WCHAR2(Wchar *wc, const char *c)
{
	Wchar b;
	int size = 0;
	wc[size] = 0;
	for (int i = 0; c[i]; i++) {
		b = utf8_to_unicode((unsigned char *)c + i, &i);
		wc[size] = b;
		size++;
		wc[size] = 0;
	}
	return size;
}

Wchar *to_WCHARi(const char *c, int *size)
{
	Wchar b;
	Wchar *wc = (Wchar*)malloc(sizeof(Wchar)*(utf8_to_unicode_length((const unsigned char *)c) + 1));
	*size = 0;
	for (int i = 0; c[i]; i++) {
		b = utf8_to_unicode((const unsigned char *)&c[i], &i);
		wc[*size] = b;
		(*size)++;
		wc[*size] = 0;
	}
	return wc;
}

Wchar *to_WCHAR(const char *c)
{
	int size;
	return to_WCHARi(c, &size);
}

char *to_CHAR(const Wchar *wc)
{
	char *c = (char*)malloc(unicode_to_utf8_length(wc) + 1);
	int size = 0;
	c[size] = 0;
	for (int i = 0; wc[i]; i++) {
		int isize = unicode_to_utf8(c + size, wc[i]);
		size += isize;
	}
	return c;
}

int to_CHARi(const Wchar *wc, char *c)
{
	int size = 0;
	c[size] = 0;
	for (int i = 0; wc[i]; i++) {
		int isize = unicode_to_utf8(c + size, wc[i]);
		size += isize;
	}
	return size;
}

char dir_exist(const char *dirname)
{
	struct stat   buffer;
	if (stat(dirname, &buffer) != 0)
		return 0;
#ifdef WIN32
	else if (buffer.st_mode & S_IFDIR)  // S_ISDIR() doesn't exist on my windows 
#else
	else if (S_ISDIR(buffer.st_mode))
#endif
		return 1;
	return 0;
}

char file_exist(const char *filename)
{
	struct stat   buffer;
	return (stat(filename, &buffer) == 0);
}

size_t file_size(const char *filename)
{
	struct stat   buffer;
	stat(filename, &buffer);
	return buffer.st_size;
}

void l_mkdir(const char* dirname) //Creating a directory using system() function [needs administrator rights]
{
#ifdef WIN32
	std::stringstream sstreamT;
	sstreamT << "md ";
	sstreamT << dirname;
	system(sstreamT.str().c_str());
#else
	mkdir(dirname, 0777);
#endif

}

float atof2(char* val)
{
	char *tmp = strchr(val, '.');
	if (tmp) tmp[0] = ',';
	return atof(val);
}

bool atob(char* val)
{
	if (strlen(val) > 0) {
		if (tolower(val[0]) == 't')
			return true;
		if (tolower(val[0]) == 'y')
			return true;
		if (val[0] == '1')
			return true;
	}
	return false;
}

short is_atoi(char* val)
{
	while (val[0]) {
		if (val[0] != '-'
			&& val[0] != '0'
			&& val[0] != '1'
			&& val[0] != '2'
			&& val[0] != '3'
			&& val[0] != '4'
			&& val[0] != '5'
			&& val[0] != '6'
			&& val[0] != '7'
			&& val[0] != '8'
			&& val[0] != '9'
			) return 0;
		val++;
	}
	return 1;
}

long microsec()
{
	//todo
	return 0;
}

char* l_realpath(const char * src)
{
	char * buffer;
#ifdef WIN32
	buffer = (char*)malloc(4092);
	GetFullPathNameA(src, 4092, buffer, NULL);
	buffer = (char*)realloc(buffer, strlen(buffer) + 1);
#else
	buffer = realpath(src, NULL);
#endif
	return buffer;
}

void hexdump(const char* function, const char* title, const void *Vbuffer, unsigned long index)
{
	const unsigned char *buffer = (const unsigned char*)Vbuffer;
	DEBUG("%s (%i) :: %s :: %s (%ld)\n", __FILE__, __LINE__, function, title, index);
	for (unsigned long i = 0; i < index; i += 16) {
		DEBUG2("[%10ld]\t", i);
		for (int spacer = 0; spacer < 16; spacer++) {
			if (i + spacer >= index)
				DEBUG2("   ");
			else
				DEBUG2("%02X ", buffer[i + spacer]);
			if ((spacer + 1) / 4 == (float)(spacer + 1) / 4)
				DEBUG2(" ");
		}
		DEBUG2("\t: ");
		for (int spacer = 0; spacer < 16; spacer++) {
			if (i + spacer >= index)
				DEBUG2("   ");
			else {
				if (buffer[i + spacer] < 32) DEBUG2(".");
				else DEBUG2("%c", buffer[i + spacer]);
			}
		}
		DEBUG2("\n");
	}
	DEBUG2("\n");
}

void DEBUG(const char *__msg, ...)
{
	if (!FError) return;
	if (!__msg) {
		fprintf(FError, "\n");
		return;
	}
	if (FError != stderr) {
		time_t rawtime;
		struct tm * t_info = new struct tm;
		time(&rawtime);
		localtime_s(t_info, &rawtime);
		fprintf(FError, "[%04i-%02i-%02i %02i:%02i:%02i] ", t_info->tm_year + 1900, t_info->tm_mon + 1, t_info->tm_mday, t_info->tm_hour, t_info->tm_min, t_info->tm_sec);
	}
	va_list __local_argv;
	va_start(__local_argv, __msg);
	vfprintf(FError, __msg, __local_argv);
	va_end(__local_argv);
	fflush(FError);
}

void DEBUG2(const char *__msg, ...)
{
	if (!FError) return;
	va_list __local_argv;
	va_start(__local_argv, __msg);
	vfprintf(FError, __msg, __local_argv);
	va_end(__local_argv);
	fflush(FError);
}
