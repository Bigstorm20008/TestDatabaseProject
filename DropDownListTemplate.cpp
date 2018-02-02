#include "DropDownListTemplate.h"


DropDownListTemplate::DropDownListTemplate(HWND parent, int dropDownListXPos, int dropDownYPos, int dropDownListWidth, int dropDownListHeight, UINT dropDownListStyle)
{
	m_selectedTextInDropDownList = nullptr;
	createDropDownList(parent, dropDownListXPos, dropDownYPos, dropDownListWidth, dropDownListHeight, dropDownListStyle);
	
}


DropDownListTemplate::~DropDownListTemplate()
{
	if (m_selectedTextInDropDownList)
	{
		delete m_selectedTextInDropDownList;
		m_selectedTextInDropDownList = nullptr;
	}
	DestroyWindow(m_DropDownListhWnd);
}

void DropDownListTemplate::createDescriptionForDropDownList(TCHAR* descriptionText)
{
	RECT controlRc;
	GetWindowRect(m_DropDownListhWnd, &controlRc);
	POINT tmp;
	tmp.x = controlRc.left;
	tmp.y = controlRc.top;
	ScreenToClient(m_parentOfDropDownList, &tmp);
	int desc_width = controlRc.right - controlRc.left;
	int desc_height = descriptionForControlHeight;
	int desc_xPos = tmp.x;
	int desc_yPos = tmp.y - desc_height;

	HWND descWnd = CreateWindow(TEXT("STATIC"),
		                        descriptionText,
		                        WS_CHILD | WS_VISIBLE | SS_LEFT | SS_EDITCONTROL,
		                        desc_xPos, desc_yPos,
		                        desc_width, desc_height,
		                        m_parentOfDropDownList,
		                        NULL,
		                        (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
		                        NULL);
}

void DropDownListTemplate::createDropDownList(HWND parent, int dropDownListXPos, int dropDownYPos, int dropDownListWidth, int dropDownListHeight, UINT dropDownListStyle)
{
	m_parentOfDropDownList = parent;
	m_DropDownListhWnd =  CreateWindow(TEXT("COMBOBOX"),
		                               TEXT(""),
									   dropDownListStyle,
									   dropDownListXPos, dropDownYPos,
									   dropDownListWidth, dropDownListHeight,
		                               parent,
		                               (HMENU)NULL,
		                               (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
		                               NULL);
	SetWindowLongPtr(m_DropDownListhWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
	m_oldDropDownListProc = (LONG_PTR)SetWindowLongPtr(m_DropDownListhWnd, GWLP_WNDPROC, (LONG_PTR)(this->DropDownListProc));
}

TCHAR* DropDownListTemplate::getSelectedItemFromDropDownList()
{
	COMBOBOXINFO info = { sizeof(COMBOBOXINFO) };
	GetComboBoxInfo(m_DropDownListhWnd, &info);
	HWND edit = info.hwndItem;
	size_t textLen = GetWindowTextLength(edit);
	if (m_selectedTextInDropDownList)
	{
		delete m_selectedTextInDropDownList;
		m_selectedTextInDropDownList = nullptr;
	}
	m_selectedTextInDropDownList = new TCHAR[textLen + 1];
	GetWindowText(edit, m_selectedTextInDropDownList, textLen + 1);
	return m_selectedTextInDropDownList;
}


void DropDownListTemplate::addNewItemToDropBox(TCHAR* item)
{
	SendMessage(m_DropDownListhWnd, CB_ADDSTRING, 0, (LPARAM)item);
}
LRESULT CALLBACK DropDownListTemplate::DropDownListProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	DropDownListTemplate* dropDownListTemplate = NULL;
	dropDownListTemplate = (DropDownListTemplate*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

	if (dropDownListTemplate != NULL)
	{
		return dropDownListTemplate->RealDropDownListListProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}

LRESULT DropDownListTemplate::RealDropDownListListProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		default:
		{
			return CallWindowProc((WNDPROC)m_oldDropDownListProc, m_DropDownListhWnd, msg, wParam, lParam);
		}
	}
}

