#pragma once
#include "cgobject.h"

class CListBx :
	public CGObject
{
public:
	CListBx(void);
	bool create(LPTSTR *fileName, UINT ident, POINT pos, HWND parent, int width, int height, const int nbImages);
	void draw(HDC where, LPDRAWITEMSTRUCT lPdis); // le drawstruct en paramètre nous permet de savoir comment dessiner notre liste
	void addItem(LPTSTR txt, BYTE type); // rajouter un élément à la liste
	~CListBx(void);
	
};
