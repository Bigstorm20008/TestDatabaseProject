//Подключаем библиотеку Windows
#include <Windows.h>
#include "AutentificationClass.h"
#include <vld.h>
#include "Constants.h"

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")



//Прототип Функции для обработки сообщений
LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

CSqlFramework* sqlODBC = nullptr;
//MyListView* listview = nullptr;
LPTSTR szClassName = L"MainWindowApp";               //Переменная с именем класса главного окна
LPTSTR szWindowName = L"Главное окно приложения";    //Переменная с названием главного окна

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{


	

	//Заполняем структуру, необходимую для регистрации окна в Windows
	WNDCLASSEX wcex;
	wcex.cbClsExtra = wcex.cbWndExtra = NULL;
	wcex.cbSize = sizeof(WNDCLASSEX);                                       //Размер структуры
	wcex.hbrBackground = static_cast<HBRUSH>(GetStockObject(GRAY_BRUSH));   //Фон окна
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);                             //Указываем тип указателя мыши
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);                           //Указываем стандартную иконку приложения
	wcex.hIconSm = NULL;                                                    //стандартная иконка на панели
	wcex.hInstance =(HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE);         //Получаем дескриптор нашего приложения
	wcex.lpfnWndProc = MainWndProc;                                         //Указываем функцию для обработки сообщений в главном окне
	wcex.lpszClassName = szClassName;                                       //Имя класса нашего окна
	wcex.lpszMenuName = NULL;                                               //Меню отсутствует
	wcex.style = CS_HREDRAW | CS_VREDRAW;                                   //Указываем стиль отображения окна(перерисовка по ветикали и горизонтали)

	//Позле заполнения структуры регистрируем класс окна в Windows
	//В случае ошибки регистрации выдаем сообщение об ошибке и прерываем выполнение программы
	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL, L"Ошибка", L"Не удалось зарегистрировать окно!!!", MB_OK);
		return FALSE;
	}

	//При успешной регистрации класса окна создаем само окно и отображаем его на экране
	HWND hWnd = CreateWindow(szClassName,                                  //Класс окна
		                     szWindowName,                                 //Имя окна
							 WS_OVERLAPPEDWINDOW | WS_VISIBLE,             //Стиль окна(перекрывающееся и видимое)
							 CW_USEDEFAULT,                                //
							 CW_USEDEFAULT,                                //позиция окна по умолчанию
							 CW_USEDEFAULT,                                //
							 CW_USEDEFAULT,                                //размеры окна по умолчанию
							 NULL,                                         //родительское окно  - рабочий стол
							 NULL,                                         //меню отсутствует
							 hInstance,                                    //дескриптор приложения
							 NULL); 

	//Проверим создалось ли окно и в случае ошибки выведем сообщение и прервем работу программы
	if (!hWnd)
	{
		MessageBox(NULL, L"Ошибка", L"Не удалось создать окно", MB_OK);
		return FALSE;
	}


	//запускаем цикл обработки сообщений для нашего окна

	MSG msg;  //Структура для получения сообщений
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}


	//При завершении програмы вернем код завершения

	return static_cast<int>(msg.wParam);
}


//Определение функции для обработки сообщений
LRESULT CALLBACK MainWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
	{	
		sqlODBC = new CSqlFramework;               //Создади указатель на класс для работы с базой данных
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
			//MessageBox(NULL, L"Статик", L"Info", MB_OK);
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
    // реакция на сообщение о прекращении работы программы
	case WM_DESTROY:
		sqlODBC->CloseConnection();
		delete sqlODBC;
		sqlODBC = nullptr;
		
		PostQuitMessage(0);  
		break;
	//Обработка всех остальных сообщений производится ОС по умолчанию
	default:
		return DefWindowProc(hWnd,msg,wParam,lParam); //Просто вернем системе сообщение, которого нет в нашем обработчике
	}
	return 0;
}

