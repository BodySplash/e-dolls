#include "cbouton.h"
#include "config.h"



CBouton::CBouton(void)
{
	ID = 0;
	state = 0;
	hWindow = NULL;
	image = NULL;

}
CBouton::CBouton(LPTSTR *fileName, UINT ident, POINT pos, HWND parent) {
	create(fileName, ident, pos, parent);
	
}

bool CBouton::create(LPTSTR* fileName, UINT ident, POINT pos, HWND parent) {

	state = 0;
	ID = ident;
	image = new CBmpManager[2];
	image[0].load(fileName[0]);
	image[1].load(fileName[1]);
	position.x = pos.x;
	position.y = pos.y;
	hWindow = CreateWindow( TEXT("button"), TEXT(""), WS_CHILD |WS_VISIBLE|BS_OWNERDRAW, pos.x, pos.y, image[0].getWidth(), image[0].getHeight(), parent,(HMENU) ident, hInst, NULL);
	main = parent;
	return true;
}


void CBouton::draw(HDC where, LPDRAWITEMSTRUCT lPdis) {
	BLENDFUNCTION bf;
	bf.BlendOp = AC_SRC_OVER;
    bf.BlendFlags = 0;
    bf.SourceConstantAlpha = 255; // opacité à 100%
    bf.AlphaFormat = AC_SRC_ALPHA; // utilisation de l'alpha channel 
	// vérifions la drawstruct pour savoir comment dessiner notre bouton
	if (lPdis->CtlID == ID)
		if (lPdis->itemState & ODS_SELECTED)
			state = 1;
			
		else
			state = 0;
	AlphaBlend(where, position.x, position.y, 
			image[state].getWidth(), image[state].getHeight(), 
			image[state].getHdc(), 0, 0, image[state].getWidth(), image[state].getHeight(), bf);
		
		
		
	
}
	
	



CBouton::~CBouton(void)
{
	if (image!=NULL)
		delete[] image;

}
