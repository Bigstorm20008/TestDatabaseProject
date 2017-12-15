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
	HFONT hFont;      //Переменная для создания шрифта
	HDC hDC;          //Контекст устройства
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
	case WM_LBUTTONDOWN:    //Обработка при нажатии левой кнопки мыши
	{
		UINT indentifer = GetWindowLong(hWnd, GWLP_ID);              //получим идентификатор кнопки
		LONG hWndParent = GetWindowLong(hWnd, GWLP_HWNDPARENT);      //получим дескриптор родительского окна
		SendMessage((HWND)hWndParent, WM_COMMAND, indentifer,0);     //отправим сообщение WM_COMMAND родительскому окну для последующей обработки
		break;
	}
	case WM_PAINT:         //Обработка при отрисовке окна
	{
		hDC = BeginPaint(hWnd, &ps);  //Начало рисования в окне	
		hFont = CreateFont(16, 0, 0, 0, 0, 0, 0, 0,          //Создаем необходимый шрифт
			DEFAULT_CHARSET,
			0, 0, 0, VARIABLE_PITCH,
			L"Time New Romans");
		SelectObject(hDC, hFont);    //Выбираем шрифт для отрисовки текста
		RECT rc;
		GetClientRect(hWnd, &rc);    //Получаем клиентскую область для рисования в окне
		SelectObject(hDC, hBrush);
		FillRect(hDC, &rc, hBrush);
		TCHAR title[255];            //Переменная для получения заголовка окна
		GetWindowText(hWnd, title, 256);  //Получим название кнопки
		size_t len = wcslen(title);       //Вычислим длину названия
		//Напишем на кнопке название
		SetBkMode(hDC,TRANSPARENT);
		DrawText(hDC,
			     title,
			     len,
				 &rc,
			     DT_CENTER);		
		EndPaint(hWnd, &ps); //Конец рисования(освободим ресурсы)
		ReleaseDC(hWnd, hDC);
		break;
	}
	// реакция на сообщение о прекращении работы программы
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
		//Обработка всех остальных сообщений производится ОС по умолчанию
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam); //Просто вернем системе сообщение, которого нет в нашем обработчике
	}
	return 0;
}