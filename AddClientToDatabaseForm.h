#pragma once


#include "AuxiliaryWindowTemplate.h"
#include "ButtonTemplate.h"
#include "EditControlTemplate.h"
#include "DropDownListTemplate.h"
#include "ImageTemplate.h"
#include "SqlFramework.h"


class AddClientToDatabaseForm :
	public AuxiliaryWindowTemplate
{
public:	
	AddClientToDatabaseForm(HWND windowToDisable, HWND parent, TCHAR* captionText);
	~AddClientToDatabaseForm();

private:
	ButtonTemplate* m_addClientToDatabaseBtn;
	ButtonTemplate* m_cancelBtn;
	EditControlTemplate* m_nicknameEdit;
	EditControlTemplate* m_lastnameEdit;
	EditControlTemplate* m_firstnameEdit;
	EditControlTemplate* m_patronymicEdit;
	DropDownListTemplate* m_clientStatus;
	ImageTemplate* m_windowForClientImage;
	EditControlTemplate* m_editForAddPhoneNumber;
	EditControlTemplate* m_additionalInfoAboutClient;
	HWND m_listForPhoneNumbers;
	void createGroupForAddPhoneNumbers(int xPos, int yPos, int editWidth, int editHeight, UINT editStyle);
	void saveNewClientInDatabase();
	void openExplorerForImageSelect();
	void addPhoneNumberToList();
	void removePhoneNumberFromList();
	virtual void createControlsForWindow();
	BOOL checkData();
	virtual LRESULT RealAuxiliaryProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

