#ifndef OPCODES_H
#define OPCODES_H

#include <vector>

class SendPacket; enum OpCode;
class OpCodes
{
public:
	static void Release();

	static const  SendPacket const * Get(OpCode);

	static bool Add(const SendPacket const *sendPacket);
	static const unsigned int Count();
private:
	static std::vector<const SendPacket const*> _opCodesList;

};

#endif