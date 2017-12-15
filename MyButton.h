#pragma once

#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <io.h>
#include <fcntl.h>


class MyButton
{
private:
	LPWSTR szClassName;    //��� ������ ������
	LPWSTR szButtonName;   //�������� ������
public:
	MyButton();
	~MyButton();

	//������� ��������� ������ (��������� ��������� ���������: ���������� ������������� ����, ������������� ������,
	//��� ������, ������� ������(x,y), ����� � ������)
	void CreateButton(HWND hWnd, UINT identifier, LPWSTR buttonName, int xPos, int yPos, int width, int height);

};

LRESULT CALLBACK ButtonProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);