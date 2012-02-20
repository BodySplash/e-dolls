#include "CGui.h"



// déclarations des fonctions utiles
ATOM	MyRegisterClass(HINSTANCE hInstance);
BOOL	InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);



LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
			
	}
	return 0;
}


int WINAPI WinMain ( HINSTANCE hInstance , HINSTANCE hPrevInstance , LPSTR lpCmdLine , int nShowCmd )
{
	MSG msg;
	
	
	MyRegisterClass(hInstance);
	if (!InitInstance(hInstance, nShowCmd)){
		return FALSE;
	}

	
	CGui test("chat"); // cette ligne et la seule chose nécessaire pour charger une fenetre skinnée

	// message pump
	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	

	delete [] wndList;

	return (int) msg.wParam;

}



ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW| CS_DBLCLKS | CS_OWNDC ;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= NULL;
	wcex.hCursor		= NULL ;
	wcex.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= WINDOWCLASS;
	wcex.hIconSm		= NULL;

	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
  

   hInst = hInstance; // Stocke le handle d'instance dans la variable globale

   mainHwnd = CreateWindowEx (0 , WINDOWCLASS , WINDOWTITLE , WS_OVERLAPPEDWINDOW , 0 , 0 , 640 , 480 , NULL , NULL , hInstance , NULL ) ;
  /* CreateWindow(TEXT("edit"),NULL, WS_CHILD|WS_VISIBLE|WS_VSCROLL|ES_AUTOVSCROLL|ES_LEFT|ES_MULTILINE, 0, 0, 373, 286, mainHwnd, (HMENU) 1, hInst, NULL);
   SetWindowLong(mainHwnd, GWL_EXSTYLE, GetWindowLong(mainHwnd, GWL_EXSTYLE)|WS_EX_LAYERED|WS_EX_NOINHERITLAYOUT);
  SetLayeredWindowAttributes(mainHwnd, 0, (255 * 70) / 100, LWA_ALPHA|LWA_COLORKEY);
  ShowWindow(mainHwnd, SW_SHOWNA);
   UpdateWindow(mainHwnd);*/



   if (!mainHwnd)
   {
      return FALSE;
   }

   return TRUE;
}