#ifndef _DATA_TYPE_HPP_
#define _DATA_TYPE_HPP_

#include <cstdint>

#ifndef ulong
#define ulong	unsigned long long
#endif

#ifndef uint
#define uint	unsigned int
#endif

#ifndef ushort
#define ushort	unsigned short
#endif

#ifndef uchar
#define uchar	unsigned char
#endif

#ifndef byte
#define byte	unsigned char
#endif

#ifndef Wchar
#define Wchar	unsigned short
#endif

#ifdef WIN32
	#define socklen_t int
#else
	#define SOCKET int
	#define SOCKET_ERROR -1
	#define INVALID_SOCKET -1
	#define SOCKADDR const struct sockaddr
#endif

#endif // _DATA_TYPE_HPP_