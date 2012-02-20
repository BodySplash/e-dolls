#pragma once

#define _WIN32_WINNT		0x500	//Dis qu'on fais un prog pour windows 2k et plus !
#define WIN32_LEAN_AND_MEAN			// Exclure les en-têtes Windows rarement utilisés
#define WINDOWCLASS "GUI"
#define WINDOWTITLE "Skinnable demo"



#include <Windows.h>
#include <Wingdi.h>
#include "imgdecoder.h"
#include <stdio.h>
#include <fstream.h>
#include <stdlib.h>

/* 
	Structure de recherche des skins
*/

struct fileConfig {
	LPTSTR fileName;	//Emplacement du fichier config du skin	
	LPTSTR wndName;	    //Nom de la fenetre	
	fileConfig* next;	//Pointeur vers l'objet suivant
};


/*
	Quelques variables globales
*/
 __declspec(selectany) fileConfig *wndList = NULL;	//liste des skins
 __declspec(selectany) HINSTANCE hInst = NULL; //handler de l'application
 __declspec(selectany) HWND mainHwnd = NULL; // handler de la fenetre principale
 





