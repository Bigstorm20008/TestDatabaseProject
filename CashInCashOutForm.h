#pragma once

#include "AuxiliaryWindowTemplate.h"
#include "ImageTemplate.h"
#include "Person.h"
#include "Client.h"
#include "EditControlTemplate.h"

class CashInCashOutForm :
	public AuxiliaryWindowTemplate
{
public:
	CashInCashOutForm(HWND windowToDisable, HWND parentForWindow, UINT pressedBtnIdentifier, Person* selectedPerson, CSqlFramework* sqlConnection, TCHAR* dateInCasino);
	~CashInCashOutForm();
private:
	CSqlFramework* m_sqlConnection;
	TCHAR* m_dateInCasino;
	UINT m_pressedBtnIdentifier;
	Person* m_selectedPerson;
	ImageTemplate* m_clientPhoto;
	EditControlTemplate* m_editForEnterValueOfCashInCashOut;
	virtual void createControlsForWindow();
	BOOL checkData(UINT pressedBtnIdentifier);
	void saveCashInCashOutInDatabase(UINT pressedBtnIdentifier, TCHAR* value);
	virtual LRESULT RealAuxiliaryProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

