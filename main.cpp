
#include <Windows.h>     //connect library for OS Windows programming
#include <vld.h>         //connect for check memory leak(need download and install from https://vld.codeplex.com/releases)

#include "UserInterface.h"

//for visual elements style Windows Vista and higher
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")



//Prototype for message processing function
LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	LPTSTR szClassName = L"MainWindowApp";               //window class name for main application window
	LPTSTR szWindowName = L"Главное окно приложения";    //title for main application window

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
		WS_OVERLAPPEDWINDOW | WS_VISIBLE|WS_EX_TOPMOST,  //window style
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
	static UserInterface* userInterface = nullptr;
	switch (msg)
	{
		case WM_CREATE:
		{	
			userInterface = new UserInterface(hWnd);
			userInterface->activateAutentificationWindow();
			break;
		}
		case INF_DATABASE_CONNECTED:
		{
			userInterface->autorisationInDatabase();
			break;
		}
		case INF_OPERATION_COMPLETE:
		{
			if (wParam)
			{
				userInterface->freeForm(wParam);
			}
			break;
		}
		case WM_NOTIFY:
		{
			switch (((LPNMHDR)lParam)->code)
			{
				case NM_CLICK:
				{
					userInterface->processClickMessage(((LPNMHDR)lParam)->hwndFrom);
					break;
				}
				default:
				{
					break;
				}
			}

			//userInterface->OnNotifyProc()
			break;
		}
		case WM_COMMAND:
		{
			
			switch (LOWORD(wParam))
			{
			case ID_CHANGE_DOLLAR_RATE:
			{
				userInterface->activateChangeCurrencyRateForm(ID_CHANGE_DOLLAR_RATE);
				break;
			}
			case ID_CHANGE_EURO_RATE:
			{
				userInterface->activateChangeCurrencyRateForm(ID_CHANGE_EURO_RATE);
				break;
			}
			case ID_CASH_IN_BUTTON:
			{
				userInterface->activateCashInCashOutForm(ID_CASH_IN_BUTTON);
				break;
			}
			case ID_CASH_OUT_BUTTON:
			{
				userInterface->activateCashInCashOutForm(ID_CASH_OUT_BUTTON);
				break;
			}
			case ID_EXIT_FROM_CASINO_BUTTON:
			{
				userInterface->changeClientState(ID_EXIT_FROM_CASINO_BUTTON);
				break;
			}
			case ID_ENTRANCE_TO_CASINO_BUTTON:
			{
				userInterface->changeClientState(ID_ENTRANCE_TO_CASINO_BUTTON);
				break;
			}
			case ID_CASH_BTN:
			{
				userInterface->activateCashView();
				break;
			}
			case ID_CLIENT_BTN:
			{
				userInterface->activateClientsView();
				break;
			}
			case ID_EMPLOYEE_BTN:
			{
				userInterface->activateEmployeesView();
				break;
			}
			default:
			{
				break;
			}
			}
			break;
		}
		case WM_DESTROY:
		{
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

