#include "MyButton.h"


MyButton::MyButton()
{
	szClassName = L"MyButton";

	WNDCLASSEX wcex;
	wcex.cbClsExtra = wcex.cbWndExtra = 0;
	wcex.cbSize = sizeof(wcex);
	wcex.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hIconSm = NULL;
	wcex.hInstance = reinterpret_cast<HINSTANCE>(GetWindowLong(NULL, GWLP_HINSTANCE));
	wcex.lpfnWndProc = ButtonProc;
	wcex.lpszClassName = szClassName;
	wcex.lpszMenuName = NULL;
	wcex.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&wcex);
}


MyButton::~MyButton()
{
}


void MyButton::CreateButton(HWND hWnd, UINT identifier, LPWSTR buttonName, int xPos, int yPos, int width, int height)
{
	CreateWindow(szClassName,
		         buttonName,
				 WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
				 xPos,
				 yPos,
				 width,
				 height,
				 hWnd,
				 (HMENU)identifier,
				 (HINSTANCE)GetWindowLong(NULL,GWLP_HINSTANCE),
				 NULL);
	szButtonName = buttonName;
}



LRESULT CALLBACK ButtonProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HBRUSH hBrush = CreateSolidBrush(RGB(220, 217, 253));
	static TRACKMOUSEEVENT tme;
	HFONT hFont;      //���������� ��� �������� ������
	HDC hDC;          //�������� ����������
	PAINTSTRUCT ps;
	switch (msg)
	{
	case WM_CREATE:
	{	
		hBrush = CreateSolidBrush(RGB(220, 217, 253));
		UpdateWindow(hWnd);
		break;
	}
	case WM_MOUSEMOVE:
	{
		tme.cbSize = sizeof(tme);
		tme.dwFlags = TME_LEAVE;
		tme.dwHoverTime = HOVER_DEFAULT;
		tme.hwndTrack = hWnd;
		TrackMouseEvent(&tme);
		RECT rc;
		GetClientRect(hWnd, &rc);
		hBrush = CreateSolidBrush(RGB(180, 174, 251));
		InvalidateRect(hWnd, &rc, TRUE);
		UpdateWindow(hWnd);
		break;
	}
	case WM_MOUSELEAVE:
	{
		RECT rc;
		GetClientRect(hWnd, &rc);
		hBrush = CreateSolidBrush(RGB(220, 217, 253));
		InvalidateRect(hWnd, &rc, TRUE);
		UpdateWindow(hWnd);
		break;
	}
	case WM_LBUTTONDOWN:    //��������� ��� ������� ����� ������ ����
	{
		UINT indentifer = GetWindowLong(hWnd, GWLP_ID);              //������� ������������� ������
		LONG hWndParent = GetWindowLong(hWnd, GWLP_HWNDPARENT);      //������� ���������� ������������� ����
		SendMessage((HWND)hWndParent, WM_COMMAND, indentifer,0);     //�������� ��������� WM_COMMAND ������������� ���� ��� ����������� ���������
		break;
	}
	case WM_PAINT:         //��������� ��� ��������� ����
	{
		hDC = BeginPaint(hWnd, &ps);  //������ ��������� � ����	
		hFont = CreateFont(16, 0, 0, 0, 0, 0, 0, 0,          //������� ����������� �����
			DEFAULT_CHARSET,
			0, 0, 0, VARIABLE_PITCH,
			L"Time New Romans");
		SelectObject(hDC, hFont);    //�������� ����� ��� ��������� ������
		RECT rc;
		GetClientRect(hWnd, &rc);    //�������� ���������� ������� ��� ��������� � ����
		SelectObject(hDC, hBrush);
		FillRect(hDC, &rc, hBrush);
		TCHAR title[255];            //���������� ��� ��������� ��������� ����
		GetWindowText(hWnd, title, 256);  //������� �������� ������
		size_t len = wcslen(title);       //�������� ����� ��������
		//������� �� ������ ��������
		SetBkMode(hDC,TRANSPARENT);
		DrawText(hDC,
			     title,
			     len,
				 &rc,
			     DT_CENTER);		
		EndPaint(hWnd, &ps); //����� ���������(��������� �������)
		ReleaseDC(hWnd, hDC);
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