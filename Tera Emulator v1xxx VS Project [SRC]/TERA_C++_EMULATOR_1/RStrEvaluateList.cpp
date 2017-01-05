#include "RStrEvaluateList.h"
#include "PlayerService.h"


RStrEvaluateList::RStrEvaluateList() : SendPacket(C_STR_EVALUATE_LIST)
{
}

void RStrEvaluateList::Process(OpCode opCode, Stream * stream, Client * caller) const
{
	stream->_pos = 22;
	std::string newName = stream->ReadUTF16StringBigEdianToASCII();
	bool nameGood = PlayerService::CheckPlayerNameForm(newName);

	stream->Clear();
	stream->WriteInt16(0);
	stream->WriteInt16(S_STR_EVALUATE_LIST);
	if (nameGood)
	{
		stream->WriteInt16(1);//unk
		stream->WriteInt16(8);//unk
		stream->WriteInt16(8);//unk
		stream->WriteInt16(0);//unk
		stream->WriteInt16(22);	 //unk
		stream->WriteInt16(1);
		stream->WriteInt16(0);
		stream->WriteInt16(0);
		stream->WriteInt16(0);
		stream->WriteString(newName);

		//WriteHexString(stream, "010008000800 0000 1600 0100 0000 0000 0000 4E00610072006A0061007A007A002E0054000000");

	}
	else
	{
		//not tested
		stream->WriteInt16(0);//unk
		stream->WriteInt16(8);//unk
		stream->WriteInt16(8);//unk
		stream->WriteInt16(0);//unk
		stream->WriteInt16(22);	 //unk
		stream->WriteInt16(0);
		stream->WriteInt16(0);
		stream->WriteInt16(0);
		stream->WriteInt16(0);
		stream->WriteString(newName);
	}
	stream->WritePos(0);

	caller->Send(stream);
}