#pragma once

#include <tchar.h>

#include "ButtonTemplate.h"
class ControlPanel
{
public:
	ControlPanel(HWND parentOfControlPanel, TCHAR* roleName, BOOL casinoState);
	~ControlPanel();
	

private:
	BOOL m_casinoState;
	HWND m_parentOfControlPanel;
	HWND m_controlPanelWnd;
	ButtonTemplate* m_CashDeskButton;
	ButtonTemplate* m_ClentsButton;
	ButtonTemplate* m_EmployeesButton;

	void createControlPanel();
	void createButtonsForRole(TCHAR* roleName);
	void createButtonsForCashier();
	void createButtonsForManager();
	void createButtonsForBarmen();
	void createButtonsForVideoMan();
	void createButtonsForPitBoss();

	void createCashDeskButton(int& xPos, int& yPos);
	void createClientsButton(int& xPos, int& yPos);
	void createEmployeesButton(int& xPos, int& yPos);

	void disableButtonOnControlPanel(UINT butonIdentifier);

	static LRESULT CALLBACK ControlPanelProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT RealControlPanelProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

