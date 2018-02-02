#include "EditControlTemplate.h"


EditControlTemplate::EditControlTemplate()
{
	m_textInEdit = nullptr;
}


EditControlTemplate::~EditControlTemplate()
{
	DestroyWindow(m_EdithWnd);
	if (m_textInEdit)
	{
		delete[]m_textInEdit;
		m_textInEdit = nullptr;
	}
}

void EditControlTemplate::createEditControl(HWND parent, int editXPos, int editYPos, int editWidth, int editHeight, UINT editStyle)
{
	m_parentOfEdit = parent;
	m_EdithWnd = CreateWindow(TEXT("EDIT"),
		                      NULL,
							  editStyle,
							  editXPos,editYPos,
							  editWidth,editHeight,
							  parent,
							  NULL,
							  (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
							  NULL);
	SetWindowLongPtr(m_EdithWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
	m_oldEditProc = (LONG_PTR)SetWindowLongPtr(m_EdithWnd, GWLP_WNDPROC, (LONG_PTR)(this->EditProc));
}

void EditControlTemplate::createDescriptionForEdit(TCHAR* descriptionText)
{
	RECT controlRc;
	GetWindowRect(m_EdithWnd, &controlRc);
	POINT tmp;
	tmp.x = controlRc.left;
	tmp.y = controlRc.top;
	ScreenToClient(m_parentOfEdit, &tmp);
	int desc_width = controlRc.right - controlRc.left;
	int desc_height = descriptionForControlHeight;
	int desc_xPos = tmp.x;
	int desc_yPos = tmp.y - desc_height;

	HWND descWnd = CreateWindow(TEXT("STATIC"),
		descriptionText,
		WS_CHILD | WS_VISIBLE | SS_LEFT | SS_EDITCONTROL,
		desc_xPos, desc_yPos,
		desc_width, desc_height,
		m_parentOfEdit,
		NULL,
		(HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
		NULL);
}

void EditControlTemplate::setNewTextForEdit(TCHAR* newText)
{
	SendMessage(m_EdithWnd, EM_SETMODIFY, (WPARAM)FALSE, 0);
	SetWindowText(m_EdithWnd, newText);
	SendMessage(m_EdithWnd, EM_SETMODIFY, (WPARAM)TRUE, 0);
}

void EditControlTemplate::setFontForEdit(HFONT hFont)
{
	SendMessage(m_EdithWnd, WM_SETFONT, (WPARAM)hFont, (LPARAM)TRUE);
}

HWND EditControlTemplate::getEditHandle() const
{
	return m_EdithWnd;
}

TCHAR* EditControlTemplate::getTextFromEdit()
{
	if (m_textInEdit)
	{
		delete[]m_textInEdit;
		m_textInEdit = nullptr;
	}

	size_t textLen = GetWindowTextLength(m_EdithWnd);
	m_textInEdit = new TCHAR[textLen + 1];
	memset(m_textInEdit, 0, (textLen + 1)*sizeof(TCHAR));
	GetWindowText(m_EdithWnd, m_textInEdit, textLen + 1);
	return m_textInEdit;
}

void EditControlTemplate::setFocusOnEdit()
{
	SetFocus(m_EdithWnd);
}

LRESULT CALLBACK EditControlTemplate::EditProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	EditControlTemplate* editTemplate = NULL;
	editTemplate = (EditControlTemplate*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

	if (editTemplate != NULL)
	{
		return editTemplate->RealEditProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}

LRESULT EditControlTemplate::RealEditProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		default:
		{
			return CallWindowProc((WNDPROC)m_oldEditProc, m_EdithWnd, msg, wParam, lParam);
		}
	}
	//return 0;
}
