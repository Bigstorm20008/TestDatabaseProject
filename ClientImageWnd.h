#pragma once
//This class create image window for ClientView. This window show photo selected client in ClientList window
#include <Windows.h>
#include "Constants.h"
class ClientImageWnd
{
public:
	ClientImageWnd();
	~ClientImageWnd();
	void loadNullImage(void);
	void showImageWindow(void);
	void DestroyImageWindow();
	void hideImageWindow(void);
};

