#include "ControlPanel.h"


ControlPanel::ControlPanel(HWND parentOfControlPanel, TCHAR* roleName)
{
	m_parentOfControlPanel = parentOfControlPanel;
	m_CashDeskButton = nullptr;
	m_ClentsButton = nullptr;
	m_EmployeesButton = nullptr;
	createControlPanel();
	createButtonsForRole(roleName);
}


ControlPanel::~ControlPanel()
{
	if (m_CashDeskButton)
	{
		delete m_CashDeskButton;
		m_CashDeskButton = nullptr;
	}
	if (m_ClentsButton)
	{
		delete m_ClentsButton;
		m_ClentsButton = nullptr;
	}
	if (m_EmployeesButton)
	{
		delete m_EmployeesButton;
		m_EmployeesButton = nullptr;
	}
}

void ControlPanel::createControlPanel()
{
	RECT parentRC;
	GetClientRect(m_parentOfControlPanel, &parentRC);
	int xPos = parentRC.left;
	int yPos = parentRC.top;
	int controlPanelWidth = parentRC.right - parentRC.left;
	int controlPanelHeight = heightOfControlPanelForApp;

	WNDCLASSEX wc;
	wc.cbClsExtra = wc.cbWndExtra = 0;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = NULL;
	wc.hIconSm = NULL;
	wc.hInstance = (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE);
	wc.lpfnWndProc = ControlPanel::ControlPanelProc;
	wc.lpszClassName = TEXT("ControlPanelWindow");
	wc.lpszMenuName = NULL;
	wc.style = 0;

	RegisterClassEx(&wc);

	m_controlPanelWnd = CreateWindow(wc.lpszClassName,
		                             NULL,
		                             WS_CHILD | WS_VISIBLE,
		                             xPos, yPos,
		                             controlPanelWidth, controlPanelHeight,
		                             m_parentOfControlPanel,
		                             NULL,
		                             (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
		                             this);
}


void ControlPanel::createButtonsForRole(TCHAR* roleName)
{
	if (_tcscmp(roleName, TEXT("CashDesk")) == 0)
	{
		createButtonsForCashier();
	}
}

void ControlPanel::createCashDeskButton(int& xPos, int& yPos)
{
	m_CashDeskButton = new ButtonTemplate;
	int buttonWidth = 100;
	int buttonHeight = 40;
	TCHAR* bitmapLocationForDisabledButton = TEXT("D:\\myProjects\\TestWindowClass\\ButtonsBitmap\\CashButton(disable).bmp");
	TCHAR* bitmapLocationForMouseMove = TEXT("D:\\myProjects\\TestWindowClass\\ButtonsBitmap\\CashButton(mousemove).bmp");
	TCHAR* bitmapLocationForMouseLeave = TEXT("D:\\myProjects\\TestWindowClass\\ButtonsBitmap\\CashButton(mouseleave).bmp");
	m_CashDeskButton->createButton(xPos, yPos, buttonWidth, buttonHeight, m_controlPanelWnd, ID_CASH_BTN, bitmapLocationForMouseMove, bitmapLocationForMouseLeave, bitmapLocationForDisabledButton);
	xPos += buttonWidth + offsetsBetweenWindow;
}

void ControlPanel::createClientsButton(int& xPos, int& yPos)
{
	m_ClentsButton = new ButtonTemplate;
	int buttonWidth = 100;
	int buttonHeight = 40;
	TCHAR* bitmapLocationForDisabledButton = TEXT("D:\\myProjects\\TestWindowClass\\ButtonsBitmap\\ClientButton(disable).bmp");
	TCHAR* bitmapLocationForMouseMove = TEXT("D:\\myProjects\\TestWindowClass\\ButtonsBitmap\\ClientButton(mousemove).bmp");
	TCHAR* bitmapLocationForMouseLeave = TEXT("D:\\myProjects\\TestWindowClass\\ButtonsBitmap\\ClientButton(mouseleave).bmp");
	m_ClentsButton->createButton(xPos, yPos, buttonWidth, buttonHeight, m_controlPanelWnd, ID_CLIENT_BTN, bitmapLocationForMouseMove, bitmapLocationForMouseLeave, bitmapLocationForDisabledButton);
	xPos += buttonWidth + offsetsBetweenWindow;
}

void ControlPanel::createEmployeesButton(int& xPos, int& yPos)
{
	m_EmployeesButton = new ButtonTemplate;
	int buttonWidth = 100;
	int buttonHeight = 40;
	TCHAR* bitmapLocationForDisabledButton = TEXT("D:\\myProjects\\TestWindowClass\\ButtonsBitmap\\EmployBtn(disable).bmp");
	TCHAR* bitmapLocationForMouseMove = TEXT("D:\\myProjects\\TestWindowClass\\ButtonsBitmap\\EmployBtn(mousemove).bmp");
	TCHAR* bitmapLocationForMouseLeave = TEXT("D:\\myProjects\\TestWindowClass\\ButtonsBitmap\\EmployBtn(mouseleave).bmp");
	m_EmployeesButton->createButton(xPos, yPos, buttonWidth, buttonHeight, m_controlPanelWnd, ID_EMPLOYEE_BTN, bitmapLocationForMouseMove, bitmapLocationForMouseLeave, bitmapLocationForDisabledButton);
	xPos += buttonWidth + offsetsBetweenWindow;
}

void ControlPanel::createButtonsForCashier()
{
	RECT controlPanelRC;
	GetClientRect(m_controlPanelWnd, &controlPanelRC);
	int xPos = controlPanelRC.left + offsetsBetweenWindow;
	int yPos = controlPanelRC.top + offsetsBetweenWindow;
	createCashDeskButton(xPos, yPos);
	createClientsButton(xPos, yPos);
	createEmployeesButton(xPos, yPos);
}

void ControlPanel::disableButtonOnControlPanel(UINT butonIdentifier)
{
	switch (butonIdentifier)
	{
		case ID_CASH_BTN:
		{
			m_CashDeskButton->disableButton();
			if (m_ClentsButton)
			{
				m_ClentsButton->enableButton();
			}
			if (m_EmployeesButton)
			{
				m_EmployeesButton->enableButton();
			}
			break;
		}
		case ID_CLIENT_BTN:
		{
			m_ClentsButton->disableButton();
			if (m_CashDeskButton)
			{
				m_CashDeskButton->enableButton();
			}
			if (m_EmployeesButton)
			{
				m_EmployeesButton->enableButton();
			}
			break;
		}
		case ID_EMPLOYEE_BTN:
		{
			m_EmployeesButton->disableButton();
			if (m_CashDeskButton)
			{
				m_CashDeskButton->enableButton();
			}
			if (m_ClentsButton)
			{
				m_ClentsButton->enableButton();
			}
			break;
		}
		default:
		{
			break;
		}
	}
}

LRESULT CALLBACK ControlPanel::ControlPanelProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	switch (msg)
	{
		case WM_CREATE:
		{
			LPCREATESTRUCT lpcs;
			lpcs = (LPCREATESTRUCT)lParam;
			SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)lpcs->lpCreateParams);
			return 0;
		}
		default:
		{
			ControlPanel* controlPanel = NULL;
			controlPanel = (ControlPanel*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

			if (controlPanel != NULL)
			{
				return controlPanel->RealControlPanelProc(hWnd, msg, wParam, lParam);
			}
			else
			{
				return DefWindowProc(hWnd, msg, wParam, lParam);
			}
		}

	}
}

LRESULT ControlPanel::RealControlPanelProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
				case ID_CASH_BTN:
				{
					disableButtonOnControlPanel(ID_CASH_BTN);
					SendMessage(m_parentOfControlPanel, WM_COMMAND, ID_CASH_BTN, 0);
					break;
				}
				case ID_CLIENT_BTN:
				{
					disableButtonOnControlPanel(ID_CLIENT_BTN);
					SendMessage(m_parentOfControlPanel, WM_COMMAND, ID_CLIENT_BTN, 0);
					break;
				}
				case ID_EMPLOYEE_BTN:
				{
					disableButtonOnControlPanel(ID_EMPLOYEE_BTN);
					SendMessage(m_parentOfControlPanel, WM_COMMAND, ID_EMPLOYEE_BTN, 0);
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
			DestroyWindow(hWnd);
			break;
		}
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

