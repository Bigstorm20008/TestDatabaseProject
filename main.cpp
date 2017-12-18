
#include <Windows.h>     //connect library for OS Windows programming
#include <vld.h>         //connect for check memory leak(need download and install from https://vld.codeplex.com/releases)

#include "AutentificationClass.h"    //connect class for create Autentification window and check login and password
#include "Constants.h"               //global variables for this project(include identifiers for windows and some constants)


//for visual elements style Windows Vista and higher
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")



//Prototype for message processing function
LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

CSqlFramework* sqlODBC = nullptr;                    //global pointer to CSqlFramework class for working with database(using ODBC API)
LPTSTR szClassName = L"MainWindowApp";               //window class name for main application window
LPTSTR szWindowName = L"Главное окно приложения";    //title for main application window

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	//Create and fill structure for registration window class in OS Windows
	WNDCLASSEX wcex;
	wcex.cbClsExtra = wcex.cbWndExtra = NULL;
	wcex.cbSize = sizeof(WNDCLASSEX);                                       //size of structure
	wcex.hbrBackground = static_cast<HBRUSH>(GetStockObject(GRAY_BRUSH));   //window background
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);                             //standart mouse pointer
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);                           //standart main icon app
	wcex.hIconSm = NULL;                                                    //standart small icon app
	wcex.hInstance =(HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE);         //descriptor for main window application
	wcex.lpfnWndProc = MainWndProc;                                         //pointer to message processing function
	wcex.lpszClassName = szClassName;                                       //window class name
	wcex.lpszMenuName = NULL;                                               //no menu in window
	wcex.style = CS_HREDRAW | CS_VREDRAW;                                   //window style (horizontal and vertical redraw)

	//Register application window in OS Windows
	RegisterClassEx(&wcex);
	

	//Create main window and show it
	HWND hWnd = CreateWindow(szClassName,                                  //window class name
		                     szWindowName,                                 //title of main window
							 WS_OVERLAPPEDWINDOW | WS_VISIBLE,             //window style
							 CW_USEDEFAULT,                                //x position on desktop
							 CW_USEDEFAULT,                                //y position on desktop
							 CW_USEDEFAULT,                                //width of window
							 CW_USEDEFAULT,                                //height of window
							 NULL,                                         //parent window - desktop
							 NULL,                                         //no menu
							 hInstance,                                    //descriptor for main window application
							 NULL); 

	//check for creating window, if window no create - send message for user and break application
	if (!hWnd)
	{
		MessageBox(NULL, L"Ошибка", L"Не удалось создать окно", MB_OK);
		return FALSE;
	}


	//launch loop for processing message

	MSG msg;  //Structure for message in OS Windows
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);   //for keyboard messages
		DispatchMessage(&msg);    //for mouse messages
	}


	//end application
	return static_cast<int>(msg.wParam);
}


//definition for message processing function
LRESULT CALLBACK MainWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	//process window create message
	case WM_CREATE:
	{	
		sqlODBC = new CSqlFramework;               //initialize pointer for database working in dynamic memory
		AutentificationClass autentificationWindow(hWnd, autorizationWnd);	//create autentification window	and give control to message processing function of autentificationWindow
		break;
	}
	//process messages from control(button,static,listview e.t.c)
	case WM_COMMAND:
	{
		if (LOWORD(wParam) == ID_ADD_NEW_CLIENT_BTN)      //if message from ID_ADD_NEW_CLIENT_BTN (defined in "Constants.h")
		{
			HWND controlPanel = GetDlgItem(hWnd, ID_CASHIER_PANEL);            //Get controlPanel handler
			SendMessage(controlPanel, WM_COMMAND, ID_ADD_NEW_CLIENT_BTN, 0);   //and send message ID_ADD_NEW_CLIENT_BTN (defined in "Constants.h") in message processing function of controlPanel window
		}
		break;
	}
	//process message from control with _NOTIFY style
	case WM_NOTIFY:
	{
		switch (((LPNMHDR)lParam)->code)
		{
		case NM_CLICK:    //left mouse button
		case NM_RCLICK:   //rigth mouse button
		{
			if (((LPNMHDR)lParam)->idFrom == ID_LIST_FOR_CLIENTVIEW)                  //if message send ID_LIST_FOR_CLIENTVIEW(defined in "Constants.h")
			{
				HWND controlPanel = GetDlgItem(hWnd, ID_CASHIER_PANEL);               //Get controlPanel handler
				HWND listWnd = GetDlgItem(hWnd, ID_LIST_FOR_CLIENTVIEW);              //Get listview handler of client view in application 
				SendMessage(controlPanel, WM_LISTVIEW_CLICKED, 0, 0);                 ////and send message WM_LISTVIEW_CLICKED (defined in "Constants.h") in message processing function of controlPanel window
			}
			break;
		}
		default:
			break;
		}
		break;
	}
    //process message if aplication close
	case WM_DESTROY:
		sqlODBC->CloseConnection();         //close connection with database and free all resource
		delete sqlODBC;                     //delete pointer
		sqlODBC = nullptr;                  //set pointer at not valid
		PostQuitMessage(0);                 //send message to OS Windows about closing app
		break;
	//processing other messages provide OS Windows
	default:
		return DefWindowProc(hWnd,msg,wParam,lParam); 
	}
	return 0;
}

