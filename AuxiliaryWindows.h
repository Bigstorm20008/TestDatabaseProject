#pragma once

#include <Windows.h>
#include <windowsx.h>
#include "Constants.h"
#include "SqlFramework.h"

class AuxiliaryWindows
{
	HWND mainWnd;
	int auxiliaryWndWidth;
	int auxiliaryWndHeight;
	int xPosCentred;
	int yPosCentred;
	void createEditBoxWithDescription(HWND parent, LPTSTR description,UINT editBoxIdentifier,UINT staticControlIdentifier,int editBox_xPos,int  editBox_yPos,int editBox_width,int editBox_height);
public:
	void destroyAuxiliaryWindow();
	void createAddNewClientWnd();
	AuxiliaryWindows();
	~AuxiliaryWindows();
};

LRESULT CALLBACK addNewClientWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);