#include "InterfaceForRole.h"


CInterfaceForRole::CInterfaceForRole()
{
	extern LPTSTR szClassName;
	extern LPTSTR szWindowName;
	mainApplicationWnd = FindWindow(szClassName, szWindowName);
	pContolPanel = new ControlPanel;
	pContolPanel->CreateControlPanel(mainApplicationWnd, ID_CONTROL_PANEL_WND, contolPanelHeight);

	LPTSTR szClassNameOfClientArea = TEXT("ClientAreaClassWindow");
	WNDCLASSEX wcex;
	wcex.cbClsExtra = wcex.cbWndExtra = NULL;
	wcex.cbSize = sizeof(WNDCLASSEX);                                       //size of structure
	wcex.hbrBackground = static_cast<HBRUSH>(GetStockObject(LTGRAY_BRUSH)); //window background
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);                             //standart mouse pointer
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);                           //standart main icon app
	wcex.hIconSm = NULL;                                                    //standart small icon app
	wcex.hInstance = (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE);        //descriptor for main window application
	wcex.lpfnWndProc = ClientAreaProc;                                      //pointer to message processing function
	wcex.lpszClassName = szClassNameOfClientArea;                           //window class name
	wcex.lpszMenuName = NULL;                                               //no menu in window
	wcex.style = CS_HREDRAW | CS_VREDRAW;                                   //window style (horizontal and vertical redraw)

	//Register application window in OS Windows
	RegisterClassEx(&wcex);
	RECT mainRC;
	GetClientRect(mainApplicationWnd, &mainRC);
	int clientAreaXPos = mainRC.left;
	int clientAreaYPos = mainRC.top + contolPanelHeight;
	int clientAreaWidth = mainRC.right;
	int clientAreaHeight = mainRC.bottom - contolPanelHeight;

	clientArea = CreateWindow(szClassNameOfClientArea,                     //window class name
		                      NULL,                                        //title of main window
		                      WS_CHILD | WS_VISIBLE,                       //window style
		                      clientAreaXPos,                              //x position on desktop
		                      clientAreaYPos,                              //y position on desktop
		                      clientAreaWidth,                             //width of window
		                      clientAreaHeight,                            //height of window
							  mainApplicationWnd,                          //parent window - desktop
							  (HMENU)ID_CLIENT_AREA,                                      
		                      reinterpret_cast<HINSTANCE>(GetWindowLong(NULL, GWLP_HINSTANCE)), //descriptor for main window application
		                      NULL);
	pImageWnd = new ImageWnd(clientArea);
	pListView = new ListView(clientArea, ID_IMAGE_WND);
	pExtentedInfoAboutSelectedPerson = new CExtPersonInfo(clientArea, ID_IMAGE_WND);
	buttons = new CButtonsForViews(clientArea,ID_LISTVIEW_WND);
	auxiliaryWnd = new AuxiliaryWindows;
	currentPerson = nullptr;
}


CInterfaceForRole::~CInterfaceForRole()
{
	if (pContolPanel)
	{
		delete pContolPanel;
		pContolPanel = nullptr;
	}
	if (pImageWnd)
	{
		delete pImageWnd;
		pImageWnd = nullptr;
	}
	if (pListView)
	{
		delete pListView;
		pListView = nullptr;
	}
	if (currentPerson)
	{
		//delete currentPerson;
		currentPerson = nullptr;
	}
	if (pExtentedInfoAboutSelectedPerson)
	{
		delete pExtentedInfoAboutSelectedPerson;
		pExtentedInfoAboutSelectedPerson = nullptr;
	}
	if (buttons)
	{
		delete buttons;
		buttons = nullptr;
	}
	if (auxiliaryWnd)
	{
		delete auxiliaryWnd;
		auxiliaryWnd = nullptr;
	}
}

void CInterfaceForRole::createInterfaceForRole(TCHAR* roleName)
{
	if (_tcscmp(roleName, TEXT("CashDesk")) == 0)
	{
		pContolPanel->createButtonForCashDesk();
	}
	else
	{
		MessageBox(mainApplicationWnd, TEXT("Не существует подходящей роли!"), TEXT("Ошибка"), MB_OK);
	}
}



void CInterfaceForRole::activateClientView()
{
	pContolPanel->disableButton(ID_STATIC_CLIENT_BTN);
	pListView->GetDataFromDatabase(TEXT("select Nickname,Фамилия,Имя,Отчество from dbo.Clients"));
	pImageWnd->loadNullImage();
	pImageWnd->showImageWindow();
	pExtentedInfoAboutSelectedPerson->showExtInfoWnd();
	pExtentedInfoAboutSelectedPerson->clearExtInfoWnd();
	buttons->createClientViewButtons();
}

void CInterfaceForRole::activateCashView()
{
	pContolPanel->disableButton(ID_STATIC_CASH_BTN);
	pListView->GetDataFromDatabase(TEXT("select Nickname,Фамилия,Имя,Отчество from dbo.Clients where (ClientState = 1)"));
	pImageWnd->loadNullImage();
	pImageWnd->showImageWindow();
	pExtentedInfoAboutSelectedPerson->showExtInfoWnd();
	pExtentedInfoAboutSelectedPerson->clearExtInfoWnd();
	buttons->createCashViewButtons();
}
void CInterfaceForRole::activateEmployeesView()
{
	pContolPanel->disableButton(ID_STATIC_DILER_BTN);
	pListView->GetDataFromDatabase(TEXT("Select Lastname,Firstname,Patronymicname,Posts.Должность from dbo.Employees join Posts on Posts.PostID = Employees.PostID order BY Posts.Должность"));
	pImageWnd->loadNullImage();
	pImageWnd->showImageWindow();
	pExtentedInfoAboutSelectedPerson->showExtInfoWnd();
	pExtentedInfoAboutSelectedPerson->clearExtInfoWnd();
	buttons->createEmployeesViewButtons();
}

void CInterfaceForRole::loadInfoAboutSelectedPerson()
{	
	currentPerson = pListView->getSelectedClient();
	if (currentPerson)
	{
		pExtentedInfoAboutSelectedPerson->clearExtInfoWnd();
		currentPerson->GetInfoForCurrentClient();
		pImageWnd->loadPersonPhoto(currentPerson);
		pExtentedInfoAboutSelectedPerson->setExtInfoAboutPerson(currentPerson);
		buttons->enableButtonsIfPersonSelected();
	}
	else
	{
		pExtentedInfoAboutSelectedPerson->clearExtInfoWnd();
		pImageWnd->loadNullImage();
		buttons->disableButtonsIfNoSelected();
	}
}

void CInterfaceForRole::hideAllWindow()
{
	pContolPanel->hideControlPanel();
	ShowWindow(clientArea, FALSE);
}

void CInterfaceForRole::showAllWindow()
{
	pContolPanel->showControlPanel();
	ShowWindow(clientArea, TRUE);
}


void CInterfaceForRole::activateCashInCashOutWindow(UINT btnIdentifier)
{
	auxiliaryWnd->createCashInCashOutWindow(currentPerson, btnIdentifier);
}

void CInterfaceForRole::activateAddClientToDatabaseWindow()
{
	auxiliaryWnd->createAddNewClientWnd();
}

void CInterfaceForRole::setFocusOnListWindow()
{
	pListView->setFocusOnItem();
}

void CInterfaceForRole::changeClientState(UINT exitOrEntranceBtnIdentifier)
{
	currentPerson->changeClientState(exitOrEntranceBtnIdentifier);
	if (exitOrEntranceBtnIdentifier == ID_EXIT_FROM_CASINO_BTN)
	{
		pListView->deleteSelectedPerson();
		pExtentedInfoAboutSelectedPerson->clearExtInfoWnd();
		pImageWnd->loadNullImage();
		buttons->disableButtonsIfNoSelected();
	}
	else
	{
		pListView->setFocusOnItem();
	}
}

LRESULT CALLBACK CInterfaceForRole::ClientAreaProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	extern LPTSTR szClassName;
	extern LPTSTR szWindowName;
	HWND mainApplicationWnd = FindWindow(szClassName, szWindowName);
	switch (msg)
	{
	
	case WM_NOTIFY:
	{
		switch (((LPNMHDR)lParam)->code)
		{
		case NM_CLICK:    //left mouse button
		case NM_RCLICK:   //rigth mouse button
		{
			SendMessage(mainApplicationWnd, WM_LISTVIEW_CLICKED, 0, 0);
			break;
		}
		default:
			break;
		}
		break;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0);                 //send message to OS Windows about closing app
		break;
	}
	//processing other messages provide OS Windows
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}
