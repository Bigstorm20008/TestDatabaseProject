#pragma once           //��������� ��������� ���������(�������� ������ � OC Windows)

#include <Windows.h>   //���������� ���������� WINDOWS

#include "MyButton.h"
#include "SqlFramework.h"
#include "AutorisationClass.h"

#define ID_USER_NAME 1000
#define ID_PASS 1001
#define ID_OKBTN 1002
#define ID_CANCELBTN 1003
#define ID_MAIN_PANEL 1004

//����� ��� ����������� � ���������(������������ ��� ������������ ���������� ���� � �������� ��������� ������)
class AutentificationClass
{
private:
	TCHAR* username;    //���� �������� �������� ��� ������������
	TCHAR* password;    //���� �������� ������

public:
	//����������� ������(�������� ���������� ������������� ���� � ������������� ��� �������� � ���������� ��������� ����)
	AutentificationClass(HWND hWnd, UINT identifier);
	//����������
	~AutentificationClass();
};


//������� ���������� ��� ��������� ��������� ��������� ����(��������� ��� ������)
LRESULT CALLBACK AutentificationProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);