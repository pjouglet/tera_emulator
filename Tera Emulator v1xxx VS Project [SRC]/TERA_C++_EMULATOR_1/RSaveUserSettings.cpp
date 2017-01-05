#include "RSaveUserSettings.h"

RSaveUserSettings::RSaveUserSettings() : SendPacket(C_SAVE_CLIENT_USER_SETTING)
{
}

void RSaveUserSettings::Process(OpCode opCode, Stream * stream, Client * owner)const
{
	Player* p = nullptr;
	if (!(p = owner->GetSelectedPlayer()))
		return;

	p->_settingSize = stream->_size;
	if (p->_playerSettings)
	{
		delete p->_playerSettings; p->_playerSettings = 0;
		p->_playerSettings = 0;
	}

	p->_playerSettings = new byte[stream->_size];
	stream->Read(p->_playerSettings, stream->_size);
}