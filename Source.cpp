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

HWND rezultat;

int vector[200];
char ch[200];

void change(int** a, char*** c, int n)
{
	for (int i = 0; i < n; i++)
	{
		(*c)[i] = (char*)malloc(10);
		_itoa((*a)[i], (*c)[i], 10);
			
	}
}


void bublleSort(int v[100],int n, HWND hwnd)
{
	char** sir;
	sir = (char**)malloc(sizeof(char*)*n);
	bool ok = TRUE;
	int temporal;
	do
	{
		ok = FALSE;
		for (int i = 0; i<n - 1; i++)
		{
			if (v[i]>v[i + 1])
			{
				temporal = v[i];
				v[i] = v[i + 1];
				v[i + 1] = temporal;
				ok = TRUE;
			}
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
		30, 20, 300, 30, hwnd, NULL, NULL, NULL);

	SendMessage(rezultat,     /*HWND*/        /*Label*/
		WM_SETTEXT,     /*UINT*/        /*Message*/
		NULL,           /*WPARAM*/      /*Unused*/
		(LPARAM)TEXT(string));  /*LPARAM*/      /*Text*/
}






LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HWND hwndedit, hwndNext, hwndExit, hwndmesaj, hwndmesaj4, hwndmesaj1, hwndmesaj2, hwndmesaj3, hwndvectori, hwndlistesimple, hwndlisteduble, hwndedit2, hwndgrafic;




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
						  350, 350, 70, 25, hwnd, (HMENU)id_next, NULL, NULL);

					 hwndExit=CreateWindowW(L"Button", L"EXIT",
					  WS_CHILD | WS_VISIBLE | SS_LEFT,
					  80, 350, 80, 25, hwnd, (HMENU)id_exit, NULL, NULL);

					  hwndedit=CreateWindow( "Edit", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 40, 60, 50, 20, hwnd, (HMENU)3, NULL, NULL);



	};
		break;
		
	case WM_COMMAND:
	{
					   switch (LOWORD(wParam))
					   {
					   case id_next:
					   {
									   ShowWindow(hwndNext, SW_HIDE);
									   ShowWindow(hwndExit, SW_HIDE);
									   ShowWindow(hwndedit, SW_HIDE);
									   ShowWindow(hwndmesaj, SW_HIDE);

									   int abc = 0;
									   char text[100];
									   char *g = &text[0];
									   char inf[100];
									   strcpy(text, "");
									   abc = GetWindowText(hwndedit, g, 100);
									   strcpy(inf, text);




									   hwndmesaj4=CreateWindowW(L"Static", mesaj2,
										   WS_CHILD | WS_VISIBLE | SS_LEFT,
										   50, 20, 300, 230, hwnd, (HMENU)5, NULL, NULL);

									   hwndedit2=CreateWindow("Edit", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 20, 60, 400, 20, hwnd, (HMENU)3, NULL, NULL);

									   hwndvectori=CreateWindowW(L"Button", L"Vectori",
										   WS_CHILD | WS_VISIBLE | SS_LEFT,
										   80, 250, 80, 25, hwnd, (HMENU)id_vectori, NULL, NULL);

									   hwndlistesimple=CreateWindowW(L"Button", L"ListeSimple",
										   WS_CHILD | WS_VISIBLE | SS_LEFT,
										   235, 250, 80, 25, hwnd, (HMENU)id_listeS, NULL, NULL);

									   hwndlisteduble=CreateWindowW(L"Button", L"ListeDuble",
										   WS_CHILD | WS_VISIBLE | SS_LEFT,
										   380, 250, 80, 25, hwnd, (HMENU)id_listeD, NULL, NULL);

									   hwndgrafic=CreateWindowW(L"Button", L"GraficEFIECIENTA",
										   WS_CHILD | WS_VISIBLE | SS_LEFT,
										   190, 350, 130, 45, hwnd, (HMENU)id_grafic, NULL, NULL);
					   };
						   break;

					   case id_vectori:{

										   ShowWindow(hwndNext, SW_HIDE);
										   ShowWindow(hwndExit, SW_HIDE);
										   ShowWindow(hwndedit, SW_HIDE);
										   ShowWindow(hwndmesaj, SW_HIDE);
										   ShowWindow(hwndvectori, SW_HIDE);
										   ShowWindow(hwndlistesimple, SW_HIDE);
										   ShowWindow(hwndlisteduble , SW_HIDE);
										   ShowWindow(hwndmesaj4, SW_HIDE);
										   ShowWindow(hwndedit2, SW_HIDE);
										   ShowWindow(hwndgrafic, SW_HIDE);

										   int abc = 0;
										   char text[200];
										   char *g = &text[0];
										   char inf[400];
										   strcpy(text, "");
										   abc = GetWindowText(hwndedit2, g, 400);
										   strcpy(inf, text);


										   int y = 0;
										   char* l;
										   l = strtok(inf, " ");
										   while (l)
										   {
											   vector[y] = atoi(l);
											   y++;
											   l = strtok(NULL, " ");
										   }


										   bublleSort(vector, y, hwnd);



										  // hwndmesaj1 = CreateWindowW(L"Static", mesaj3,
											//   WS_CHILD | WS_VISIBLE | SS_LEFT,
											  // 50, 20, 300, 230, hwnd, (HMENU)5, NULL, NULL);
					   }; break;

					   case id_listeS:{
										  
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
											  50, 20, 300, 230, hwnd, (HMENU)5, NULL, NULL);

					   }; break;

					   case id_listeD:{
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

										  hwndmesaj1 = CreateWindowW(L"Static", mesaj5,
											  WS_CHILD | WS_VISIBLE | SS_LEFT,
											  50, 20, 300, 230, hwnd, (HMENU)5, NULL, NULL);
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