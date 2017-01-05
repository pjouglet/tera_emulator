#include "RRequestContract.h"



RRequestContract::RRequestContract() : SendPacket(C_REQUEST_CONTRACT)
{
}

void RRequestContract::Process(OpCode opCode, Stream * data, Client * caller) const
{
	short nameOffset = data->ReadInt16();
	int unk1 = data->ReadInt32();
	int contract = data->ReadInt32();
	int unk2 = data->ReadInt32();
	int unk3 = data->ReadInt32();
	int unk4 = data->ReadInt32();
	data->_pos = nameOffset;
	std::string contractorName = data->ReadUTF16StringBigEdianToASCII();

	data->Clear();
	data->WriteInt16(8);
	data->WriteInt16(S_REPLY_REQUEST_CONTRACT);
	data->WriteInt32(contract);
	caller->Send(data);

	data->Clear();
	data->WriteInt16(4);
	data->WriteInt16(S_BIND_ITEM_BEGIN);
	caller->Send(data);
}
