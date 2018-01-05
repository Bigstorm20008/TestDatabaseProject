#pragma once

#include "ControlPanel.h"
#include "Constants.h"
#include <tchar.h>
#include "ImageWnd.h"
#include "ListView.h"
#include "ExtPersonInfo.h"
#include "ButtonsForViews.h"
#include "AuxiliaryWindows.h"

class CInterfaceForRole
{
	HWND mainApplicationWnd;
	HWND clientArea;
	
	ImageWnd* pImageWnd;
	ListView* pListView;
	CExtPersonInfo* pExtentedInfoAboutSelectedPerson;
	CButtonsForViews* buttons;
	ControlPanel* pContolPanel;
	AuxiliaryWindows* auxiliaryWnd;
	Client* currentPerson;

	void hideAllWindow();
	static LRESULT CALLBACK ClientAreaProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
public:
	void setFocusOnListWindow();
	void activateCashInWindow();
	void showAllWindow();
	void activateClientView();
	void activateCashView();
	void activateEmployeesView();
	void loadInfoAboutSelectedPerson();
	void createInterfaceForRole(TCHAR* roleName);
	CInterfaceForRole();
	~CInterfaceForRole();
};

