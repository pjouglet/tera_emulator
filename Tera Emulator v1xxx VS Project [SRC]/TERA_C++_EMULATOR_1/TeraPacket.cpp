#include "TeraPacket.hpp"
#include "Stream.h"
#include "OpCodesEnum.h"

TeraPacket::TeraPacket()
{


}

TeraPacket::~TeraPacket()
{


}

Stream* TeraPacket::GetPacket(SOCKET sock, Crypt::Session * session, OpCode &outOpCode)
{
	Stream* out = new Stream(4);
	
	int read = 0;
	int len = 0;

	read = recv(sock, (char*)out->_raw, 4, 0);
	if (read == SOCKET_ERROR || read == 0)
	{
		shutdown(sock, SD_BOTH);
		closesocket(sock);
		read = -1;

		delete out;
		return nullptr;
	}
	len = read;
	if (sock == INVALID_SOCKET)
	{
		delete out;
	}
	else
	{
		std::lock_guard<std::mutex> locker(_recvMutex);
		session->Decrypt(out->_raw, 4);

		short packetSize = ((out->_raw[1] << 8) | out->_raw[0]);
		outOpCode = (OpCode)((out->_raw[3] << 8) | out->_raw[2]);
		out->Resize(packetSize - 4);

		while (out->_size > len && sock != INVALID_SOCKET && read >= 0)
		{
			read = recv(sock, (char*)&out->_raw[len], out->_size - len, 0);

			if (read == SOCKET_ERROR)
			{
				shutdown(sock, SD_BOTH);
				closesocket(sock);
				delete out;
				return nullptr;
			}
			len += read;
		}
		if (sock == INVALID_SOCKET)
		{
			delete out;
			return nullptr;
		}

		if (out->_size > 4)
			session->Decrypt(&out->_raw[4], out->_size - 4);

		return out;
	}
	return nullptr;
}
