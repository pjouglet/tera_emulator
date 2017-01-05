#include "RHardwareInfo.h"
#include "Client.hpp"
#include "Account.hpp"


RHardwareInfo::RHardwareInfo() : SendPacket(C_HARDWARE_INFO)
{

}

void RHardwareInfo::Process(OpCode opCode, Stream * data, Client * caller) const
{
	Account* a = caller->GetAccount();
	if (a)
	{
		data->_pos = 55;
		a->_hardwareInfo = data->ReadUTF16StringLittleEdianToASCII();
	}
}
