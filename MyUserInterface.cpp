#include "MyUserInterface.h"


MyUserInterface::MyUserInterface(TCHAR* pRoleMember)
{
	extern LPWSTR szClassName;
	extern LPWSTR szWindowName;
	parentWnd = FindWindow(szClassName, szWindowName);
	if (lstrcmp(pRoleMember, L"CashDesk") == 0)
	{
		CreateInterfaceForCashier();
	}
}


MyUserInterface::~MyUserInterface()
{
}

void MyUserInterface::CreateInterfaceForCashier(void)
{
	CreateMainPanel(ID_CASHIER_PANEL);
	int  buttons[] = { ID_CASH_BTN, ID_CLIENT_BTN, ID_DILER_BTN };
	size_t len = sizeof(buttons) / sizeof(buttons[0]);
	CreateButtons(buttons,len);
}

void MyUserInterface::CreateMainPanel(UINT identify)
{
	ControlPanel panelForCashier;
	panelForCashier.CreateControlPanel(parentWnd, identify);	
}

void MyUserInterface::CreateButtons(int* buttons,size_t len)
{
	int btnHeight = 40;
	int btnWidth = 90;
	HWND panelWnd = GetDlgItem(parentWnd, ID_CASHIER_PANEL);
	RECT rc;
	GetClientRect(panelWnd, &rc);
	int btnXPos = rc.left + 5;
	int btnYPos = rc.top + 5;
	for (unsigned int i = 0; i <= len; i++)
	{
		switch (buttons[i])
		{
			case ID_CASH_BTN:
			{
				MyButton cashBtn;				
				cashBtn.CreateButton(panelWnd, ID_CASH_BTN, L"Касса", btnXPos, btnYPos, btnWidth, btnHeight);
				btnXPos += btnWidth + 5;
				break;
			}
			case ID_CLIENT_BTN:
			{
				MyButton clientBtn;
				clientBtn.CreateButton(panelWnd, ID_CLIENT_BTN, L"Клиенты", btnXPos, btnYPos, btnWidth, btnHeight);
				btnXPos += btnWidth + 5;
				break;
			}
			case ID_DILER_BTN:
			{
				MyButton dilerBtn;
				dilerBtn.CreateButton(panelWnd, ID_DILER_BTN, L"Дилера", btnXPos, btnYPos, btnWidth, btnHeight);
				btnXPos += btnWidth + 5;
				break;
			}
		}
	}		
}