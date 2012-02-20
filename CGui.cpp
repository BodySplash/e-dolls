#include "CGui.h"

using namespace std;




LRESULT CALLBACK AniProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	static POINTS rectPt;
	static POINTS finalPt;
	static BOOL move = FALSE;
	switch (message) {
		
		case WM_QUIT:
			PostQuitMessage(0);
			return 0;

		case WM_MEASUREITEM:
			{
				LPMEASUREITEMSTRUCT lpmis = (LPMEASUREITEMSTRUCT) lParam; 

				// Set the height of the list box items. 

				lpmis->itemHeight = 30; 
				return TRUE; 
			}

		case WM_LBUTTONUP:
			// on a fini de déplacer la fenêtre
			if (move){
				// donc on relache la capture et le lock et on remet notre bool a faux
				ReleaseCapture();
				LockWindowUpdate(NULL);
				move = FALSE;
			}
			return 0;
		

		case WM_MOUSEMOVE:
			{
				// si on ne déplace pas encore la fenêtre et que le bouton gauche est enfoncé
				if (!move && (wParam & MK_LBUTTON)){
					// alors on capture la souris
					SetCapture(hWnd);
					// on lock l'update pour éviter que qq chose se dessine par dessus
					LockWindowUpdate(hWnd);
					// on récupère les coord de la souris
					rectPt = MAKEPOINTS(lParam);
					// et on stipule que nous déplaçons la fenêtre
					move = TRUE;
				}
				// si nous déplaçons la fenêtre
				if (move){
					// on récupère le clientRect
					RECT rc;
					GetWindowRect(hWnd, &rc);
					
					// on met à jour les coordonnées en ajoutant à la position de la fenetre la position de la souris
					// moins la position de départ
					finalPt.x = rc.left+(LOWORD(lParam)-rectPt.x);
					finalPt.y = rc.top+(HIWORD(lParam)-rectPt.y); 
					// et on déplace la fenêtre
					MoveWindow(hWnd, finalPt.x, finalPt.y, rc.right-rc.left, rc.bottom-rc.top, TRUE);
				
				}
				return 0;
			}

			
			
	
		case WM_DRAWITEM:
			{
			// récupération de la classe CGui associée à la fenêtre
			LPDRAWITEMSTRUCT pdis = (LPDRAWITEMSTRUCT) lParam;
			CGui *p = (CGui *) GetWindowLongPtr(hWnd, GWLP_USERDATA);
			p->drawChild(pdis);
			return TRUE;
			
			}
		case  WM_COMMAND:
			{
				if (wParam == 1)
					PostQuitMessage(0) ;
				if (wParam == 3)
					ShowWindow(hWnd, SW_MINIMIZE);
				if (LOWORD(wParam) == 4)
					if (HIWORD(wParam) == EN_ERRSPACE || HIWORD(wParam) == EN_MAXTEXT)
						MessageBox(NULL, "Out of space", "erreur", MB_OK | MB_ICONSTOP);
				return 0;
			}
		

		
	
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	
return 0;
}

CGui::CGui(void)
{
	wndList = new fileConfig;
	wndList->fileName = "chat.txt";
	wndList->wndName = "chat";
	wndList->next = NULL;
	hWindow = NULL;
	boutons = NULL;
	edit = NULL;
	listBox = NULL;
	
	
	
}

CGui::CGui(LPTSTR name) {
	// remplissage de la liste, position provisoire
	wndList = new fileConfig;
	wndList->fileName = "chat.txt";
	wndList->wndName = "chat";
	wndList->next = NULL;
	hWindow = NULL;
	
	
	skin = fileSeek(name);
	if (skin == 0)
		error("Impossible de trouver la fenetre demandée", true);
	wndName =  name;
	// remplissage de la classe windows
	WNDCLASSEX wc ;
	wc.cbClsExtra = 0 ;	//no extra class information
	wc.cbSize = sizeof ( WNDCLASSEX ) ; //size of structure
	wc.cbWndExtra = 0 ;	//no extra window information
	wc.hbrBackground = CreateSolidBrush(RGB(255,0,255)) ;	//black brush
	wc.hCursor = LoadCursor(NULL, IDC_ARROW) ;	//no cursor
	wc.hIcon = NULL ;	//no icon
	wc.hIconSm = NULL ;	//no small icon
	wc.hInstance = hInst ;	//instance handle
	wc.lpfnWndProc = (WNDPROC) AniProc ;	//window procedure
	wc.lpszClassName = "chat" ;	//name of class
	wc.lpszMenuName = NULL ;	//no menu
	wc.style = CS_HREDRAW | CS_VREDRAW  ;	//class styles
	RegisterClassEx ( &wc );

	//création de la fenêtre en stipulant surtout WS_EX_LAYERED pour gérer la transparence
	hWindow = CreateWindowEx ( WS_EX_LAYERED|WS_EX_TOPMOST|WS_EX_NOINHERITLAYOUT  , wc.lpszClassName , "meuh" , WS_POPUP|WS_CHILD , 0 , 0 , 0 , 0 , NULL , NULL , hInst , NULL );
	SetWindowLongPtr(hWindow, GWLP_USERDATA, (LONG_PTR) this);
	// et chargeons gentiment le skin
	loadSkin(skin);
}

bool CGui::loadSkin(LPTSTR skinName){
	char *rd = new char[64];
	char *wd = new char[30];
	char *tmp = new char[30];
	POINT pt;
	nbBoutons = 0;
	nbListBox = 0;
	nbEdit = 0;

	int width, height, id;
	id = 0;
	fstream file("skin.txt", ios::in);
	file >> rd;
	file >> wd;
	file >> rd;
	strcpy(tmp, wd);
	
	rd = strcat(tmp, rd);
	
	bmp.load(rd);
	
	while (!file.eof()) {
		file >> rd;
		
		if (strcmp(rd, "nbBoutons")==0)
		{
			char *test[2];
			
			file >> rd;
			nbBoutons = atoi(rd);
			boutons = new CBouton[nbBoutons];
			for (int i = 0; i<nbBoutons; i++)
			{
				test[0] = new char[30];
				test[1] = new char[30];
				file >> pt.x;
				file >> pt.y;
				file >> rd;
				strcpy(test[0], rd);
				
				file >> rd;
				strcpy(test[1], rd);
				
				strcpy(tmp, wd);
				strcat(tmp, test[0]);
				strcpy(test[0], tmp);
				strcpy(tmp, wd);
				strcat(tmp, test[1]);
				strcpy(test[1], tmp);

				boutons[i].create(test,id, pt, hWindow);
				
				id++;
			}
		}
		if (strcmp(rd, "nbEdit") == 0)
		{
			file >> rd;
			nbEdit = atoi(rd);
			edit = new CTexte[nbEdit];
			BOOL readOnly;
			for (int i = 0; i<nbEdit; i++)
			{
				file >> pt.x;
				file >> pt.y;
				file >> width;
				file >> height;
				file >> readOnly;
				edit[i].create(NULL, id, pt, hWindow, width, height, readOnly);
				id++;
			}
		}
		if (strcmp(rd, "nbList") == 0)
		{
			file >> rd;
			nbListBox = atoi(rd);
			listBox = new CListBx[nbListBox];
			LPTSTR *f = new LPTSTR[3];
			f[0] = "images/listIcones/tekki.png";
			f[1] = "images/listIcones/barbare.png";
			f[2] = "images/listIcones/voleuse.png";
			for (int i = 0; i< nbListBox; i++)
			{
				file >> pt.x;
				file >> pt.y;
				file >> width;
				file >> height;
				listBox[i].create(f, id, pt, hWindow, width, height, 3);
				id++;
			}
		}


		
	}
	file.close();

	if (nbListBox){
		listBox->addItem("Aran", 0);
		listBox->addItem("BodySplash", 1);
		listBox->addItem("Poncherello", 2);
		listBox->addItem("BaLisTicK", 1);
		listBox->addItem("Makimura", 0);
		listBox->addItem("DarkWolf", 2);
		listBox->addItem("Tom", 0);
		listBox->addItem("Ouroboros", 2);
	}
	MoveWindow(hWindow, 0, 0, bmp.getWidth(), bmp.getHeight(), FALSE);
	SetLayeredWindowAttributes(hWindow, RGB(255, 0, 255), 255, LWA_COLORKEY);

	ShowWindow(hWindow, SW_SHOWNA);
	UpdateWindow(hWindow);
	return true;
}


void CGui::error(LPTSTR texte, bool end) {
	MessageBox(NULL, texte, "Erreur", MB_OK);
	if (end)
		PostQuitMessage(0);
}

LPTSTR CGui::fileSeek(LPTSTR wnd) {
	// recherche du fichier config associé
	fileConfig *temp;
	temp = wndList;
	while (temp !=NULL){
		if (wnd == temp->wndName)
			return temp->fileName;
		temp = temp->next;
	}
	return 0;
}




	




void CGui::drawChild(LPDRAWITEMSTRUCT lPdis) {
	
	HDC hdc = GetDC(hWindow); // récupération du DC

	BLENDFUNCTION bf; // déclaration de notre fonction de transparence
	bf.BlendOp = AC_SRC_OVER; 
	bf.BlendFlags = 0; 
	bf.SourceConstantAlpha = 255; // l'image doit être opaque 
	bf.AlphaFormat = AC_SRC_ALPHA;  // utilisation de l'alpha channel de notre image  
	AlphaBlend(hdc, 0, 0, 
		bmp.getWidth(), bmp.getHeight(), 
		bmp.getHdc(), 0, 0, bmp.getWidth(), bmp.getHeight(), bf); // et on copie l'interface principale sur notre fenetre
	for (int i = 0; i<nbBoutons; i++) // on dessine ensuite nos boutons
		boutons[i].draw(hdc, lPdis);
	for (int i = 0; i<nbEdit; i++)
		edit[i].draw(hdc);
	for (int i = 0; i<nbListBox; i++)
		listBox[0].draw(hdc, lPdis);
	ReleaseDC(hWindow, hdc); // on relache le dc
	
}




CGui::~CGui(void)
{
	if (edit!=NULL)
		delete [] edit;
	if (boutons!=NULL)
		delete[] boutons;
	if (listBox != NULL)
		delete[] listBox;

}
