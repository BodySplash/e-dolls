#pragma once
#include "config.h"

class CBmpManager
{
private:
	HDC hdcBmp; // HDC ou placer l'image
	HBITMAP hBmp; // handler de l'image
public:
	CBmpManager(void);
	CBmpManager(LPTSTR fileName); // charger l'image depuis un fichier
	void load(LPTSTR fileName); // charger une image depuis un fichier
	int getHeight(); // retourner la hauteur
	int getWidth(); // retourner la largeur
	void  alphaMultiply(LPBYTE pBitmapBits); // fonction pour multiplier pour chaque pixel le R, V et B par la valeur alpha. Indispensable pour faire de l'alphaBlend
	inline const HDC getHdc() {return hdcBmp;}
	inline const HBITMAP getHwnd() {return hBmp;}
	~CBmpManager(void);
};
