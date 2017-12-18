#pragma once
//This class create image window for ClientView. This window show photo selected client in ClientList window
#include <Windows.h>
#include "Constants.h"
class ClientImageWnd
{
private:
	HWND mainWnd;                  //main app window(init in constructor)
public:
	ClientImageWnd();              //constructor create "static" control for show image of current client(selected in Client ListView)
	~ClientImageWnd();             //destructor
	void loadNullImage(void);      //load empty bitmap
	void showImageWindow(void);    //show image window
	void DestroyImageWindow();     //destroy image window
	void hideImageWindow(void);    //hide image window
};

