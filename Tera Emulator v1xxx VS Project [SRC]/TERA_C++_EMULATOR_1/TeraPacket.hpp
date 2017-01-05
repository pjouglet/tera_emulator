#ifndef PACKET_H
#define PACKET_H

#include <mutex>
#include "Crypt\data_type.hpp"
#include "Crypt\TeraCrypt.hpp"
#include "ServerUtils.hpp"

#include "socket.hpp"

class Stream; enum OpCode;
class TeraPacket
{
public:
	TeraPacket();
	~TeraPacket();
	Stream* GetPacket(SOCKET sock, Crypt::Session * session , OpCode& outOpcode);
	std::mutex _recvMutex;
};

#endif