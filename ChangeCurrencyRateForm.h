#pragma once
#include "AuxiliaryWindowTemplate.h"
#include "EditControlTemplate.h"
#include "SqlFramework.h"
#include "CurrencyOperation.h"

class ChangeCurrencyRateForm : public AuxiliaryWindowTemplate
{
public:

	ChangeCurrencyRateForm(HWND windowToDisable, HWND parent, HWND windowWithInfoAboutRate,UINT btnIdentifer, CSqlFramework* sqlConnection);
	~ChangeCurrencyRateForm();

private:
	CSqlFramework* m_sqlConnection;
	UINT m_pressedBtnIdentifier;
	HWND m_windowWithInfoAboutRate;

	TCHAR* m_captionForWindow;
	TCHAR* m_descriptionForEdit;
	EditControlTemplate* m_editForNewCurrencyRate;

	BOOL changeCurrencyRate();

	virtual void createControlsForWindow();
	virtual LRESULT RealAuxiliaryProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

