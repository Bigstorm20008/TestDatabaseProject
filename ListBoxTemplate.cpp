#include "ListBoxTemplate.h"


ListBoxTemplate::ListBoxTemplate(int xPos, int yPos, int listWidth, int listHeight, UINT listStyle, HWND parentOfList)
{
	m_listWnd = CreateWindow(TEXT("LISTBOX"),
		                     NULL,
		                     listStyle,
		                     xPos, yPos,
		                     listWidth, listHeight,
		                     parentOfList,
		                     (HMENU)NULL,
		                     (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
		                     NULL);
}


ListBoxTemplate::~ListBoxTemplate()
{
}

