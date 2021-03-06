#include "stdafx.h"
#include "CNodeWCharPtr.h"

CNodeWCharPtr::CNodeWCharPtr()
{
	m_nodeType = nt_pwchar;
	m_strName = "PWChar";
}

void CNodeWCharPtr::Update(CHotSpot & Spot)
{
	StandardUpdate(Spot);
	__int64 v = _ttoi64(Spot.Text.GetString());
	if (Spot.ID == 0)
		ReClassWriteMemory((LPVOID)Spot.Address, &v, sizeof(size_t));
}

int CNodeWCharPtr::Draw(ViewInfo & View, int x, int y)
{
	if (m_bHidden)
		return DrawHidden(View, x, y);

	size_t* pMemory = (size_t*)&View.pData[m_Offset];

	AddSelection(View, 0, y, g_FontHeight);
	AddDelete(View, x, y);
	AddTypeDrop(View, x, y);
	//AddAdd(View, x, y);

	int tx = x + TXOFFSET;
	tx = AddIcon(View, tx, y, ICON_INTEGER, HS_NONE, HS_NONE);
	tx = AddAddressOffset(View, tx, y);
	tx = AddText(View, tx, y, crType, HS_NONE, _T("PWCHAR "));
	tx = AddText(View, tx, y, crName, HS_NAME, m_strName);

	//tx = AddText(View,tx,y,crName,HS_NONE," = ");
	//tx = AddText(View,tx,y,crValue,0,"%lli",pMemory[0]) + FontWidth;
	//tx = AddComment(View,tx,y);

	/*
	int tx = x + 16;
	tx = AddIcon(View,tx,y,ICON_TEXT,HS_NONE,HS_NONE);
	tx = AddAddressOffset(View,tx,y);
	tx = AddText(View,tx,y,crType,HS_NONE,"Text ");
	tx = AddText(View,tx,y,crName,69,"%s",m_strName);
	tx = AddText(View,tx,y,crIndex,HS_NONE,"[");
	tx = AddText(View,tx,y,crIndex,0,"%i",memsize);
	tx = AddText(View,tx,y,crIndex,HS_NONE,"]");
	*/

	tx = AddText(View, tx, y, crChar, HS_NONE, _T(" = '"));
	if (VALID(pMemory))
	{
		CStringW sc = ReadMemoryStringW((size_t)pMemory[0], 128);
		tx = AddText(View, tx, y, crChar, 1, "%ls", sc.GetBuffer());
	}

	tx = AddText(View, tx, y, crChar, HS_NONE, _T("' ")) + g_FontWidth;
	tx = AddComment(View, tx, y);

	return y += g_FontHeight;
}
