#pragma once

#include <Windows.h>
#include "Constants.h"

#define btnBitmapWidth 100
#define btnBitmapHeight 40

#define ID_STATIC_CASH_BTN   1010
#define ID_STATIC_CLIENT_BTN 1011
#define ID_STATIC_DILER_BTN  1012

class ControlPanel
{
private:
	UINT controlPanelIdentifier;
	HWND mainWindow;
	HWND controlPanelWnd;
	HWND cashButton;
	HWND clientButton;
	HWND employButton;
	void createClientButton();
	void createCashButton();
	void createEmployeesButton();
	void loadBitmapForBtn(HWND button, LPTSTR bitmapLocation);
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	
public:
	void hideControlPanel();
	void showControlPanel();
	void createButtonForCashDesk();
	void disableButton(UINT btnIdentifier);
	ControlPanel();
	void CreateControlPanel(HWND hWnd, UINT identify, int controlPanelHeight);
	void MoveMyWindow(HWND hWnd);
	~ControlPanel();
	
};


static WNDPROC oldClientBtnProc;
LRESULT CALLBACK ClientBtnProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);

static WNDPROC oldCashBtnProc;
LRESULT CALLBACK CashBtnProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);

static WNDPROC oldEmployBtnProc;
LRESULT CALLBACK EmployBtnProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);


