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



LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HWND hwndedit;


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
		400, 100, 700, 600, NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) {

		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
	WPARAM wParam, LPARAM lParam) {

	static wchar_t *mesaj = L"Dati numarul de elemente ce urmeaza sa fie sortate:";
	static wchar_t *mesaj2 = L"Dati elementele:";
	switch (msg) {

	case WM_CREATE:
	{
					  CreateWindowW(L"Static", mesaj,
						  WS_CHILD | WS_VISIBLE | SS_LEFT,
						  50, 20, 300, 230, hwnd, (HMENU)1, NULL, NULL);

					  CreateWindowW(L"Button", L"NEXT",
						  WS_CHILD | WS_VISIBLE | SS_LEFT,
						  450, 350, 80, 25, hwnd, (HMENU)id_next, NULL, NULL);

					  CreateWindowW(L"Button", L"EXIT",
					  WS_CHILD | WS_VISIBLE | SS_LEFT,
					  80, 350, 80, 25, hwnd, (HMENU)id_exit, NULL, NULL);

					  hwndedit=CreateWindow( L"Edit", L"", WS_CHILD | WS_VISIBLE | WS_BORDER, 40, 60, 50, 20, hwnd, (HMENU)3, NULL, NULL);



	};
		break;
		//Verificare
	case WM_COMMAND:
	{
					   switch (LOWORD(wParam))
					   {
					   case id_next:
					   {
									   CreateWindowW(L"Static", mesaj2,
										   WS_CHILD | WS_VISIBLE | SS_LEFT,
										   50, 20, 300, 230, hwnd, (HMENU)1, NULL, NULL);

									   CreateWindow(L"Edit", L"", WS_CHILD | WS_VISIBLE | WS_BORDER, 20, 60, 400, 20, hwnd, (HMENU)3, NULL, NULL);
					   };
						   break;
					   }
	}

	case WM_DESTROY:

		PostQuitMessage(0);
		break;
	}

	return DefWindowProcW(hwnd, msg, wParam, lParam);
}