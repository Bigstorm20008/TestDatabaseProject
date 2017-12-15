#pragma once           //Исключаем повторные включения(работает только в OC Windows)

#include <Windows.h>   //Подключаем библиотеку WINDOWS

#include "MyButton.h"
#include "SqlFramework.h"
#include "AutorisationClass.h"
#include "Constants.h"


//Класс для авторизации в программе(используется для формирования интерфейса окна и проверки введенных данных)
class AutentificationClass
{
private:
	TCHAR* username;    //сюда сохраним введеное имя пользователя
	TCHAR* password;    //сюда сохраним пароль

public:
	//Конструктор класса(получает дескриптор родительского окна и идентификатор для создания и управления дочернего окна)
	AutentificationClass(HWND hWnd, UINT identifier);
	//Деструктор
	~AutentificationClass();
};


//Функция обработчик для обработки сообщений дочернего окна(объявлена вне класса)
LRESULT CALLBACK AutentificationProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);