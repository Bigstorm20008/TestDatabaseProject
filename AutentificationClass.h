#pragma once           //��������� ��������� ���������(�������� ������ � OC Windows)

#include <Windows.h>   //���������� ���������� WINDOWS

#include "MyButton.h"
#include "SqlFramework.h"
#include "AutorisationClass.h"
#include "Constants.h"


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