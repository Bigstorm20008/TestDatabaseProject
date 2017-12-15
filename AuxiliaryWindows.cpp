#include "AuxiliaryWindows.h"


AuxiliaryWindows::AuxiliaryWindows()
{
	extern LPTSTR szClassName;
	extern LPTSTR szWindowName;
	mainWnd = FindWindow(szClassName, szWindowName);
	RECT mainRC;
	GetClientRect(mainWnd, &mainRC);
	auxiliaryWndWidth = mainRC.right / 3;
	auxiliaryWndHeight = auxiliaryWndWidth;
	xPosCentred = mainRC.right / 2 - auxiliaryWndWidth / 2;
	yPosCentred = mainRC.bottom / 2 - auxiliaryWndHeight / 2;
}


AuxiliaryWindows::~AuxiliaryWindows()
{
}

void AuxiliaryWindows::createAddNewClientWnd()
{
	WNDCLASSEX wc;
	wc.cbClsExtra = wc.cbWndExtra = 0;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = NULL;
	wc.hIconSm = NULL;
	wc.hInstance = (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE);
	wc.lpfnWndProc = addNewClientWndProc;
	wc.lpszClassName = TEXT("NewClientWnd");
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&wc);
	
	HWND hwnd = CreateWindow(TEXT("NewClientWnd"),
		         TEXT("���������� ������ �������"),
				 WS_CHILD|WS_VISIBLE|WS_BORDER,
				 xPosCentred,yPosCentred,
				 auxiliaryWndWidth,auxiliaryWndHeight,
				 mainWnd,
				 (HMENU)ID_ADD_NEW_CLIENT_WND,
				 (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
				 NULL);

	HWND staticCaption = CreateWindow(TEXT("STATIC"),
		                              TEXT("���������� ������ ������� � ���� ������"),
									  WS_CHILD | WS_VISIBLE | SS_CENTER | SS_EDITCONTROL,
									  0,0,
									  auxiliaryWndWidth,20,
									  hwnd,
									  (HMENU)ID_STATIC_CAPTION,
									  (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE), 
									  NULL);

	RECT hwndRC;
	GetClientRect(hwnd, &hwndRC);
	int btnWidth = 150;
	int btnHeight = 25;
	int xPos = hwndRC.right - btnWidth - 10;
	int yPos = hwndRC.bottom - btnHeight - 10;
	HWND okBtn = CreateWindow(TEXT("BUTTON"),
		                      TEXT("�������� � ����"),
							  WS_CHILD | WS_VISIBLE |BS_DEFPUSHBUTTON,
							  xPos,yPos,
							  btnWidth, btnHeight,
							  hwnd,
							  (HMENU)ID_ADD_TO_BASE_BTN,
							  (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE), 
							  NULL);
	xPos -= btnWidth + 10;

	HWND cancelBtn = CreateWindow(TEXT("BUTTON"),
		                          TEXT("������"),
		                          WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
		                          xPos, yPos,
		                          btnWidth, btnHeight,
		                          hwnd,
								  (HMENU)ID_CANCEL_ADD_TO_BASE_BTN,
		                          (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
		                          NULL);
}

void AuxiliaryWindows::destroyAuxiliaryWindow()
{
	HWND hwndToDestroy = GetDlgItem(mainWnd, ID_ADD_NEW_CLIENT_WND);
	if (hwndToDestroy)
	{
		DestroyWindow(hwndToDestroy);
	}
}


LRESULT CALLBACK addNewClientWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)

{
	switch (msg)
	{
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
			case ID_CANCEL_ADD_TO_BASE_BTN:
			{
				extern LPTSTR szClassName;
				extern LPTSTR szWindowName;
				HWND mainWnd = FindWindow(szClassName, szWindowName);
				HWND controlPanel = GetDlgItem(mainWnd, ID_CASHIER_PANEL);
				SendMessage(controlPanel, WM_COMMAND, ID_CLIENT_BTN, 0);
				UpdateWindow(mainWnd);
				break;
			}
			default:
			{
				break;
			}
		}
		break;
	}
	// ������� �� ��������� � ����������� ������ ���������
	case WM_DESTROY:
	{
		DestroyWindow(hwnd);
		break;
	}
		//��������� ���� ��������� ��������� ������������ �� �� ���������
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam); //������ ������ ������� ���������, �������� ��� � ����� �����������
	}
	return 0;
}