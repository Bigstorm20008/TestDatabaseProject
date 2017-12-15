#pragma once

#include <Windows.h>
#include "MyButton.h"


#define ID_CASH_BTN 1010
#define ID_CLIENT_BTN 1011
#define ID_DILER_BTN 1012

class ControlPanel
{
private:
	UINT identifyNum;
public:
	ControlPanel();
	void CreateControlPanel(HWND hWnd, UINT identify);
	void MoveMyWindow(HWND hWnd);
	~ControlPanel();
};

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);