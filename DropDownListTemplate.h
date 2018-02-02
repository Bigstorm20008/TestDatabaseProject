#pragma once

#include<Windows.h>

#include "Constatnts.h"

class DropDownListTemplate
{
public:
	DropDownListTemplate(HWND parent, int dropDownListXPos, int dropDownYPos, int dropDownListWidth, int dropDownListHeight, UINT dropDownListStyle);
	~DropDownListTemplate();
	
	void createDescriptionForDropDownList(TCHAR* descriptionText);
	void setFontForDropDownList(HFONT hFont);
	TCHAR* getSelectedItemFromDropDownList();
	void addNewItemToDropBox(TCHAR* item);
private:
	LONG_PTR m_oldDropDownListProc;
	static LRESULT CALLBACK DropDownListProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	UINT m_listIdentifier;
	void createDropDownList(HWND parent, int dropDownListXPos, int dropDownYPos, int dropDownListWidth, int dropDownListHeight, UINT dropDownListStyle);

protected:
	LRESULT RealDropDownListListProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	HWND m_DropDownListhWnd;
	HWND m_parentOfDropDownList;
	TCHAR* m_selectedTextInDropDownList;
};

