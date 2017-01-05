#ifndef SOCKET_H
#define SOCKET_H

#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _WINSOCKAPI_

#include <Windows.h>
#include <WinSock2.h>


#pragma comment(lib, "ws2_32.lib")

#include "Crypt\data_type.hpp"

#endif