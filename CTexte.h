#pragma once
#include "cgobject.h"

class CTexte :
	public CGObject
{
private:

public:
	CTexte(void);
	void draw(HDC where);
	bool create(LPTSTR *fileName, UINT ident, POINT pos, HWND parent, int width, int height, bool readOnly); 

	~CTexte(void);
};
