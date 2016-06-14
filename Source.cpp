#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<commctrl.h>
#include<limits.h>
#include<time.h>

#define id_next 1
#define id_exit 2
#define id_vectori 3
#define id_listeS 4
#define id_listeD 5
#define id_grafic 7
#define id_vectori 8
#define id_listesimple 9
#define id_listeduble 10
#define id_back 11

HWND rezultat;

int nr_step_vectori = 0,nr_step_liste = 0,nr_step_listeD = 0;
bool alg_sortare = false;

int vector[200];
char c[200];
int nrelem;
void change(int** a, char*** c, int n)
{
	for (int i = 0; i < n; i++)
	{
		(*c)[i] = (char*)malloc(10);
		_itoa((*a)[i], (*c)[i], 10);
			
	}
}


void bubbleSort(int v[100],int n, HWND hwnd)
{
	char** sir;
	sir = (char**)malloc(sizeof(char*)*n);
	 int ok = 1;
	int aux;
	do
	{
		ok = 0;
		for (int i = 0; i<n - 1; i++)
		{
			if (v[i]>v[i + 1])
			{
				aux = v[i];
				v[i] = v[i + 1];
				v[i + 1] = aux;
				ok = 1;
			}
			nr_step_vectori++;
		}
	} while (ok);

	char string[2000];
	change(&v, &sir, n);
	strcpy(string, sir[0]);
	strcat(string, " ");

	for (int i = 1; i < n; i++)
	{
		strcat(string, sir[i]);
		strcat(string, " ");
	}
	rezultat = CreateWindow("Static", TEXT(string),
		WS_CHILD | WS_VISIBLE | SS_LEFT,
		50, 60, 300, 230, hwnd, NULL, NULL, NULL);
	
	SendMessage(rezultat,     /*HWND*/        /*Label*/
		WM_SETTEXT,     /*UINT*/        /*Message*/
		NULL,           /*WPARAM*/      /*Unused*/
		(LPARAM)TEXT(string));  /*LPARAM*/      /*Text*/
}

typedef struct simpla
{
	int key;
	simpla *urm;
};

typedef struct dubla
{
	int key;
	dubla *urm, *pre;
};

simpla *prims = 0;
simpla *ultims = 0;
dubla *primd = 0;
dubla *ultimd = 0;

int searchS(int key)
{
	simpla *p = prims;
	while (p != NULL)
	{
		if (p->key == key)
			return 1;
		p = p->urm;
	}
	return 0;
}

void inserts(int key)
{
	simpla *p;
	p = (simpla *)malloc(sizeof(simpla)); /* rezervare spatiu de memorie în heap*/
	p->key = key; //citire date în nodul de adresa p;
	if (searchS(key) == 1)
		return;
	p->urm = 0; /*nodul este ultimul în lista */

	if (ultims != 0)
		ultims->urm = p; /* lista nu este vida */
	else
		prims = p; /* nodul p este primul introdus în lista */
	ultims = p;
	
}

int searchD(int key)
{
	dubla *p = primd;
	while (p != NULL)
	{
		if (p->key == key)
			return 1;
		p = p->urm;
	}
	return 0;
}

void insertd(int key)
{
	dubla *p;
	p = (dubla*)malloc(sizeof(dubla));
	p->key = key;
	if (searchD(key) == 1)
		return;
	if (primd == 0)
	{
		/* este primul nod în lista */
		primd = p;
		ultimd = p;
		p->urm = 0;
		p->pre = 0;
	}
	else
	{
		/* lista nu este vida */
		ultimd->urm = p;
		p->pre = ultimd;
		p->urm = 0;
		p->pre = ultimd;
		ultimd = p;
	}
}


void bubble_liste_simple(int n)
{
	simpla *i=prims;
	int ok = 1;
	int aux;
	
	do
	{
		ok = 1;
		for (i = prims; i->urm; i = i->urm)
		{
			if (i->key > i->urm->key) //interschimba
			{
				aux = i->key;
				i->key = i->urm->key;
				i->urm->key = aux;
				ok = 0;

			}
			nr_step_liste++;
		}
	} while (!ok);
}

void bubble_liste_dubla(int n)
{
	dubla *i;
	int ok = 1;
	int aux;
	int x;

	do
	{
		ok = 1;
		for (i = primd; i->urm; i = i->urm)
		{
			if (i->key>i->urm->key) //interschimba
			{
				aux = i->key;
				i->key = i->urm->key;
				i->urm->key = aux;
				ok = 0;
			}
			nr_step_listeD++;
		}

	} while (!ok);

}

void afisare(HWND hwnd)
{
	simpla *p;
	p = prims;
	int* a = NULL;
	int k = 0;
	while (p)
	{
		a = (int*)realloc(a, (k + 1)*sizeof(int));
		a[k] = p->key;
		k++;
		p = p->urm;
	}
	char** sir;
	sir = (char**)malloc(sizeof(char*)*k);
	char string[2000];
	change(&a, &sir, k);
	strcpy(string, sir[0]);
	strcat(string, " ");

	for (int i = 1; i < k; i++)
	{
		strcat(string, sir[i]);
		strcat(string, " ");
	}
	rezultat = CreateWindow("Static", TEXT(string),
		WS_CHILD | WS_VISIBLE | SS_LEFT,
		50, 60, 300, 230, hwnd, NULL, NULL, NULL);

	SendMessage(rezultat,     /*HWND*/        /*Label*/
		WM_SETTEXT,     /*UINT*/        /*Message*/
		NULL,           /*WPARAM*/      /*Unused*/
		(LPARAM)TEXT(string));  /*LPARAM*/      /*Text*/


}


void afisareD(HWND hwnd)
{
	dubla *p;
	p = primd;
	int* a = NULL;
	int k = 0;
	while (p)
	{
		a = (int*)realloc(a, (k + 1)*sizeof(int));
		a[k] = p->key;
		k++;
		p = p->urm;
	}
	char** sir;
	sir = (char**)malloc(sizeof(char*)*k);
	char string[2000];
	change(&a, &sir, k);
	strcpy(string, sir[0]);
	strcat(string, " ");

	for (int i = 1; i < k; i++)
	{
		strcat(string, sir[i]);
		strcat(string, " ");
	}
	rezultat = CreateWindow("Static", TEXT(string),
		WS_CHILD | WS_VISIBLE | SS_LEFT,
		50, 60, 300, 230, hwnd, NULL, NULL, NULL);

	SendMessage(rezultat,     /*HWND*/        /*Label*/
		WM_SETTEXT,     /*UINT*/        /*Message*/
		NULL,           /*WPARAM*/      /*Unused*/
		(LPARAM)TEXT(string));  /*LPARAM*/      /*Text*/


}



LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HWND hwndedit, hwndNext, hwndExit, hwndmesaj, hwndmesaj4, hwndmesaj1, hwndmesaj2, hwndmesaj3, hwndvectori, hwndlistesimple, hwndlisteduble, hwndedit2, hwndgrafic, hwndback;



int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PWSTR pCmdLine, int nCmdShow) {

	MSG  msg;
	HWND hwnd;
	WNDCLASSW wc;

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.lpszClassName = L"Window";
	wc.hInstance = hInstance;
	wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	wc.lpszMenuName = NULL;
	wc.lpfnWndProc = WndProc;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassW(&wc);
	hwnd = CreateWindowW(wc.lpszClassName, L"BUBBLE SORT",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		400, 100, 550, 450, NULL, NULL, hInstance, NULL); //crearea primei ferestre

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) {

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
	WPARAM wParam, LPARAM lParam) {

	static wchar_t *mesaj = L"Dati numarul de elemente ce urmeaza sa fie sortate:";
	static wchar_t *mesaj2 = L"Introduceti elementele:";
	static wchar_t *mesaj3 = L"Bubble sort-vector:";
	static wchar_t *mesaj4 = L"Bubble sort-lista simplu inlantuita:";
	static wchar_t *mesaj5 = L"Bubble sort-lista dublu inlantuita:";
	switch (msg) {

	case WM_CREATE:
	{
					  hwndmesaj=CreateWindowW(L"Static", mesaj,
						  WS_CHILD | WS_VISIBLE | SS_LEFT,
						  50, 20, 700, 230, hwnd, (HMENU)1, NULL, NULL); //primul rand din fereastra

					  hwndNext=CreateWindowW(L"Button", L"NEXT",
						  WS_CHILD | WS_VISIBLE | SS_LEFT,
						  350, 350, 70, 25, hwnd, (HMENU)id_next, NULL, NULL); //butonul next

					 hwndExit=CreateWindowW(L"Button", L"EXIT",
					  WS_CHILD | WS_VISIBLE | SS_LEFT,
					  80, 350, 80, 25, hwnd, (HMENU)id_exit, NULL, NULL); //butonul exit

					  hwndedit=CreateWindow( "Edit", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 40, 60, 50, 20, hwnd, (HMENU)3, NULL, NULL); //casuta de introducere



	};
		break;
		
	case WM_COMMAND:
	{
					   switch (LOWORD(wParam))
					   {
					   case id_next:
					   {
									  

									   int abc = 0;
									   char text[100];
									   char *g = &text[0];
									   char inf[100];
									   strcpy(text, "");
									   abc = GetWindowText(hwndedit, g, 100);
									   strcpy(inf, text);
									   if (strcmp(inf,"")==0)
										   MessageBox(hwnd, "Introduceti numarul de elemente!", "Eroare", MB_ICONERROR);

									   else
									   {
										   nrelem = atoi(inf);
										   ShowWindow(hwndNext, SW_HIDE);
										   ShowWindow(hwndExit, SW_HIDE);
										   ShowWindow(hwndedit, SW_HIDE);
										   ShowWindow(hwndmesaj, SW_HIDE);


										   hwndmesaj4 = CreateWindowW(L"Static", mesaj2,
											   WS_CHILD | WS_VISIBLE | SS_LEFT,
											   50, 20, 300, 230, hwnd, (HMENU)5, NULL, NULL); //INTRODUCETI ELEMENTELE

										   hwndedit2 = CreateWindow("Edit", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 20, 60, 500, 20, hwnd, (HMENU)3, NULL, NULL);

										   hwndvectori = CreateWindowW(L"Button", L"Vectori",
											   WS_CHILD | WS_VISIBLE | SS_LEFT,
											   80, 250, 80, 25, hwnd, (HMENU)id_vectori, NULL, NULL);

										   hwndlistesimple = CreateWindowW(L"Button", L"ListeS",
											   WS_CHILD | WS_VISIBLE | SS_LEFT,
											   235, 250, 80, 25, hwnd, (HMENU)id_listeS, NULL, NULL);

										   hwndlisteduble = CreateWindowW(L"Button", L"ListeD",
											   WS_CHILD | WS_VISIBLE | SS_LEFT,
											   380, 250, 80, 25, hwnd, (HMENU)id_listeD, NULL, NULL);

										   hwndgrafic = CreateWindowW(L"Button", L"NUMAR PASI",
											   WS_CHILD | WS_VISIBLE | SS_LEFT,
											   190, 350, 130, 45, hwnd, (HMENU)id_grafic, NULL, NULL);
									   }
					   };
						   break;

					   case id_vectori:{

										   
										   int abc = 0;
										   char text[200];
										   char *g = &text[0];
										   char inf[400];
										   strcpy(text, "");
										   abc = GetWindowText(hwndedit2, g, 400);
										   strcpy(inf, text);
										   if (strcmp(inf, "") == 0)
										   {
											   MessageBox(hwnd, "Introduceti elementele!", "Eroare", MB_ICONERROR);
										   }
										   else
										   {

											   int y = 0;
											   char* l;
											   l = strtok(inf, " ");
											   while (l)
											   {
												   vector[y] = atoi(l);
												   y++;
												   l = strtok(NULL, " ");
											   }

											   if (y != nrelem)
											   {
												   MessageBox(hwnd, "Numarul de elemente este incorect!", "Eroare", MB_ICONERROR);
											   }
											   else
											   {


												   ShowWindow(hwndNext, SW_HIDE);
												   ShowWindow(hwndExit, SW_HIDE);
												   ShowWindow(hwndedit, SW_HIDE);
												   ShowWindow(hwndmesaj, SW_HIDE);
												   ShowWindow(hwndvectori, SW_HIDE);
												   ShowWindow(hwndlistesimple, SW_HIDE);
												   ShowWindow(hwndlisteduble, SW_HIDE);
												   ShowWindow(hwndmesaj4, SW_HIDE);
												   ShowWindow(hwndedit2, SW_HIDE);
												   ShowWindow(hwndgrafic, SW_HIDE);

												   bubbleSort(vector, y, hwnd);
												   hwndback = CreateWindowW(L"Button", L"Back",
													   WS_CHILD | WS_VISIBLE | SS_LEFT,
													   80, 350, 80, 25, hwnd, (HMENU)id_back, NULL, NULL);
												   hwndmesaj1 = CreateWindowW(L"Static", mesaj3,
													   WS_CHILD | WS_VISIBLE | SS_LEFT,
													   50, 20, 300, 25, hwnd, (HMENU)5, NULL, NULL);
											   }
										   }

										  
					   }; break;

					   case id_listeS:{
										  
										  

										  char inf[400];
										  char inf1[400];
										  int abc = 0;
										  char text[200];
										  char* g = &text[0];
										  strcpy(text, "");
										  abc = GetWindowText(hwndedit2, g, 400);
										  strcpy(inf, text);
										  strcpy(inf1, inf);
										  if (strcmp(inf, "") == 0)
										  {
											  MessageBox(hwnd, "Introduceti elementele!", "Eroare", MB_ICONERROR);
										  }
										  else
										  {

											 

											  char* l;
											  int n = 0;
											  l = strtok(inf1, " ");
											  simpla* p = prims;
											  while (l)
											  {
												  n++;
												  l = strtok(NULL, " ");

											  }
											  if (n != nrelem)
											  {
												  MessageBox(hwnd, "Numarul de elemente este incorect!", "Eroare", MB_ICONERROR);
											  }
											  else
											  {
												  l = strtok(inf, " ");
												  n = 0;
												  while (l)
												  {
													  inserts(atoi(l));
													  n++;
													  l = strtok(NULL, " ");

												  }

												  ShowWindow(hwndNext, SW_HIDE);
												  ShowWindow(hwndExit, SW_HIDE);
												  ShowWindow(hwndedit, SW_HIDE);
												  ShowWindow(hwndmesaj, SW_HIDE);
												  ShowWindow(hwndvectori, SW_HIDE);
												  ShowWindow(hwndlistesimple, SW_HIDE);
												  ShowWindow(hwndlisteduble, SW_HIDE);
												  ShowWindow(hwndmesaj4, SW_HIDE);
												  ShowWindow(hwndedit2, SW_HIDE);
												  ShowWindow(hwndgrafic, SW_HIDE);

												  hwndmesaj1 = CreateWindowW(L"Static", mesaj4,
													  WS_CHILD | WS_VISIBLE | SS_LEFT,
													  50, 20, 300, 25, hwnd, (HMENU)5, NULL, NULL);
												  bubble_liste_simple(n);
												  afisare(hwnd);
												  hwndback = CreateWindowW(L"Button", L"Back",
													  WS_CHILD | WS_VISIBLE | SS_LEFT,
													  80, 350, 80, 25, hwnd, (HMENU)id_back, NULL, NULL);
											  }
										  }

					   }; break;
				
					   case id_listeD:{
										  
										  char inf[400], inf1[400];
										  int abc = 0;
										  char text[200];
										  char* g = &text[0];
										  strcpy(text, "");
										  abc = GetWindowText(hwndedit2, g, 400);
										  strcpy(inf, text);
										  strcpy(inf1, inf);
										  if (strcmp(inf, "") == 0)
										  {
											  MessageBox(hwnd, "Introduceti elementele!", "Eroare", MB_ICONERROR);
										  }
										  else
										  {
											


											  

											  char* l;
											  int n = 0;
											  l = strtok(inf, " ");
											  dubla* p = primd;
											  while (l)
											  {
												  n++;
												  l = strtok(NULL, " ");

											  }
											  if (n != nrelem)
											  {
												  MessageBox(hwnd, "Numarul de elemente este incorect!", "Eroare", MB_ICONERROR);
											  }
											  else
											  {
												  n = 0;
												  l = strtok(inf1, " ");
												  while (l)
												  {
													  insertd(atoi(l));
													  n++;
													  l = strtok(NULL, " ");

												  }

												  ShowWindow(hwndNext, SW_HIDE);
												  ShowWindow(hwndExit, SW_HIDE);
												  ShowWindow(hwndedit, SW_HIDE);
												  ShowWindow(hwndmesaj, SW_HIDE);
												  ShowWindow(hwndvectori, SW_HIDE);
												  ShowWindow(hwndlistesimple, SW_HIDE);
												  ShowWindow(hwndlisteduble, SW_HIDE);
												  ShowWindow(hwndmesaj4, SW_HIDE);
												  ShowWindow(hwndedit2, SW_HIDE);
												  ShowWindow(hwndgrafic, SW_HIDE);

												  bubble_liste_dubla(nrelem);

												  hwndmesaj1 = CreateWindowW(L"Static", mesaj5,
													  WS_CHILD | WS_VISIBLE | SS_LEFT,
													  50, 20, 300, 25, hwnd, (HMENU)5, NULL, NULL);
												  
												  hwndback = CreateWindowW(L"Button", L"Back",
													  WS_CHILD | WS_VISIBLE | SS_LEFT,
													  80, 350, 80, 25, hwnd, (HMENU)id_back, NULL, NULL);
												  afisareD(hwnd);
											  }
										  }
					   }; break;
					   case id_back:{
										ShowWindow(hwndmesaj4, SW_SHOW);
										ShowWindow(hwndedit2, SW_SHOW);
										ShowWindow(rezultat, SW_HIDE);
										ShowWindow(hwndback, SW_HIDE);
										ShowWindow(hwndvectori, SW_SHOW);
										ShowWindow(hwndlistesimple, SW_SHOW);
										ShowWindow(hwndlisteduble, SW_SHOW);
										ShowWindow(hwndgrafic, SW_SHOW);
										ShowWindow(hwndmesaj1, SW_HIDE);
					   }; break;
					   case id_grafic:{
								  char buffff[100];
								  sprintf(buffff, "%d  %d  %d", nr_step_liste, nr_step_vectori, nr_step_listeD);
								  MessageBox(hwnd, buffff, "sjan", MB_ICONEXCLAMATION);
					   }; break;
					   case id_exit:{
										PostQuitMessage(0);
					   }; break;


					   }; break;
	}

	case WM_DESTROY:

		PostQuitMessage(0);
		break;
	}

	return DefWindowProcW(hwnd, msg, wParam, lParam);	
}