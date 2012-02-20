#pragma once

#include "config.h"
#include "CBouton.h"
#include "CBmpManager.h"
#include "CTexte.h"
#include "CListBx.h"


//TODO:
// ecrire une classe pour chaque type de controle qu'il puisse se dessiner eux-memes
// prevoir de stocker leur �tat
// mettre a jour du coup la classe Gui du dessus pour virer tous cex pointeurs et tableaux
// qui me donnent la migraine parqu'il est quand meme 7h du mat et je me leve dans 3h

//   Class GUI qui g�re les skins du jeu
//   Elle est capable de charger des skins � l
//   a voler ou de charger une fenetre 
//   � la demande



LRESULT CALLBACK SkinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam); //le proc de la fenetre skin�e

class CGui
{
private:
	HWND hWindow;	// le handler vers la fenetre
	CBmpManager bmp; // l'image de fond
	LPTSTR skin;	// le skin actuel
	LPTSTR wndName;// Le nom de la fen�tre
	CBouton * boutons;
	BYTE nbBoutons;
	BYTE nbEdit;
	BYTE nbListBox;
	CTexte* edit;
	CListBx* listBox;
public:
	CGui(void);	    // Constructeur par d�faut
	CGui(LPTSTR name); // Constructeur par param�tre
	~CGui(void);	// Destructeur
	bool loadSkin(LPTSTR skinName);	// charge un skin et l'applique
	static LPTSTR fileSeek(LPTSTR wnd); // recherche du fichier associ� 
	void error(LPTSTR texte, bool end); // petite fonction pour quitter le programme avec un message
	inline const HWND getHwnd() {return hWindow;} //r�cup�rer le handler de la fenetre
	void drawChild(LPDRAWITEMSTRUCT lPdis);

};



 