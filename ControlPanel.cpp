#include "ControlPanel.h"


ControlPanel::ControlPanel()
{
	WNDCLASSEX wcex;
	wcex.cbClsExtra = wcex.cbWndExtra = NULL;
	wcex.cbSize = sizeof(WNDCLASSEX);                                       //������ ���������
	wcex.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));  //��� ����
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);                             //��������� ��� ��������� ����
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);                           //��������� ����������� ������ ����������
	wcex.hIconSm = NULL;                                                    //����������� ������ �� ������
	wcex.hInstance = (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE);        //�������� ���������� ������ ����������
	wcex.lpfnWndProc = WndProc;                                             //��������� ������� ��� ��������� ��������� � ������� ����
	wcex.lpszClassName = L"ControlPanelWindow";                             //��� ������ ������ ����
	wcex.lpszMenuName = NULL;                                               //���� �����������
	wcex.style = CS_HREDRAW | CS_VREDRAW;                                   //��������� ����� ����������� ����(����������� �� �������� � �����������)

	RegisterClassEx(&wcex);
	
}


ControlPanel::~ControlPanel()
{
}


void ControlPanel::CreateControlPanel(HWND hWnd, UINT identify)
{
	identifyNum = identify;
	RECT rc;
	GetClientRect(hWnd, &rc);
	int xPos = rc.left;
	int yPos = rc.top;
	int width = rc.right - rc.left;
	int height = 50;
	HWND cPanelWnd = CreateWindow(L"ControlPanelWindow",
		                          L"",
		                          WS_CHILD | WS_VISIBLE,
		                          xPos,
		                          yPos,
		                          width,
		                          height,
		                          hWnd,
		                          HMENU(identify),
		                          (HINSTANCE)GetWindowLong(NULL, GWLP_HINSTANCE),
		                          NULL);

}

void ControlPanel::MoveMyWindow(HWND hWnd)
{
	HWND chWnd = GetDlgItem(hWnd, identifyNum);
	MoveWindow(chWnd, 70, 0, 800, 50, TRUE);
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static ClientView* clientView = nullptr;
	switch (msg)
	{
	case WM_LISTVIEW_CLICKED:
	{
		clientView->getInfoAboutSelectedClient();
		break;
	}
	case WM_COMMAND:
	{		
		switch (LOWORD(wParam))
		{		
			case ID_CASH_BTN:
			{	
				if (clientView)
				{
					clientView->DestroyAllClientViewWindow();
					delete clientView;
					clientView = nullptr;
				}
				break;
			}
			case ID_CLIENT_BTN:
			{	
				if (!clientView)
				{
					clientView = new ClientView;
					clientView->CreateClientViewWindows();
				}
				else
				{
					clientView->destroyAuxiliaryWindows();
					clientView->showAllWndForClientView();
				}
				break;
			}
			case ID_DILER_BTN:
			{
				if (clientView)
				{
					clientView->DestroyAllClientViewWindow();
					delete clientView;
					clientView = nullptr;
				}
				break;
			}
			case ID_ADD_NEW_CLIENT_BTN:
			{
				clientView->hideWndForClientView();
				clientView->InitAddClientWnd();
				break;
			}

			return 0;
		}
		break;
	}
	// ������� �� ��������� � ����������� ������ ���������
	case WM_DESTROY:
	{
		if (clientView)
		{
			delete clientView;
			clientView = nullptr;
		}
		DestroyWindow(hWnd);
		break;
	}
		//��������� ���� ��������� ��������� ������������ �� �� ���������
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam); //������ ������ ������� ���������, �������� ��� � ����� �����������
	}
	return 0;
}


