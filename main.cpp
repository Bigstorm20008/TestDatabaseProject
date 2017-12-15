//���������� ���������� Windows
#include <Windows.h>
#include "AutentificationClass.h"
#include <vld.h>
#include "Constants.h"

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")



//�������� ������� ��� ��������� ���������
LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

CSqlFramework* sqlODBC = nullptr;
//MyListView* listview = nullptr;
LPTSTR szClassName = L"MainWindowApp";               //���������� � ������ ������ �������� ����
LPTSTR szWindowName = L"������� ���� ����������";    //���������� � ��������� �������� ����

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{


	

	//��������� ���������, ����������� ��� ����������� ���� � Windows
	WNDCLASSEX wcex;
	wcex.cbClsExtra = wcex.cbWndExtra = NULL;
	wcex.cbSize = sizeof(WNDCLASSEX);                                       //������ ���������
	wcex.hbrBackground = static_cast<HBRUSH>(GetStockObject(GRAY_BRUSH));   //��� ����
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);                             //��������� ��� ��������� ����
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);                           //��������� ����������� ������ ����������
	wcex.hIconSm = NULL;                                                    //����������� ������ �� ������
	wcex.hInstance =(HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE);         //�������� ���������� ������ ����������
	wcex.lpfnWndProc = MainWndProc;                                         //��������� ������� ��� ��������� ��������� � ������� ����
	wcex.lpszClassName = szClassName;                                       //��� ������ ������ ����
	wcex.lpszMenuName = NULL;                                               //���� �����������
	wcex.style = CS_HREDRAW | CS_VREDRAW;                                   //��������� ����� ����������� ����(����������� �� �������� � �����������)

	//����� ���������� ��������� ������������ ����� ���� � Windows
	//� ������ ������ ����������� ������ ��������� �� ������ � ��������� ���������� ���������
	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL, L"������", L"�� ������� ���������������� ����!!!", MB_OK);
		return FALSE;
	}

	//��� �������� ����������� ������ ���� ������� ���� ���� � ���������� ��� �� ������
	HWND hWnd = CreateWindow(szClassName,                                  //����� ����
		                     szWindowName,                                 //��� ����
							 WS_OVERLAPPEDWINDOW | WS_VISIBLE,             //����� ����(��������������� � �������)
							 CW_USEDEFAULT,                                //
							 CW_USEDEFAULT,                                //������� ���� �� ���������
							 CW_USEDEFAULT,                                //
							 CW_USEDEFAULT,                                //������� ���� �� ���������
							 NULL,                                         //������������ ����  - ������� ����
							 NULL,                                         //���� �����������
							 hInstance,                                    //���������� ����������
							 NULL); 

	//�������� ��������� �� ���� � � ������ ������ ������� ��������� � ������� ������ ���������
	if (!hWnd)
	{
		MessageBox(NULL, L"������", L"�� ������� ������� ����", MB_OK);
		return FALSE;
	}


	//��������� ���� ��������� ��������� ��� ������ ����

	MSG msg;  //��������� ��� ��������� ���������
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}


	//��� ���������� �������� ������ ��� ����������

	return static_cast<int>(msg.wParam);
}


//����������� ������� ��� ��������� ���������
LRESULT CALLBACK MainWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
	{	
		sqlODBC = new CSqlFramework;               //������� ��������� �� ����� ��� ������ � ����� ������
		AutentificationClass autentificationWindow(hWnd, autorizationWnd);		
		break;
	}
	case WM_SIZE:
	{
		break;
	}
	case WM_COMMAND:
	{
		if (LOWORD(wParam) == ID_ADD_NEW_CLIENT_BTN)
		{
			HWND controlPanel = GetDlgItem(hWnd, ID_CASHIER_PANEL);
			SendMessage(controlPanel, WM_COMMAND, ID_ADD_NEW_CLIENT_BTN, 0);
		}
   		//if (LOWORD(wParam) == ID_IMAGE_WND)
			//MessageBox(NULL, L"������", L"Info", MB_OK);
		break;
	}
	case WM_NOTIFY:
	{
		switch (((LPNMHDR)lParam)->code)
		{
		case NM_CLICK:
		case NM_RCLICK:
		{
			if (((LPNMHDR)lParam)->idFrom == ID_LIST_FOR_CLIENTVIEW)
			{
				HWND controlPanel = GetDlgItem(hWnd, ID_CASHIER_PANEL);
				HWND listWnd = GetDlgItem(hWnd, ID_LIST_FOR_CLIENTVIEW);
				SendMessage(controlPanel, WM_LISTVIEW_CLICKED, 0, 0);
			}
			break;
		}
		default:
			break;
		}
		break;
	}
    // ������� �� ��������� � ����������� ������ ���������
	case WM_DESTROY:
		sqlODBC->CloseConnection();
		delete sqlODBC;
		sqlODBC = nullptr;
		
		PostQuitMessage(0);  
		break;
	//��������� ���� ��������� ��������� ������������ �� �� ���������
	default:
		return DefWindowProc(hWnd,msg,wParam,lParam); //������ ������ ������� ���������, �������� ��� � ����� �����������
	}
	return 0;
}

