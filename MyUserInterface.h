#pragma once
#include <Windows.h>

#include "ControlPanel.h"
#include "MyButton.h"
#include "Constants.h"




class MyUserInterface
{
private:
	HWND parentWnd;
	void CreateInterfaceForCashier(void);
	void CreateMainPanel(UINT identify);
	void CreateButtons(int* buttons,size_t len);
public:
	MyUserInterface(TCHAR* pRoleMember);
	~MyUserInterface();
};

