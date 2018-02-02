#pragma once

#include <Windows.h>

class ListBoxTemplate
{
public:
	ListBoxTemplate(int xPos,int yPos,int listWidth,int listHeight,UINT listStyle,HWND parentOfList);
	~ListBoxTemplate();
private:
	HWND m_listWnd;
};

