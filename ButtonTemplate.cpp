#include "ButtonTemplate.h"


ButtonTemplate::ButtonTemplate()
{
}


ButtonTemplate::~ButtonTemplate()
{
	destroyButton();
}
HWND ButtonTemplate::getButtonHwnd()
{
	return m_hWnd;
}

void ButtonTemplate::createButton(int xPos,
	int yPos,
	int buttonWidth,
	int buttonHeight,
	HWND parent,
	UINT buttonIdentifier,
	TCHAR* bitmapLocationForMouseMove,
	TCHAR* bitmapLocationForMouseLeave,
	TCHAR* bitmapLocationForDisabledButton)
{
	m_btnIdentifier = buttonIdentifier;
	m_buttonWidth = buttonWidth;
	m_buttonHeight = buttonHeight;
	m_hWnd = CreateWindow(TEXT("STATIC"),
		NULL,
		WS_CHILD | SS_NOTIFY | SS_BITMAP,
		xPos, yPos,
		buttonWidth, buttonHeight,
		parent,
		(HMENU)buttonIdentifier,
		(HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
		NULL);
	SetWindowLongPtr(m_hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
	m_oldButtonProc = (LONG_PTR)SetWindowLongPtr(m_hWnd, GWLP_WNDPROC, (LONG_PTR)(this->ButtonProc));
	//m_Bitmap = (HBITMAP)LoadImage(NULL, TEXT("D:\\Clients\\ClientButton(mouseleave).bmp"), IMAGE_BITMAP, buttonWidth, buttonHeight, LR_LOADFROMFILE);
	m_BitmapForButtonDisable = (HBITMAP)LoadImage(NULL, bitmapLocationForDisabledButton, IMAGE_BITMAP, buttonWidth, buttonHeight, LR_LOADFROMFILE);
	m_BitmapForMouseLeave = (HBITMAP)LoadImage(NULL, bitmapLocationForMouseLeave, IMAGE_BITMAP, buttonWidth, buttonHeight, LR_LOADFROMFILE);
	m_BitmapForMouseMove = (HBITMAP)LoadImage(NULL, bitmapLocationForMouseMove, IMAGE_BITMAP, buttonWidth, buttonHeight, LR_LOADFROMFILE);
	showButton();
}
void ButtonTemplate::loadBitmap(HBITMAP bitmap)
{
	SendMessage(m_hWnd, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)bitmap);
	UpdateWindow(m_hWnd);
}

void ButtonTemplate::disableButton()
{
	EnableWindow(m_hWnd, FALSE);
}
void ButtonTemplate::enableButton()
{
	EnableWindow(m_hWnd, TRUE);
}

void ButtonTemplate::showButton()
{
	ShowWindow(m_hWnd, SW_NORMAL);
}

void ButtonTemplate::destroyButton()
{
	DestroyWindow(m_hWnd);
}
LRESULT CALLBACK ButtonTemplate::ButtonProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ButtonTemplate* buttonTemplate = NULL;
	buttonTemplate = (ButtonTemplate*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	
	if (buttonTemplate != NULL)
	{
		return buttonTemplate->RealButtonProc(hWnd, msg, wParam, lParam);		
	}

	return 0;
}


LRESULT ButtonTemplate::RealButtonProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_SHOWWINDOW:
	{
		if (IsWindowEnabled(hWnd))
		{
			m_hBitmap = m_BitmapForMouseLeave;
			SendMessage(hWnd, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)m_hBitmap);
			//UpdateWindow(hWnd);
		}
		else
		{
			m_hBitmap = m_BitmapForButtonDisable;
			SendMessage(hWnd, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)m_hBitmap);
			//UpdateWindow(hWnd);
		}
		break;
	}
	
	case WM_MOUSEMOVE:
	{
		if (IsWindowEnabled(hWnd))
		{
			TrackMouseEvent(&m_tme);
			m_tme.cbSize = sizeof(m_tme);
			m_tme.dwFlags = TME_LEAVE;
			m_tme.dwHoverTime = HOVER_DEFAULT;
			m_tme.hwndTrack = hWnd;

			m_hBitmap = m_BitmapForMouseMove;
			SendMessage(hWnd, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)m_hBitmap);
			//UpdateWindow(hWnd);
		}
		else
		{
			m_hBitmap = m_BitmapForButtonDisable;
			SendMessage(hWnd, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)m_hBitmap);
			//UpdateWindow(hWnd);
		}
		break;
	}
	case WM_MOUSELEAVE:
	{
		if (IsWindowEnabled(hWnd))
		{
			m_hBitmap = m_BitmapForMouseLeave;
			SendMessage(hWnd, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)m_hBitmap);
			//UpdateWindow(hWnd);
		}
		else
		{
			m_hBitmap = m_BitmapForButtonDisable;
			SendMessage(hWnd, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)m_hBitmap);
			//UpdateWindow(hWnd);
		}
		break;
	}
	case WM_ENABLE:
	{
		if (IsWindowEnabled(hWnd))
		{
			m_hBitmap = m_BitmapForMouseLeave;
			SendMessage(hWnd, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)m_hBitmap);
			//UpdateWindow(hWnd);
		}
		else
		{
			m_hBitmap = m_BitmapForButtonDisable;
			SendMessage(hWnd, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)m_hBitmap);
			//UpdateWindow(hWnd);
		}
		break;
	}
	case WM_PAINT:
	{
		PAINTSTRUCT     ps;
		HDC             hdc;
		BITMAP          bitmap;
		HDC             hdcMem;
		HGDIOBJ         oldBitmap;

		hdc = BeginPaint(m_hWnd, &ps);
		hdcMem = CreateCompatibleDC(hdc);
		oldBitmap = SelectObject(hdcMem, m_hBitmap);
		GetObject(m_hBitmap, sizeof(bitmap), &bitmap);
		BitBlt(hdc, 0, 0, m_buttonWidth, m_buttonHeight, hdcMem, 0, 0, SRCCOPY);
		SelectObject(hdcMem, oldBitmap);
		DeleteDC(hdcMem);
		EndPaint(m_hWnd, &ps);
		break;
	}
		default:
		{
			return CallWindowProc((WNDPROC)m_oldButtonProc, m_hWnd, msg, wParam, lParam);
		}

	}
	return 0;
}
