#include "UserInterface.h"


UserInterface::UserInterface(HWND mainApplicationWindow)
{
	m_mainApplicationWindow = mainApplicationWindow;
	m_sqlConection = new CSqlFramework;
	m_autentification = nullptr;
	m_controlPanel = nullptr;
	m_views = new ApplicationViews(mainApplicationWindow);
	m_controls = nullptr;
	m_addClientToDatabaseForm = nullptr;
	m_cashInCashOutForm = nullptr;
	m_changeCurrencyRateForm = nullptr;
	m_dateInCasino = nullptr;
	m_casinoState = nullptr;
}


UserInterface::~UserInterface()
{
	if (m_sqlConection)
	{
		m_sqlConection->CloseConnection();
		delete m_sqlConection;
		m_sqlConection = nullptr;
	}
	if (m_autentification)
	{
		delete m_autentification;
		m_autentification = nullptr;
	}
	if (m_addClientToDatabaseForm)
	{
		delete m_addClientToDatabaseForm;
		m_addClientToDatabaseForm = nullptr;
	}
	if (m_controlPanel)
	{
		delete m_controlPanel;
		m_controlPanel = nullptr;
	}
	if (m_views)
	{
		delete m_views;
		m_views = nullptr;
	}
	if (m_controls)
	{
		delete m_controls;
		m_controls = nullptr;
	}
	if (m_cashInCashOutForm)
	{
		delete m_cashInCashOutForm;
		m_cashInCashOutForm = nullptr;
	}
	if (m_changeCurrencyRateForm)
	{
		delete m_changeCurrencyRateForm;
		m_changeCurrencyRateForm = nullptr;
	}
	if (m_dateInCasino)
	{
		m_dateInCasino = nullptr;
	}
	if (m_casinoState)
	{
		delete m_casinoState;
		m_casinoState = nullptr;
	}
}

void UserInterface::activateAutentificationWindow()
{
	m_autentification = new AutentificationForm(m_mainApplicationWindow, m_mainApplicationWindow, m_sqlConection);
}

void UserInterface::autorisationInDatabase()
{
	if (m_autentification)
	{

		delete m_autentification;
		m_autentification = nullptr;
	}

	AutorisationClass* autorisation = new AutorisationClass(m_sqlConection);
	TCHAR* roleName = autorisation->GetRoleOfCurrentUser();
	
	m_casinoState = new CasinoState(m_sqlConection);
	m_dateInCasino = m_casinoState->getDateInCasino();
	m_controlPanel = new ControlPanel(m_mainApplicationWindow, roleName, m_casinoState->getCasinoState());
	delete autorisation;
	autorisation = nullptr;
}


void UserInterface::processClickMessage(HWND hwndFrom)
{
	if (hwndFrom == m_views->getListHandle())
	{
		if (m_views->showInfoAboutSelectedPerson())
		{
			m_controls->enableButtonsIfSelectedPerson();
		}
		else
		{
			m_controls->disableButtonsIfNoSelectedPerson();
		}
	}
}

void UserInterface::createControlsAreaForViews()
{
	HWND list = m_views->getListHandle();
	RECT listRC;
	GetWindowRect(list, &listRC);
	POINT tmp;
	tmp.x = listRC.right;
	tmp.y = listRC.top;
	ScreenToClient(m_mainApplicationWindow, &tmp);

	RECT parentRc;
	GetClientRect(m_mainApplicationWindow, &parentRc);
	int xPos = tmp.x + offsetsBetweenWindow;
	int yPos = tmp.y;
	int width = parentRc.right - xPos - offsetsBetweenWindow;
	int height = (parentRc.bottom - parentRc.top) - heightOfControlPanelForApp - 2 * offsetsBetweenWindow;
	m_controls = new ControlsForViews(m_mainApplicationWindow, xPos, yPos, width, height,m_sqlConection);
}
void UserInterface::activateCashView()
{
	m_views->activateCashView(m_sqlConection);
	 
	if (!m_controls)
	{
		createControlsAreaForViews();
	}
	m_controls->createControlsForCashView();
}

void UserInterface::activateClientsView()
{
	m_views->activateClientsView(m_sqlConection);
	if (!m_controls)
	{
		createControlsAreaForViews();
	}
	m_controls->createControlsForClientsView();
}

void UserInterface::activateEmployeesView()
{
	m_views->activateEmployeesView(m_sqlConection);
	if (!m_controls)
	{
		createControlsAreaForViews();
	}
	m_controls->createControlsForEmployeesView();
}

void UserInterface::activateChangeCurrencyRateForm(UINT pressedBtnIdentifier)
{
	m_changeCurrencyRateForm = new ChangeCurrencyRateForm(m_mainApplicationWindow, m_mainApplicationWindow, m_controls->getInfoWindowForRate(pressedBtnIdentifier), pressedBtnIdentifier, m_sqlConection);
}
void UserInterface::activateCashInCashOutForm(UINT pressedBtnIdentifier)
{
	m_cashInCashOutForm = new CashInCashOutForm(m_mainApplicationWindow, m_mainApplicationWindow, pressedBtnIdentifier,m_views->getSelectedPerson(),m_sqlConection,m_dateInCasino);
}

void UserInterface::freeForm(UINT pressedBtnIdentifier)
{
	m_views->setFocusOnList();
	switch (pressedBtnIdentifier)
	{
	case ID_CHANGE_CURRENCY_RATE:
	{
		delete m_changeCurrencyRateForm;
		m_changeCurrencyRateForm = nullptr;
		break;
	}
	case INF_CASHIN_CASHOUT_COMPLETE:
	{
		delete m_cashInCashOutForm;
		m_cashInCashOutForm = nullptr;
	}
	default:
	{
		break;
	}
	}
}

void UserInterface::changeClientState(UINT exitOrEntranceBtnIdentifier)
{
	Person* selectedPerson = m_views->getSelectedPerson();
	int clientID = selectedPerson->getPersonId();
	TCHAR* sqlCommand = nullptr;
	switch (exitOrEntranceBtnIdentifier)
	{
		case ID_EXIT_FROM_CASINO_BUTTON:
		{
			int parameterArray[] = { clientID };
			sqlCommand = TEXT("UPDATE [dbo].[Clients] SET [ClientState] = 'False' WHERE (ClientID = ?)");
			SQLHANDLE statementHandle = m_sqlConection->ExecutePrepearedQuery(sqlCommand, parameterArray);
			m_sqlConection->FreeBinding(statementHandle);
			m_views->deletePersonFromList();
			m_views->clearInfoWindows();
			((Client*)selectedPerson)->setClientState(FALSE);
			break;
		}
		case ID_ENTRANCE_TO_CASINO_BUTTON:
		{
			if (!((Client*)selectedPerson)->getClientState())
			{
				TCHAR stringClientID[4];
				_itot_s(clientID, stringClientID, 4, 10);
				SQLTCHAR* parameterArray[] = { m_dateInCasino, stringClientID };
				sqlCommand = TEXT("UPDATE [dbo].[Clients] SET [ClientState] = 'True',[LastVisit] = ? WHERE (ClientID = ?)");
				SQLHANDLE statementHandle = m_sqlConection->ExecutePrepearedQuery(sqlCommand, parameterArray);
				m_sqlConection->FreeBinding(statementHandle);
				m_views->setFocusOnList();
				((Client*)selectedPerson)->setClientState(TRUE);
				((Client*)selectedPerson)->setLastVisit(m_dateInCasino);
			}
			else
			{
				MessageBox(m_mainApplicationWindow, TEXT("Клиент уже в казино"), TEXT("Информация"), MB_OK);
				m_views->setFocusOnList();
			}
			break;
		}
		default:
		{
			break;
		}
	}
}



