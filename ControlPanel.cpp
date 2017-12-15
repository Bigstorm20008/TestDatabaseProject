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


void ControlPanel::CreateControlPanel(HWND hWnd, UINT identify)
{
	identifyNum = identify;
	RECT rc;
	GetClientRect(hWnd, &rc);
	int xPos = rc.left;
	int yPos = rc.top;
	int width = rc.right - rc.left;
	int height = 50;
	HWND cPanelWnd = CreateWindow(L"ControlPanelWindow",
		                          L"",
		                          WS_CHILD | WS_VISIBLE,
		                          xPos,
		                          yPos,
		                          width,
		                          height,
		                          hWnd,
		                          HMENU(identify),
		                          (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
		                          NULL);
}

void ControlPanel::MoveMyWindow(HWND hWnd)
{
	HWND chWnd = GetDlgItem(hWnd, identifyNum);
	MoveWindow(chWnd, 70, 0, 800, 50, TRUE);
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
	{
		int heightBtn = 40;
		int widthBtn = 60;
		int xPos = 5;
		int yPos = 5;
		MyButton btn1; 
		btn1.CreateButton(hWnd,ID_CASH_BTN, L"�����", xPos, yPos, widthBtn, heightBtn);
		MyButton btn2;
		btn2.CreateButton(hWnd, ID_CLIENT_BTN, L"�������", xPos += (widthBtn + 5), yPos, widthBtn, heightBtn);
		MyButton btn3;
		btn3.CreateButton(hWnd, ID_DILER_BTN, L"������", xPos += (widthBtn + 5), yPos, widthBtn, heightBtn);
		break;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case ID_CASH_BTN:
		{
			MessageBox(NULL, L"�����", L"����������", MB_OK);
			break;
		}
		case ID_CLIENT_BTN:
		{
			MessageBox(NULL, L"�������", L"����������", MB_OK);
			break;
		}
		case ID_DILER_BTN:
		{
			MessageBox(NULL, L"������", L"����������", MB_OK);
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