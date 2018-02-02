#pragma once

#include "AuxiliaryWindowTemplate.h"
#include "EditControlTemplate.h"
#include "SqlFramework.h"

#include "Constatnts.h"

class AutentificationForm :
	public AuxiliaryWindowTemplate
{
public:
	AutentificationForm(HWND windowToDisable, HWND parent, CSqlFramework* sqlConnection);
	~AutentificationForm();
private:
	EditControlTemplate* m_UserName;
	EditControlTemplate* m_Password;
	CSqlFramework* m_sqlConnection;
	BOOL connectToDatabase();
	virtual void createControlsForWindow();
	virtual LRESULT RealAuxiliaryProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

