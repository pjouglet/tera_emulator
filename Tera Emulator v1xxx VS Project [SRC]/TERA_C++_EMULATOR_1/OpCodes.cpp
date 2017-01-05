#include "OpCodes.hpp"
#include "OpCodesEnum.h"
#include "SendPacket.h"

void OpCodes::Release()
{
	for (size_t i = 0; i < _opCodesList.size(); i++)
	{
		if (_opCodesList[i])
		{
			delete _opCodesList[i];
			_opCodesList[i] = 0;
		}
	}
	_opCodesList.clear();
}

const SendPacket const * OpCodes::Get(OpCode opCode)
{
	for (size_t i = 0; i < _opCodesList.size(); i++)
	{
		if (_opCodesList[i])
		{
			if (opCode == _opCodesList[i]->_toRecv)
			{
				return _opCodesList[i];
			}
		}
	}
	return nullptr;
}

bool OpCodes::Add(const SendPacket const  *sendPacket)
{
	if (!sendPacket)
		return false;
	_opCodesList.push_back(sendPacket);
	return true;
}

const unsigned int OpCodes::Count()
{
	return _opCodesList.size();
}

std::vector<const SendPacket const *> OpCodes::_opCodesList;
