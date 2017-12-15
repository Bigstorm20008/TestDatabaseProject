#pragma once

#include <Windows.h>
#include <windowsx.h>
#include "Constants.h"

class AuxiliaryWindows
{
	HWND mainWnd;
	int auxiliaryWndWidth;
	int auxiliaryWndHeight;
	int xPosCentred;
	int yPosCentred;
public:
	void destroyAuxiliaryWindow();
	void createAddNewClientWnd();
	AuxiliaryWindows();
	~AuxiliaryWindows();
};

LRESULT CALLBACK addNewClientWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);