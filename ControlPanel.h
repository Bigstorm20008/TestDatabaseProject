#pragma once

#include <Windows.h>
#include "MyButton.h"
#include "MyUserInterface.h"
#include "ClientView.h"



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