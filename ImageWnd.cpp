#include "ImageWnd.h"


ImageWnd::ImageWnd(HWND parent)
{
	mainWnd = parent;           // handler of main window

	RECT parentRC;
	GetClientRect(mainWnd, &parentRC);
	int imageXPos = parentRC.left + offsetBetweenWindow;
	int imageYPos = parentRC.top + offsetBetweenWindow;
	int imageWndWidth = imageWidth;
	int imageWndHeight = imageHeight;
	//Create static control window
	imageWnd = CreateWindow(TEXT("STATIC"),
		                          NULL,
								  WS_CHILD | WS_BORDER | SS_BITMAP | SS_NOTIFY,
								  imageXPos,
								  imageYPos,
								  imageWndWidth,    //is not required if SS_BITMAP(width set by BITMAP)
								  imageWndHeight,    //is not required if SS_BITMAP(height set by BITMAP)
								  mainWnd, 
								  (HMENU)ID_IMAGE_WND, //defined in Constatnts.h
								  (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
								  NULL);
	//Load empty bitmap and set it
	HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, TEXT("D:\\Clients\\Безымянный1.bmp"), IMAGE_BITMAP, imageWidth, imageHeight, LR_LOADFROMFILE);
	SendMessage(imageWnd, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);
}


ImageWnd::~ImageWnd()
{
}

void ImageWnd::DestroyImageWindow()
{
	
	DestroyWindow(imageWnd);                             //destroy image window
}

void ImageWnd::hideImageWindow(void)
{
	ShowWindow(imageWnd, SW_HIDE);                      //hide image window
}

void ImageWnd::showImageWindow(void)
{
	ShowWindow(imageWnd, SW_NORMAL);                    //show image window
}

void ImageWnd::loadNullImage(void)
{ 
	//Load empty bitmap and set it
	HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, TEXT("D:\\Clients\\Безымянный1.bmp"), IMAGE_BITMAP, imageWidth, imageHeight, LR_LOADFROMFILE);
	SendMessage(imageWnd, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);
	ShowWindow(imageWnd, SW_NORMAL);
	UpdateWindow(imageWnd);
}

void ImageWnd::loadPersonPhoto(SQLTCHAR* imageLocation)
{
	HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, imageLocation, IMAGE_BITMAP, imageWidth, imageHeight, LR_LOADFROMFILE);
	SendMessage(imageWnd, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);
	ShowWindow(imageWnd, SW_NORMAL);
	UpdateWindow(imageWnd);
}

void ImageWnd::loadPersonPhoto(Client* currentPerson)
{
	SQLTCHAR* imageLocation = currentPerson->getImageLocation();
	if (imageLocation)
	{
		loadPersonPhoto(imageLocation);
	}
	else
	{
		loadNullImage();
	}
}
