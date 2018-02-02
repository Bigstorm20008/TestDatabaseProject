#pragma once
#include <Windows.h>
#include "Constatnts.h"

class ButtonTemplate
{
public:
	ButtonTemplate();
	~ButtonTemplate();

	void createButton(int xPos,
		                      int yPos,
		                      int buttonWidth,
		                      int buttonHeight,
		                      HWND parent,
		                      UINT buttonIdentifier,
		                      TCHAR* bitmapLocationForMouseMove,
		                      TCHAR* bitmapLocationForMouseLeave,
		                      TCHAR* bitmapLocationForDisabledButton);

	void loadBitmap(HBITMAP bitmap);
	void disableButton();
	void enableButton();
	void showButton();
	void destroyButton();
	HWND getButtonHwnd();

	
private:	
	HBITMAP m_hBitmap;
	TRACKMOUSEEVENT m_tme;
	LONG_PTR m_oldButtonProc;
	static LRESULT CALLBACK ButtonProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	HBITMAP m_BitmapForMouseLeave;
	HBITMAP m_BitmapForMouseMove;
	HBITMAP m_BitmapForButtonDisable;
	int m_buttonWidth;
	int m_buttonHeight;
	UINT m_btnIdentifier;
	
	
	
protected:
	LRESULT RealButtonProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	HWND m_hWnd;
};

