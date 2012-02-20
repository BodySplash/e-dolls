#include "ctexte.h"


WNDPROC oldProc;

LRESULT CALLBACK scrollProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam); // la proc permettant de dessiner les scroll


LRESULT CALLBACK scrollProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	
	

	switch (message) {
		
		case WM_VSCROLL:
			InvalidateRect(hwnd, NULL, false);
			break;
		case WM_HSCROLL:
			InvalidateRect(hwnd, NULL, false);
			break;

	}
	
	return CallWindowProc(oldProc, hwnd, message, wParam, lParam);
}


CTexte::CTexte(void)
{
}



bool CTexte::create(LPTSTR *fileName, UINT ident, POINT pos, HWND parent, int width, int height, bool readOnly) {
	position.x = pos.x;
	position.y = pos.y;
	DWORD style = WS_CHILD|WS_VISIBLE|WS_VSCROLL|ES_AUTOVSCROLL|ES_LEFT|ES_MULTILINE;
	if (readOnly)
		style = style |ES_READONLY;

	hWindow = CreateWindow(TEXT("edit"),NULL,style , pos.x, pos.y, width, height, parent, (HMENU) ident, hInst, NULL);
	
	oldProc = (WNDPROC) SetWindowLong(hWindow, GWL_WNDPROC, (LONG)scrollProc);
	ID = ident;
	return true;

}

void CTexte::draw(HDC where) {
	
//InvalidateRect(hWindow, NULL, true);


}


CTexte::~CTexte(void)
{
}
