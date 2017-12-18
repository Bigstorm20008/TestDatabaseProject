#include "ClientImageWnd.h"


ClientImageWnd::ClientImageWnd()
{
	extern LPTSTR szClassName;                                 //window class of main app window(init in main.cpp)
	extern LPTSTR szWindowName;                                //title of main app window(init in main.cpp)
	mainWnd = FindWindow(szClassName, szWindowName);           //find handler of main window

	//Create static control window
	HWND staticWnd = CreateWindow(TEXT("STATIC"),
		                          NULL,
								  WS_CHILD | WS_VISIBLE | WS_BORDER | SS_BITMAP | SS_NOTIFY,
								  5,     
								  55,
								  NULL,    //is not required if SS_BITMAP(width set by BITMAP)
								  NULL,    //is not required if SS_BITMAP(height set by BITMAP)
								  mainWnd, 
								  (HMENU)ID_IMAGE_WND, //defined in Constatnts.h
								  (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
								  NULL);
	//Load empty bitmap and set it
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
	HWND imgWnd = GetDlgItem(mainWnd, ID_IMAGE_WND);   //get handler to image window by identifier
	DestroyWindow(imgWnd);                             //destroy image window
}

void ClientImageWnd::hideImageWindow(void)
{
	HWND imgWnd = GetDlgItem(mainWnd, ID_IMAGE_WND);  //get handler to image window by identifier
	ShowWindow(imgWnd, SW_HIDE);                      //hide image window
}

void ClientImageWnd::showImageWindow(void)
{
	HWND imgWnd = GetDlgItem(mainWnd, ID_IMAGE_WND);  //get handler to image window by identifier
	ShowWindow(imgWnd, SW_NORMAL);                    //show image window
}

void ClientImageWnd::loadNullImage(void)
{ 
	HWND imgWnd = GetDlgItem(mainWnd, ID_IMAGE_WND);  //get handler to image window by identifier
	//Load empty bitmap and set it
	HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, TEXT("D:\\Clients\\Безымянный1.bmp"), IMAGE_BITMAP, imageWidth, imageHeight, LR_LOADFROMFILE);
	SendMessage(imgWnd, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);
	ShowWindow(imgWnd, SW_NORMAL);
	UpdateWindow(imgWnd);
}
