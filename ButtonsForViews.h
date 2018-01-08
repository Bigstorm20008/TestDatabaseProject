#pragma once
#include <Windows.h>
#include "Constants.h"
class CButtonsForViews
{
private:
	HWND parentWindow;
	HWND parentForButtons;

	//CashView buttons
	HWND cashInButton;
	HWND cashOutButton;
	HWND clientOutButton;
	HWND incomingBtn;
	HWND clientInButton;

	//ClientView buttons
	HWND addClientButton;
	void createCaptionForGroupButton(int yPos, TCHAR* caption);
	void createParentWindowForButtons(HWND listWnd);
	
	SYSTEMTIME dateTime;
	void getCurrentDate();
	
public:
	CButtonsForViews(HWND parent, UINT listWndIdentifier);
	~CButtonsForViews();

	void createCashViewButtons();
	void createClientViewButtons();
	void createEmployeesViewButtons();

	void enableButtonsIfPersonSelected();
	void disableButtonsIfNoSelected();
};

static WNDPROC oldParentForButtonsProc;
LRESULT CALLBACK ParentForButtonsProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);