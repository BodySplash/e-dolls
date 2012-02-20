#include "cbmpmanager.h"

CBmpManager::CBmpManager(void)
{
	hdcBmp = NULL;
	hBmp = NULL;


}

CBmpManager::CBmpManager(LPTSTR fileName) {
	load(fileName);
}

void CBmpManager::load(LPTSTR fileName) {
	hdcBmp = CreateCompatibleDC(NULL);
	BITMAP bitmap;	//Informations sur le bitmap
	BITMAPINFO * bif=new BITMAPINFO();	//Pour la création d'un bitmap a partir de son contenu
	//Variables pour la librairie de chargement de fichiers
	LPVOID m_pImgDecoder=NULL;
	LPBYTE bmpBits=NULL;
	LPVOID pImg= NULL;
	ImgNewDecoder(&m_pImgDecoder);	//Initialization de la librairie de chargement de fichier
	ImgNewDIBFromFile(m_pImgDecoder,fileName,&pImg);
	ImgGetHandle(pImg, &hBmp, (LPVOID *) &bmpBits);
	GetObject(hBmp, sizeof(BITMAP), &bitmap);
	// convertion des valeurs alpha
	alphaMultiply( bmpBits);
	// sauvegarde de l'image car ImgDeleteDIBSection détruit le premier handler
	bif->bmiHeader.biWidth = bitmap.bmWidth;
	bif->bmiHeader.biHeight=bitmap.bmHeight;
	bif->bmiHeader.biPlanes=bitmap.bmPlanes;
	bif->bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
	bif->bmiHeader.biBitCount=32;
	bif->bmiHeader.biCompression=BI_RGB;
	// convertion dans un 'joli' format windows
	hBmp = CreateDIBitmap(GetDC(NULL),&bif->bmiHeader, CBM_INIT, bmpBits, bif,DIB_RGB_COLORS);
	// supression des éléments temporaires
    ImgDeleteDIBSection(pImg);
	ImgDeleteDecoder(m_pImgDecoder);
	SelectObject(hdcBmp, hBmp);
}

void CBmpManager::alphaMultiply(LPBYTE pBitmapBits) {
	BITMAP bmpInfo;
	GetObject(hBmp,sizeof(BITMAP),&bmpInfo);

	// multiplié les couches rgb avec la valeur de la couche alpha
	for (int y=0; y<bmpInfo.bmHeight; ++y)
	{
		BYTE *pPixel= pBitmapBits + bmpInfo.bmWidth *4 * y;

		for (int x=0; x<bmpInfo.bmWidth ; ++x)
		{
			pPixel[0]= pPixel[0]*pPixel[3]/255;
			pPixel[1]= pPixel[1]*pPixel[3]/255;
			pPixel[2]= pPixel[2]*pPixel[3]/255;

			pPixel+= 4;
		}
	}
}

int CBmpManager::getHeight() {
	BITMAP bmp ;
	GetObject(hBmp, sizeof(BITMAP), &bmp);
	return bmp.bmHeight;
}

int CBmpManager::getWidth() {
	BITMAP bmp ;
	GetObject(hBmp, sizeof(BITMAP), &bmp);
	return bmp.bmWidth;
}



CBmpManager::~CBmpManager(void)
{
	DeleteDC(hdcBmp);
	DeleteObject(hBmp);
}
