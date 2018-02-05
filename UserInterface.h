#pragma once

#include "SqlFramework.h"
#include "AutentificationForm.h"
#include "AutorisationClass.h"
#include "AddClientToDatabaseForm.h"
#include "CashInCashOutForm.h"
#include "ChangeCurrencyRateForm.h"
#include "ControlPanel.h"
#include "ApplicationViews.h"
#include "ControlsForViews.h"
#include "CasinoState.h"

class UserInterface
{
public:
	UserInterface(HWND mainApplicationWindow);
	~UserInterface();
	void activateAutentificationWindow();
	void autorisationInDatabase();
	
	void activateCashView();
	void activateClientsView();
	void activateEmployeesView();

	void activateChangeCurrencyRateForm(UINT pressedBtnIdentifier);
	void activateCashInCashOutForm(UINT pressedBtnIdentifier);
	void changeClientState(UINT exitOrEntranceBtnIdentifier);
	void freeForm(UINT pressedBtnIdentifier);

	void processClickMessage(HWND hwndFrom);
private:
	HWND m_mainApplicationWindow;
	TCHAR* m_dateInCasino;
	CasinoState* m_casinoState;

	CSqlFramework* m_sqlConection;
	AutentificationForm* m_autentification;
	ControlPanel* m_controlPanel;
	ApplicationViews* m_views;
	ControlsForViews* m_controls;

	
	ChangeCurrencyRateForm* m_changeCurrencyRateForm;
	CashInCashOutForm* m_cashInCashOutForm;
	AddClientToDatabaseForm* m_addClientToDatabaseForm;

	void createUserInterfaceForRole(TCHAR* roleName);
	void createControlsAreaForViews();
};

