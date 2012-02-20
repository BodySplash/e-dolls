#pragma once
#include "config.h"
#include "CBmpManager.h"

class CGObject
{
protected :

	BYTE state; // flag indiquant comment dessiner l'objet
	CBmpManager *image; // objet à dessiner
	UINT ID; // id utilisé dans le windowProc
	HWND hWindow; // Handler vers la fenetre
	HWND main;
	POINT position; // position dans la fenetre principale
	

public:
	
	 //virtual void draw(HDC where) = 0; // fonction de dessin
	 //virtual bool create(LPTSTR *fileName, UINT ident, POINT pos, HWND parent) = 0; // fonction d'init
	
};
