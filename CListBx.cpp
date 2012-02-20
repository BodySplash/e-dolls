#include "clistbx.h"

// TODO : pouvoir attacher l'ip à un nom de la liste afin de pouvoir répondre aux messages éventuels


CListBx::CListBx(void)
{
}



bool CListBx::create(LPTSTR *fileName, UINT ident, POINT pos, HWND parent, int width, int height, const int nbImages) {
	position.x = pos.x;
	position.y = pos.y;
	hWindow = CreateWindow(TEXT("listbox"), NULL, WS_CHILD|WS_VISIBLE|LBS_STANDARD|LBS_HASSTRINGS|LBS_OWNERDRAWVARIABLE, pos.x, pos.y, width, height, parent, (HMENU) ident, hInst, NULL);
	image = new CBmpManager[nbImages];
	for (int i  = 0; i<nbImages; i++)
		image[i].load(fileName[i]);
	
	ID = ident;
	return true;
}

void CListBx::draw(HDC where, LPDRAWITEMSTRUCT lPdis) {
	if (lPdis->CtlID==ID){
		const UINT act = lPdis->itemAction;
		switch (act)
		{
		case ODA_SELECT:
		case ODA_DRAWENTIRE:
			{
				// déclarations d'un buffer de char et d'un objet TEXTMETRIC utilise pour le dessin
				TCHAR txt[20];
				TEXTMETRIC txtMet;
				// on récupére le numéro de l'image associé à la sélection actuelle
				BYTE who = (BYTE) SendMessage(lPdis->hwndItem, LB_GETITEMDATA, lPdis->itemID, (LPARAM) 0);
				// on l'affiche aux coordonnées indiquées dans le DRAWITEMSTRUCT
				BitBlt(lPdis->hDC, lPdis->rcItem.left, lPdis->rcItem.top,lPdis->rcItem.right - lPdis->rcItem.left,
					lPdis->rcItem.bottom - lPdis->rcItem.top, image[who].getHdc(), 0, 0, SRCCOPY);
				// on récupère ensuite le texte
				SendMessage(lPdis->hwndItem, LB_GETTEXT, 
					lPdis->itemID, (LPARAM) txt); 
				// on récupère le système metric de la fenetre
				GetTextMetrics(lPdis->hDC, &txtMet);
				// a partir de là on peut calculer le y pour le textOut
				int y = (lPdis->rcItem.bottom + lPdis->rcItem.top - 
					txtMet.tmHeight) / 2; 
				// si l'option est sélectionnées, on change la couleur de texte
				 if (lPdis->itemState & ODS_SELECTED) 
						SetTextColor(lPdis->hDC, RGB(255, 0, 0));
				// et on affiche le texte à l'y calculé et au x égale à la largeur de l'image + 2
					 TextOut(lPdis->hDC, 
					image[who].getWidth() + 2, 
					y, 
					txt, 
					strlen(txt));
					
			     // on réinitilase les couleurs

				 SetTextColor(lPdis->hDC, RGB(0, 0, 0));
                    break; 

			}
		}


	}
}

void CListBx::addItem(LPTSTR txt, BYTE type){
	int nItem;
	// on rajoutte dans un premier temps le texte
	nItem = SendMessage(hWindow, LB_ADDSTRING, 0,(LPARAM) txt);
	// gràca à l'id retourné, on attache maintenant le numéro de l'image associée
	SendMessage(hWindow, LB_SETITEMDATA, nItem, (LPARAM)type);
}
CListBx::~CListBx(void)
{
	delete[] image;
}
