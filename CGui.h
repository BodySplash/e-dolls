#pragma once

#include "config.h"
#include "CBouton.h"
#include "CBmpManager.h"
#include "CTexte.h"
#include "CListBx.h"


//TODO:
// ecrire une classe pour chaque type de controle qu'il puisse se dessiner eux-memes
// prevoir de stocker leur état
// mettre a jour du coup la classe Gui du dessus pour virer tous cex pointeurs et tableaux
// qui me donnent la migraine parqu'il est quand meme 7h du mat et je me leve dans 3h

//   Class GUI qui gère les skins du jeu
//   Elle est capable de charger des skins à l
//   a voler ou de charger une fenetre 
//   à la demande



LRESULT CALLBACK SkinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam); //le proc de la fenetre skinée

class CGui
{
private:
	HWND hWindow;	// le handler vers la fenetre
	CBmpManager bmp; // l'image de fond
	LPTSTR skin;	// le skin actuel
	LPTSTR wndName;// Le nom de la fenêtre
	CBouton * boutons;
	BYTE nbBoutons;
	BYTE nbEdit;
	BYTE nbListBox;
	CTexte* edit;
	CListBx* listBox;
public:
	CGui(void);	    // Constructeur par défaut
	CGui(LPTSTR name); // Constructeur par paramètre
	~CGui(void);	// Destructeur
	bool loadSkin(LPTSTR skinName);	// charge un skin et l'applique
	static LPTSTR fileSeek(LPTSTR wnd); // recherche du fichier associé 
	void error(LPTSTR texte, bool end); // petite fonction pour quitter le programme avec un message
	inline const HWND getHwnd() {return hWindow;} //récupérer le handler de la fenetre
	void drawChild(LPDRAWITEMSTRUCT lPdis);

};



 