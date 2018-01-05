#include "ControlPanel.h"


ControlPanel::ControlPanel()
{
	WNDCLASSEX wcex;
	wcex.cbClsExtra = wcex.cbWndExtra = NULL;
	wcex.cbSize = sizeof(WNDCLASSEX);                                       //������ ���������
	wcex.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));  //��� ����
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);                             //��������� ��� ��������� ����
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);                           //��������� ����������� ������ ����������
	wcex.hIconSm = NULL;                                                    //����������� ������ �� ������
	wcex.hInstance = (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE);        //�������� ���������� ������ ����������
	wcex.lpfnWndProc = WndProc;                                             //��������� ������� ��� ��������� ��������� � ������� ����
	wcex.lpszClassName = L"ControlPanelWindow";                             //��� ������ ������ ����
	wcex.lpszMenuName = NULL;                                               //���� �����������
	wcex.style = CS_HREDRAW | CS_VREDRAW;                                   //��������� ����� ����������� ����(����������� �� �������� � �����������)

	RegisterClassEx(&wcex);
	
}


ControlPanel::~ControlPanel()
{
}

void ControlPanel::hideControlPanel()
{
  ShowWindow(controlPanelWnd, FALSE);
}

void ControlPanel::showControlPanel()
{
	ShowWindow(controlPanelWnd, TRUE);
}

void ControlPanel::CreateControlPanel(HWND hWnd, UINT identify,int controlPanelHeight)
{
	controlPanelIdentifier = identify;
	mainWindow = hWnd;
	RECT rc;
	GetClientRect(hWnd, &rc);
	int xPos = rc.left;
	int yPos = rc.top;
	int width = rc.right - rc.left;
	int height = controlPanelHeight;
	controlPanelWnd = CreateWindow(L"ControlPanelWindow",
		                          L"",
		                          WS_CHILD | WS_VISIBLE,
		                          xPos,
		                          yPos,
		                          width,
		                          height,
								  mainWindow,
		                          HMENU(identify),
		                          (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
		                          NULL);
}

void ControlPanel::MoveMyWindow(HWND hWnd)
{
	RECT mainRc;
	GetClientRect(hWnd, &mainRc);
	HWND chWnd = GetDlgItem(hWnd, controlPanelIdentifier);
	MoveWindow(chWnd, 0, 0, mainRc.right, 50, TRUE);
}

void ControlPanel::createClientButton()
{
	clientButton = CreateWindow(TEXT("STATIC"),
		                                NULL,
								        WS_CHILD | WS_VISIBLE | SS_BITMAP | SS_NOTIFY ,//| WS_BORDER,
		                                110,
		                                5,
								        btnBitmapWidth,
								        btnBitmapHeight,
		                                controlPanelWnd,
		                                (HMENU)ID_STATIC_CLIENT_BTN,
		                                (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
		                                NULL);
	extern WNDPROC oldClientBtnProc;
	oldClientBtnProc = (WNDPROC)SetWindowLong(clientButton, GWL_WNDPROC, (LONG)ClientBtnProc);
}

void ControlPanel::createCashButton()
{
	cashButton = CreateWindow(TEXT("STATIC"),
		NULL,
		WS_CHILD | WS_VISIBLE | SS_BITMAP | SS_NOTIFY,// | WS_BORDER,
		5,
		5,
		btnBitmapWidth,
		btnBitmapHeight,
		controlPanelWnd,
		(HMENU)ID_STATIC_CASH_BTN,
		(HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
		NULL);
	extern WNDPROC oldCashBtnProc;
	oldCashBtnProc = (WNDPROC)SetWindowLong(cashButton, GWL_WNDPROC, (LONG)CashBtnProc);
}

void ControlPanel::createEmployeesButton()
{
	employButton = CreateWindow(TEXT("STATIC"),
		NULL,
		WS_CHILD | WS_VISIBLE | SS_BITMAP | SS_NOTIFY,// | WS_BORDER,
		215,
		5,
		btnBitmapWidth,
		btnBitmapHeight,
		controlPanelWnd,
		(HMENU)ID_STATIC_DILER_BTN,
		(HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
		NULL);
	extern WNDPROC oldEmployBtnProc;
	oldEmployBtnProc = (WNDPROC)SetWindowLong(employButton, GWL_WNDPROC, (LONG)EmployBtnProc);

}

void ControlPanel::createButtonForCashDesk()
{
	createCashButton();
	createClientButton();
	createEmployeesButton();
}

void ControlPanel::disableButton(UINT btnIdentifier)
{
	switch (btnIdentifier)
	{
		case ID_STATIC_CASH_BTN:
		{
			EnableWindow(cashButton, FALSE);
			EnableWindow(clientButton, TRUE);
			EnableWindow(employButton, TRUE);
			break;
		}
		case ID_STATIC_CLIENT_BTN:
		{
			EnableWindow(cashButton, TRUE);
			EnableWindow(clientButton, FALSE);
			EnableWindow(employButton, TRUE);
			break;
		}
		case ID_STATIC_DILER_BTN:
		{
			EnableWindow(cashButton, TRUE);
			EnableWindow(clientButton, TRUE);
			EnableWindow(employButton, FALSE);
			break;
		}
		default:
		{
			break;
		}
	}
}

void ControlPanel::loadBitmapForBtn(HWND button, LPTSTR bitmapLocation)
{
	HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, bitmapLocation, IMAGE_BITMAP, btnBitmapWidth, btnBitmapHeight, LR_LOADFROMFILE);
	SendMessage(button, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);
	UpdateWindow(button);
}


LRESULT CALLBACK ControlPanel::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	extern LPTSTR szClassName;
	extern LPTSTR szWindowName;
	HWND mainWnd = FindWindow(szClassName, szWindowName);
	HWND clientAreaForInterfaceElement = GetDlgItem(mainWnd, ID_CLIENT_AREA);
	switch (msg)
	{
	case WM_CREATE:
	{			
		break;
	}
	
	case WM_COMMAND:
	{
		switch (wParam)
		{
		case ID_STATIC_CASH_BTN:
		{	
			SendMessage(mainWnd, WM_COMMAND, ID_STATIC_CASH_BTN, 0);
			break;
		}
		case ID_STATIC_CLIENT_BTN:
		{	
			SendMessage(mainWnd, WM_COMMAND, ID_STATIC_CLIENT_BTN, 0);
			break;
		}
		case ID_STATIC_DILER_BTN:
		{
			SendMessage(mainWnd, WM_COMMAND, ID_STATIC_DILER_BTN, 0);
			break;
		}
			return 0;
		}
		break;
	}
	// ������� �� ��������� � ����������� ������ ���������
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
		//��������� ���� ��������� ��������� ������������ �� �� ���������
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam); //������ ������ ������� ���������, �������� ��� � ����� �����������
	}
	return 0;
}

LRESULT CALLBACK ClientBtnProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	static TRACKMOUSEEVENT tme;
	static HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, TEXT("D:\\Clients\\ClientButton(mouseleave).bmp"), IMAGE_BITMAP, btnBitmapWidth, btnBitmapHeight, LR_LOADFROMFILE);
	//����� ��� ��������� ������ �� Static
	//� ����� ������ ������������ ������ proc ��� static
	switch (msg)
	{
		case WM_MOUSEMOVE:
		{
			if (IsWindowEnabled(hWnd))
			{
				TrackMouseEvent(&tme);
				tme.cbSize = sizeof(tme);
				tme.dwFlags = TME_LEAVE;
				tme.dwHoverTime = HOVER_DEFAULT;
				tme.hwndTrack = hWnd;

				hBitmap = (HBITMAP)LoadImage(NULL, TEXT("D:\\Clients\\ClientButton(mousemove).bmp"), IMAGE_BITMAP, btnBitmapWidth, btnBitmapHeight, LR_LOADFROMFILE);
				SendMessage(hWnd, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);
				UpdateWindow(hWnd);
			}
			else
			{
				hBitmap = (HBITMAP)LoadImage(NULL, TEXT("D:\\Clients\\ClientButton(disable).bmp"), IMAGE_BITMAP, btnBitmapWidth, btnBitmapHeight, LR_LOADFROMFILE);
				SendMessage(hWnd, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);
				UpdateWindow(hWnd);
			}
			break;
		}
		case WM_MOUSELEAVE:
		{
			
			if (IsWindowEnabled(hWnd))
			{
				hBitmap = (HBITMAP)LoadImage(NULL, TEXT("D:\\Clients\\ClientButton(mouseleave).bmp"), IMAGE_BITMAP, btnBitmapWidth, btnBitmapHeight, LR_LOADFROMFILE);
				SendMessage(hWnd, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);
				UpdateWindow(hWnd);
			}
			else
			{
				hBitmap = (HBITMAP)LoadImage(NULL, TEXT("D:\\Clients\\ClientButton(disable).bmp"), IMAGE_BITMAP, btnBitmapWidth, btnBitmapHeight, LR_LOADFROMFILE);
				SendMessage(hWnd, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);
				UpdateWindow(hWnd);
			}
			break;
		}
		case WM_ENABLE:
		{
			switch (wp)
			{
				case TRUE:
				{
					hBitmap = (HBITMAP)LoadImage(NULL, TEXT("D:\\Clients\\ClientButton(mouseleave).bmp"), IMAGE_BITMAP, btnBitmapWidth, btnBitmapHeight, LR_LOADFROMFILE);
					SendMessage(hWnd, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);
					UpdateWindow(hWnd);
					break;
				}
				case FALSE:
				{
					hBitmap = (HBITMAP)LoadImage(NULL, TEXT("D:\\Clients\\ClientButton(disable).bmp"), IMAGE_BITMAP, btnBitmapWidth, btnBitmapHeight, LR_LOADFROMFILE);
					SendMessage(hWnd, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);
					UpdateWindow(hWnd);
					break;
				}
				default:
				{
					break;
				}
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

				hdc = BeginPaint(hWnd, &ps);
				hdcMem = CreateCompatibleDC(hdc);
				oldBitmap = SelectObject(hdcMem, hBitmap);
				GetObject(hBitmap, sizeof(bitmap), &bitmap);
				BitBlt(hdc, 0, 0, btnBitmapWidth, btnBitmapHeight, hdcMem, 0, 0, SRCCOPY);
				SelectObject(hdcMem, oldBitmap);
				DeleteDC(hdcMem);
				EndPaint(hWnd, &ps);		
			break;
		}
		default:
		{
			break;
		}
			
	}
	extern WNDPROC oldClientBtnProc;
	return CallWindowProc(oldClientBtnProc, hWnd, msg, wp, lp);
}

LRESULT CALLBACK CashBtnProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	static TRACKMOUSEEVENT tme;
	static HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, TEXT("D:\\Clients\\CashButton(mouseleave).bmp"), IMAGE_BITMAP, btnBitmapWidth, btnBitmapHeight, LR_LOADFROMFILE);
	//����� ��� ��������� ������ �� Static
	//� ����� ������ ������������ ������ proc ��� static
	switch (msg)
	{
	case WM_MOUSEMOVE:
	{
		if (IsWindowEnabled(hWnd))
		{
			TrackMouseEvent(&tme);
			tme.cbSize = sizeof(tme);
			tme.dwFlags = TME_LEAVE;
			tme.dwHoverTime = HOVER_DEFAULT;
			tme.hwndTrack = hWnd;

			hBitmap = (HBITMAP)LoadImage(NULL, TEXT("D:\\Clients\\CashButton(mousemove).bmp"), IMAGE_BITMAP, btnBitmapWidth, btnBitmapHeight, LR_LOADFROMFILE);
			SendMessage(hWnd, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);
			UpdateWindow(hWnd);
		}
		else
		{
			hBitmap = (HBITMAP)LoadImage(NULL, TEXT("D:\\Clients\\CashButton(disable).bmp"), IMAGE_BITMAP, btnBitmapWidth, btnBitmapHeight, LR_LOADFROMFILE);
			SendMessage(hWnd, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);
			UpdateWindow(hWnd);
		}
		break;
	}
	case WM_MOUSELEAVE:
	{

		if (IsWindowEnabled(hWnd))
		{
			hBitmap = (HBITMAP)LoadImage(NULL, TEXT("D:\\Clients\\CashButton(mouseleave).bmp"), IMAGE_BITMAP, btnBitmapWidth, btnBitmapHeight, LR_LOADFROMFILE);
			SendMessage(hWnd, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);
			UpdateWindow(hWnd);
		}
		else
		{
			hBitmap = (HBITMAP)LoadImage(NULL, TEXT("D:\\Clients\\CashButton(disable).bmp"), IMAGE_BITMAP, btnBitmapWidth, btnBitmapHeight, LR_LOADFROMFILE);
			SendMessage(hWnd, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);
			UpdateWindow(hWnd);
		}
		break;
	}
	case WM_ENABLE:
	{
		switch (wp)
		{
		case TRUE:
		{
			hBitmap = (HBITMAP)LoadImage(NULL, TEXT("D:\\Clients\\CashButton(mouseleave).bmp"), IMAGE_BITMAP, btnBitmapWidth, btnBitmapHeight, LR_LOADFROMFILE);
			SendMessage(hWnd, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);
			UpdateWindow(hWnd);
			break;
		}
		case FALSE:
		{
			hBitmap = (HBITMAP)LoadImage(NULL, TEXT("D:\\Clients\\CashButton(disable).bmp"), IMAGE_BITMAP, btnBitmapWidth, btnBitmapHeight, LR_LOADFROMFILE);
			SendMessage(hWnd, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);
			UpdateWindow(hWnd);
			break;
		}
		default:
		{
			break;
		}
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

		hdc = BeginPaint(hWnd, &ps);
		hdcMem = CreateCompatibleDC(hdc);
		oldBitmap = SelectObject(hdcMem, hBitmap);
		GetObject(hBitmap, sizeof(bitmap), &bitmap);
		BitBlt(hdc, 0, 0, btnBitmapWidth, btnBitmapHeight, hdcMem, 0, 0, SRCCOPY);
		SelectObject(hdcMem, oldBitmap);
		DeleteDC(hdcMem);
		EndPaint(hWnd, &ps);


		break;
	}
	default:
	{
		break;
	}

	}
	extern WNDPROC oldCashBtnProc;
	return CallWindowProc(oldCashBtnProc, hWnd, msg, wp, lp);
}



LRESULT CALLBACK EmployBtnProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	static TRACKMOUSEEVENT tme;
	static HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, TEXT("D:\\Clients\\EmployBtn(mouseleave).bmp"), IMAGE_BITMAP, btnBitmapWidth, btnBitmapHeight, LR_LOADFROMFILE);
	//����� ��� ��������� ������ �� Static
	//� ����� ������ ������������ ������ proc ��� static
	switch (msg)
	{
	case WM_MOUSEMOVE:
	{
		if (IsWindowEnabled(hWnd))
		{
			TrackMouseEvent(&tme);
			tme.cbSize = sizeof(tme);
			tme.dwFlags = TME_LEAVE;
			tme.dwHoverTime = HOVER_DEFAULT;
			tme.hwndTrack = hWnd;

			hBitmap = (HBITMAP)LoadImage(NULL, TEXT("D:\\Clients\\EmployBtn(mousemove).bmp"), IMAGE_BITMAP, btnBitmapWidth, btnBitmapHeight, LR_LOADFROMFILE);
			SendMessage(hWnd, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);
			UpdateWindow(hWnd);
		}
		else
		{
			hBitmap = (HBITMAP)LoadImage(NULL, TEXT("D:\\Clients\\EmployBtn(disable).bmp"), IMAGE_BITMAP, btnBitmapWidth, btnBitmapHeight, LR_LOADFROMFILE);
			SendMessage(hWnd, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);
			UpdateWindow(hWnd);
		}
		break;
	}
	case WM_MOUSELEAVE:
	{

		if (IsWindowEnabled(hWnd))
		{
			hBitmap = (HBITMAP)LoadImage(NULL, TEXT("D:\\Clients\\EmployBtn(mouseleave).bmp"), IMAGE_BITMAP, btnBitmapWidth, btnBitmapHeight, LR_LOADFROMFILE);
			SendMessage(hWnd, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);
			UpdateWindow(hWnd);
		}
		else
		{
			hBitmap = (HBITMAP)LoadImage(NULL, TEXT("D:\\Clients\\EmployBtn(disable).bmp"), IMAGE_BITMAP, btnBitmapWidth, btnBitmapHeight, LR_LOADFROMFILE);
			SendMessage(hWnd, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);
			UpdateWindow(hWnd);
		}
		break;
	}
	case WM_ENABLE:
	{
		switch (wp)
		{
		case TRUE:
		{
			hBitmap = (HBITMAP)LoadImage(NULL, TEXT("D:\\Clients\\EmployBtn(mouseleave).bmp"), IMAGE_BITMAP, btnBitmapWidth, btnBitmapHeight, LR_LOADFROMFILE);
			SendMessage(hWnd, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);
			UpdateWindow(hWnd);
			break;
		}
		case FALSE:
		{
			hBitmap = (HBITMAP)LoadImage(NULL, TEXT("D:\\Clients\\EmployBtn(disable).bmp"), IMAGE_BITMAP, btnBitmapWidth, btnBitmapHeight, LR_LOADFROMFILE);
			SendMessage(hWnd, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);
			UpdateWindow(hWnd);
			break;
		}
		default:
		{
			break;
		}
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

		hdc = BeginPaint(hWnd, &ps);

		hdcMem = CreateCompatibleDC(hdc);

		//hBitmap = (HBITMAP)LoadImage(NULL, TEXT("D:\\Clients\\ClientButton(disable).bmp"), IMAGE_BITMAP, 100, 40, LR_LOADFROMFILE);
		oldBitmap = SelectObject(hdcMem, hBitmap);

		GetObject(hBitmap, sizeof(bitmap), &bitmap);
		BitBlt(hdc, 0, 0, btnBitmapWidth, btnBitmapHeight, hdcMem, 0, 0, SRCCOPY);

		SelectObject(hdcMem, oldBitmap);
		DeleteDC(hdcMem);

		EndPaint(hWnd, &ps);


		break;
	}
	default:
	{
		break;
	}

	}
	extern WNDPROC oldEmployBtnProc;
	return CallWindowProc(oldEmployBtnProc, hWnd, msg, wp, lp);
}