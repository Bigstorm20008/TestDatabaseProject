//���������� ���������� Windows
#include <Windows.h>
#include "ControlPanel.h"
#include "AutentificationClass.h"


#define controlPanelWnd 1000
#define autorizationWnd 1001
//�������� ������� ��� ��������� ���������
LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

CSqlFramework* sqlODBC = nullptr;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{


	LPWSTR szClassName = L"MainWindowApp";               //���������� � ������ ������ ����
	LPWSTR szWindowName = L"������� ���� ����������";    //���������� � ��������� ����

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
		sqlODBC = new CSqlFramework;               //������� ��������� �� ����� ��� ������ � ������ ������
		AutentificationClass autentificationWindow(hWnd, autorizationWnd);
		break;
	}
	case WM_SIZE:
	{
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

