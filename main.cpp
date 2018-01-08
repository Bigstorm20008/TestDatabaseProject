
#include <Windows.h>     //connect library for OS Windows programming
#include <vld.h>         //connect for check memory leak(need download and install from https://vld.codeplex.com/releases)

#include "ControlPanel.h"
#include "SqlFramework.h"
#include "AutorisationClass.h"
#include "AutentificationClass.h"
#include "InterfaceForRole.h"

//for visual elements style Windows Vista and higher
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")



//Prototype for message processing function
LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);



LPTSTR szClassName = L"MainWindowApp";               //window class name for main application window
LPTSTR szWindowName = L"Главное окно приложения";    //title for main application window

CSqlFramework* sqlODBC = nullptr;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	//Create and fill structure for registration window class in OS Windows
	WNDCLASSEX wcex;
	wcex.cbClsExtra = wcex.cbWndExtra = NULL;
	wcex.cbSize = sizeof(WNDCLASSEX);                                       //size of structure
	wcex.hbrBackground = static_cast<HBRUSH>(GetStockObject(GRAY_BRUSH)); //window background
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);                             //standart mouse pointer
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);                           //standart main icon app
	wcex.hIconSm = NULL;                                                    //standart small icon app
	wcex.hInstance = (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE);         //descriptor for main window application
	wcex.lpfnWndProc = MainWndProc;                                         //pointer to message processing function
	wcex.lpszClassName = szClassName;                                       //window class name
	wcex.lpszMenuName = NULL;                                               //no menu in window
	wcex.style = CS_HREDRAW | CS_VREDRAW;                                   //window style (horizontal and vertical redraw)

	//Register application window in OS Windows
	RegisterClassEx(&wcex);

	//Get desktop width and height
	int desktopWidth = GetSystemMetrics(SM_CXSCREEN);        //width
	int desktopHeight = GetSystemMetrics(SM_CYSCREEN);       //height

	//Compute main window application parameters
	int mainWndWidth = desktopWidth * 0.7;                      //main window width
	int mainWndHeight = desktopHeight * 0.85;                    //main window height
	int mainWndXPos = desktopWidth / 2 - mainWndWidth / 2;      //xPos for placed window at center
	int mainWndYPos = desktopHeight / 2 - mainWndHeight / 2;    //yPos for placed window at center
	//Create main window and show it
	HWND hWnd = CreateWindow(szClassName,                    //window class name
		szWindowName,                                        //title of main window
		WS_OVERLAPPEDWINDOW |  WS_VISIBLE,  //window style
		mainWndXPos,                                         //x position on desktop
		mainWndYPos,                                         //y position on desktop
		mainWndWidth,                                        //width of window
		mainWndHeight,                                       //height of window
		NULL,                                                //parent window - desktop
		NULL,                                                //no menu
		hInstance,                                           //descriptor for main window application
		NULL);

	//ShowWindow(hWnd, SW_MAXIMIZE);
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
	static AutentificationClass* autentfication = nullptr;
	static AutorisationClass* authorisation = nullptr;
	static CInterfaceForRole* userInterface = nullptr;
	switch (msg)
	{
	//process window create message
	case WM_CREATE:
	{
		sqlODBC = new CSqlFramework;
		autentfication = new AutentificationClass(hWnd, ID_AUTENTIFICATION_WND);
		break;
	}
	case INF_DATABASE_CONNECTED:
	{
		delete autentfication;
		autentfication = nullptr;
		TCHAR* pRoleName = nullptr;
		authorisation = new AutorisationClass;
		pRoleName = authorisation->GetRoleOfCurrentUser();
		userInterface = new CInterfaceForRole;
		userInterface->createInterfaceForRole(pRoleName);
		delete authorisation;
		authorisation = nullptr;
		break;
	}
	case WM_SIZE:
	{
		break;
	}
	case WM_LISTVIEW_CLICKED:
	{
		userInterface->loadInfoAboutSelectedPerson();
		break;
	}
	case INF_OPERATION_COMPLETE:
	{
		userInterface->setFocusOnListWindow();
		break;
	}
	//process messages from control(button,static,listview e.t.c)
	case WM_COMMAND:
	{
		switch (wParam)
		{
			//Messages from control Panel
			//===========================================================
			case ID_STATIC_CLIENT_BTN:
			{
				userInterface->activateClientView();
				break;
			}
			case ID_STATIC_CASH_BTN:
			{	
				userInterface->activateCashView();
				break;
			}
			case ID_STATIC_DILER_BTN:
			{
				userInterface->activateEmployeesView();
				break;
			}
			//===========================================================


			//Messages from cash view
			//===========================================================
			case ID_CASH_IN_BTN:
			{		
				userInterface->activateCashInCashOutWindow(ID_CASH_IN_BTN);
				break;
			}
			case ID_CASH_OUT_BTN:
			{
				userInterface->activateCashInCashOutWindow(ID_CASH_OUT_BTN);
				break;
			}
			case ID_EXIT_FROM_CASINO_BTN:
			{
				userInterface->changeClientState(ID_EXIT_FROM_CASINO_BTN);
				break;
			}
			//===========================================================


			//Messages from Client View
			//===========================================================
			case ID_ADD_CLIENT_TO_DATABASE:
			{
				userInterface->activateAddClientToDatabaseWindow();
				break;
			}
			case ID_ENTRANCE_IN_CASINO_BTN:
			{
				userInterface->changeClientState(ID_ENTRANCE_IN_CASINO_BTN);
				break;
			}
			case ID_CANCEL_AUXILIARY_BTN:
			{
				break;
			}
			default:
			{
				break;
			}
		}
		break;
	}
	//process message if aplication close
	case WM_DESTROY:
	{
		sqlODBC->CloseConnection();
		delete sqlODBC;
		sqlODBC = nullptr;
		if (userInterface)
		{
			delete userInterface;
			userInterface = nullptr;
		}
		PostQuitMessage(0);                 //send message to OS Windows about closing app
		break;
	}
		//processing other messages provide OS Windows
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}