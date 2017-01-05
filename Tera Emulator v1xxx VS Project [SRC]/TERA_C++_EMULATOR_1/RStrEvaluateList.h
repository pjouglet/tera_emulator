#ifndef RS_EVALUATE_LIST_H
#define RS_EVALUATE_LIST_H

#include "SendPacket.h"
class RStrEvaluateList :
	public SendPacket
{
public:
	RStrEvaluateList();
	

	// Inherited via SendPacket
	virtual void Process(OpCode opCode, Stream * data, Client * caller)const override;

};

#endif