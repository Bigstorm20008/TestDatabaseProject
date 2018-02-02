#pragma once

#include <Windows.h>
#include "Constatnts.h"
#include "SqlFramework.h"
#include "CurrencyOperation.h"

class ControlsForViews
{
public:
	ControlsForViews(HWND parentForControls, int xPos, int yPos, int width, int height,CSqlFramework* sqlConnection);
	~ControlsForViews();
	void createControlsForCashView();
	void createControlsForClientsView();
	void createControlsForEmployeesView();
	void enableButtonsIfSelectedPerson();
	void disableButtonsIfNoSelectedPerson();
	HWND getInfoWindowForRate(UINT pressedBtnIdentifier);
private:
	HWND m_parentOfControl;
	HWND m_parentOfParentOfControl;
	CSqlFramework* m_sqlConnection;

	HWND m_cashInButton;
	HWND m_cashOutButton;
	HWND m_exitFromCasinoButton;
	HWND m_dollarRate;
	HWND m_euroRate;

	HWND m_entranceToCasinoButton;

	LONG_PTR m_oldParentForButtonProc;
	static LRESULT CALLBACK ParentForButtonProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT RealParentForButtonProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	void destroyAllControls();
	void createCaptionForGroupButton(int yPos, TCHAR* captionForGroup);
	HWND createInfoWindowAboutRate(int xPos, int yPos, int width, int height, TCHAR* currencyName, UINT identifierForChangeRateBtn);
};

