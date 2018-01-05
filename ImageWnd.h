#pragma once
//This class create image window for ClientView. This window show photo selected client in ClientList window
#include <Windows.h>
#include "Constants.h"
#include "Client.h"
class ImageWnd
{
private:
	HWND mainWnd;            //main app window(init in constructor)
	HWND imageWnd;
	void loadPersonPhoto(SQLTCHAR* imageLocation);
public:
	ImageWnd(HWND parent);   //constructor create "static" control for show image of current client(selected in Client ListView)
	~ImageWnd();             //destructor
	void loadNullImage(void);      //load empty bitmap
	void loadPersonPhoto(Client* currentPerson);
	void showImageWindow(void);    //show image window
	void DestroyImageWindow();     //destroy image window
	void hideImageWindow(void);    //hide image window
};

