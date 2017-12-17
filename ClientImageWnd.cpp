#include "ClientImageWnd.h"


ClientImageWnd::ClientImageWnd()
{
	extern LPTSTR szClassName;
	extern LPTSTR szWindowName;
	HWND mainWnd = FindWindow(szClassName, szWindowName);
	HWND staticWnd = CreateWindow(TEXT("STATIC"),
		                          NULL,
								  WS_CHILD | WS_VISIBLE | WS_BORDER | SS_BITMAP | SS_NOTIFY,
								  5,
								  55,
								  NULL,
								  NULL,
								  mainWnd, 
								  (HMENU)ID_IMAGE_WND,
								  (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
								  NULL);
	HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, TEXT("D:\\Clients\\Безымянный1.bmp"), IMAGE_BITMAP, imageWidth, imageHeight, LR_LOADFROMFILE);
	SendMessage(staticWnd, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);
	ShowWindow(staticWnd, SW_NORMAL);
	UpdateWindow(staticWnd);
}


ClientImageWnd::~ClientImageWnd()
{
}

void ClientImageWnd::DestroyImageWindow()
{
	extern LPTSTR szClassName;
	extern LPTSTR szWindowName;
	HWND mainWnd = FindWindow(szClassName, szWindowName);
	HWND imgWnd = GetDlgItem(mainWnd, ID_IMAGE_WND);
	DestroyWindow(imgWnd);
}

void ClientImageWnd::hideImageWindow(void)
{
	extern LPTSTR szClassName;
	extern LPTSTR szWindowName;
	HWND mainWnd = FindWindow(szClassName, szWindowName);
	HWND imgWnd = GetDlgItem(mainWnd, ID_IMAGE_WND);
	ShowWindow(imgWnd, SW_HIDE);
}

void ClientImageWnd::showImageWindow(void)
{
	extern LPTSTR szClassName;
	extern LPTSTR szWindowName;
	HWND mainWnd = FindWindow(szClassName, szWindowName);
	HWND imgWnd = GetDlgItem(mainWnd, ID_IMAGE_WND);
	ShowWindow(imgWnd, SW_NORMAL);
}

void ClientImageWnd::loadNullImage(void)
{
	extern LPTSTR szClassName;
	extern LPTSTR szWindowName;
	HWND mainWnd = FindWindow(szClassName, szWindowName);
	HWND imgWnd = GetDlgItem(mainWnd, ID_IMAGE_WND);
	HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, TEXT("D:\\Clients\\Безымянный1.bmp"), IMAGE_BITMAP, imageWidth, imageHeight, LR_LOADFROMFILE);
	SendMessage(imgWnd, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);
	ShowWindow(imgWnd, SW_NORMAL);
	UpdateWindow(imgWnd);
}
