#pragma once

#include "config.h"
#include "CGObject.h"

//	Classe bouton qui comme
//	son nom l'indique
//	gère les boutons 



class CBouton :
	public CGObject
{
public:
	CBouton(void);
	CBouton(LPTSTR *fileName, UINT ident, POINT pos, HWND parent); // constructeur par paramètres
	bool create(LPTSTR *fileName, UINT ident, POINT pos, HWND parent); // fonction de création 
	inline void setState(BYTE st) { state = st;} // fonction pour changer l'état de notre bouton
	~CBouton(void);
	void draw(HDC where, LPDRAWITEMSTRUCT lPdis); // fonction de dessin prenant en paramètre le dc ou le dessiner et une drawstruct obtenue par le windowProx
};
