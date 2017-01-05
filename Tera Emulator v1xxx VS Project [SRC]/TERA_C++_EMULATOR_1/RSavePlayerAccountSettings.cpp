#include "RSavePlayerAccountSettings.h"

RSavePlayerAccountSettings::RSavePlayerAccountSettings() : SendPacket(C_SAVE_CLIENT_ACCOUNT_SETTING)
{
}

void RSavePlayerAccountSettings::Process(OpCode opCode, Stream * stream, Client * caller)const
{
	Account * a = nullptr;
	if (!(a = caller->GetAccount()))
		return;

	if (a->_accountSettings)
	{
		delete a->_accountSettings; a->_accountSettings = 0;
		a->_accountSettings = 0;
	}
	a->_accountSettingsSize = (unsigned short)stream->_size;
	a->_accountSettings = new byte[stream->_size];
	stream->Read(a->_accountSettings, stream->_size);
}