#include "AuxiliaryWindowTemplate.h"


AuxiliaryWindowTemplate::AuxiliaryWindowTemplate(HWND windowToDisable, HWND parent, int auxiliaryWidth, int auxiliaryHeight, TCHAR* captionText)
{
	createModalAuxiliaryWindow(windowToDisable, parent, auxiliaryWidth, auxiliaryHeight, captionText);
}


AuxiliaryWindowTemplate::~AuxiliaryWindowTemplate()
{
	DestroyWindow(m_auxiliaryWnd);
}

void AuxiliaryWindowTemplate::createModalAuxiliaryWindow(HWND windowToDisable, HWND parent, int auxiliaryWidth, int auxiliaryHeight, TCHAR* captionText)
{
	m_WndToDisable = windowToDisable;
	m_auxiliaryParent = parent;
	HWND desktop = GetDesktopWindow();
	RECT desktopRC;
	GetClientRect(desktop, &desktopRC);
	int xPos = desktopRC.right / 2 - auxiliaryWidth / 2;
	int yPos = desktopRC.bottom / 2 - auxiliaryHeight / 2;

	WNDCLASSEX wc;
	wc.cbClsExtra = wc.cbWndExtra = 0;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = NULL;
	wc.hIconSm = NULL;
	wc.hInstance = (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE);
	wc.lpfnWndProc = AuxiliaryWindowTemplate::AuxiliaryProc;
	wc.lpszClassName = TEXT("AuxiliaryWindow");
	wc.lpszMenuName = NULL;
	wc.style = 0;

	RegisterClassEx(&wc);

	m_auxiliaryWnd = CreateWindow(wc.lpszClassName,
		                          NULL,
		                          WS_POPUP | WS_VISIBLE | WS_BORDER | WS_OVERLAPPED,
		                          xPos, yPos,
		                          auxiliaryWidth, auxiliaryHeight,
		                          parent,
		                          NULL,
		                          (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
		                          this);

	m_captionWnd = CreateWindow(TEXT("STATIC"),
		                        captionText,
		                        WS_CHILD | WS_VISIBLE | SS_CENTER,
		                        0, 0,
		                        auxiliaryWidth, windowCaptionHeight,
		                        m_auxiliaryWnd,
		                        (HMENU)ID_AUXILIARY_CAPTION,
		                        (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
		                        NULL);

	EnableWindow(m_WndToDisable, FALSE);

	/*CreateWindow(TEXT("BUTTON"),
		TEXT("BUTTON"),
		WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
		10, windowCaptionHeight + offsetsBetweenWindow,
		200, 25,
		m_auxiliaryWnd,
		(HMENU)ID_CANCEL_AUXILIARY_BTN,
		(HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
		NULL);*/
}


LRESULT CALLBACK AuxiliaryWindowTemplate::AuxiliaryProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	
	switch (msg)
	{
		case WM_CREATE:
		{
			LPCREATESTRUCT lpcs;
			lpcs = (LPCREATESTRUCT)lParam;
			SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)lpcs->lpCreateParams);
			return 0;
		}
		case WM_CTLCOLORSTATIC:
		{
			HWND captionWnd = GetDlgItem(hWnd, ID_AUXILIARY_CAPTION);
			if ((HWND)lParam == captionWnd)
			{
				HDC hdcStatic = (HDC)wParam;
				HFONT hFont = CreateFont(16, 0, 0, 0, 0, 0, 0, 0,
					DEFAULT_CHARSET,
					0, 0, 0, VARIABLE_PITCH,
					L"Time New Romans");
				SelectObject(hdcStatic, hFont);
				SetBkMode(hdcStatic, TRANSPARENT);
				return (INT_PTR)CreateSolidBrush(RGB(217, 236, 249));
			}
			else
			{
				AuxiliaryWindowTemplate* auxiliaryTemplate = NULL;
				auxiliaryTemplate = (AuxiliaryWindowTemplate*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

				if (auxiliaryTemplate != NULL)
				{
					return auxiliaryTemplate->RealAuxiliaryProc(hWnd, msg, wParam, lParam);
				}
				else
				{
					return DefWindowProc(hWnd, msg, wParam, lParam);
				}
			}
			break;
		}
		default:
		{
			AuxiliaryWindowTemplate* auxiliaryTemplate = NULL;
			auxiliaryTemplate = (AuxiliaryWindowTemplate*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

			if (auxiliaryTemplate != NULL)
			{
				return auxiliaryTemplate->RealAuxiliaryProc(hWnd, msg, wParam, lParam);
			}
			else
			{
				return DefWindowProc(hWnd, msg, wParam, lParam);
			}
		}
			
	}	
}
	

LRESULT AuxiliaryWindowTemplate::RealAuxiliaryProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{	
		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
				case ID_CANCEL_AUXILIARY_BTN:
				{
					SendMessage(hWnd, WM_DESTROY, 0, 0);
					break;
				}
			}
			break;
		}
		case WM_DESTROY:
		{
			EnableWindow(m_WndToDisable, TRUE);
			DestroyWindow(hWnd);
			
			break;
		}
			
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
