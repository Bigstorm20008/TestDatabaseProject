#pragma once

#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <io.h>
#include <fcntl.h>


class MyButton
{
private:
	LPWSTR szClassName;    //Имя класса кнопки
	LPWSTR szButtonName;   //Название кнопки
public:
	MyButton();
	~MyButton();

	//Функция создающая кнопку (принимает следующие аргументы: дескриптор родительского окна, идентификатор кнопки,
	//имя кнопки, позицию кнопки(x,y), длину и ширину)
	void CreateButton(HWND hWnd, UINT identifier, LPWSTR buttonName, int xPos, int yPos, int width, int height);

};

LRESULT CALLBACK ButtonProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);