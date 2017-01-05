#include "RRequestInstoreProductList.h"


RRequestInstoreProductList::RRequestInstoreProductList() : SendPacket(C_REQUEST_INGAMESTORE_PRODUCT_LIST)
{
}

void RRequestInstoreProductList::Process(OpCode opCode, Stream * data, Client * caller)const
{
	
	data->WriteInt16(7);
	data->WriteInt16(S_INGAMESHOP_CATEGORY_BEGIN);
	data->WriteInt16(1);
	data->WriteByte(0);
	caller->Send(data);
	data->Clear();

	data->WriteInt16(7);
	data->WriteInt16(S_INGAMESHOP_CATEGORY_END);
	data->WriteInt16(1);
	data->WriteByte(0);
	caller->Send(data);
	data->Clear();

	data->WriteInt16(7);
	data->WriteInt16(S_INGAMESHOP_PRODUCT_BEGIN);
	data->WriteInt16(1);
	data->WriteByte(0);
	caller->Send(data);
	data->Clear();

	data->WriteInt16(7);
	data->WriteInt16(S_INGAMESHOP_PRODUCT_END);
	data->WriteInt16(1);
	data->WriteByte(0);
	caller->Send(data);
	data->Clear();
}
