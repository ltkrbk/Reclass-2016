#pragma once

#include "CNodeBase.h"

class CNodeHex32 : public CNodeBase
{
public:
	CNodeHex32();

	virtual void Update(CHotSpot& Spot);

	virtual int GetMemorySize() { return 4; }

	virtual int Draw(ViewInfo& View, int x, int y);
};