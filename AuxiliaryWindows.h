#pragma once

#include <Windows.h>
#include <windowsx.h>
#include "Constants.h"
#include "SqlFramework.h"
#include "Client.h"
#include <commctrl.h>


class AuxiliaryWindows
{
	HWND mainWnd;
	HWND auxiliaryWnd;

	void createAuxiliaryWindow(int width, int height, TCHAR* captionText);
	void createEditBoxWithDescription(HWND parent, LPTSTR description,UINT editBoxIdentifier,int editBox_xPos,int  editBox_yPos,int editBox_width,int editBox_height);
	void createComboBoxForClientStatusSelect(HWND parent, UINT comboBoxIdentifier, int xPos, int yPos, int width, int height);
	void createDescriptionForControl(HWND parentOfControl, HWND controlWnd, LPTSTR description);
	void createGroupForImgWindow(HWND parent, UINT imgWndIdentifier, UINT btnIdentifier, UINT editIdentifier);
public:
	void destroyAuxiliaryWindow();
	void createCashInCashOutWindow(Client* currentClient, UINT btnIdentifier);
	void createAddNewClientWnd();
	AuxiliaryWindows();
	~AuxiliaryWindows();
};

LRESULT CALLBACK AuxiliaryWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);