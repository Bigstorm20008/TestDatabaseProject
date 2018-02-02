#include "ApplicationViews.h"


ApplicationViews::ApplicationViews(HWND parentForViews)
{
	m_parentForViews = parentForViews;
	m_selectedPerson = nullptr;
	m_selectedClient = nullptr;
	m_selectedEmployee = nullptr;
	m_extInfoWindow = nullptr;
}


ApplicationViews::~ApplicationViews()
{
	if (m_selectedClient)
	{
		delete m_selectedClient;
		m_selectedClient = nullptr;
	}
	if (m_selectedEmployee)
	{
		delete m_selectedEmployee;
		m_selectedEmployee = nullptr;
	}
	if (m_personPhoto)
	{
		delete m_personPhoto;
		m_personPhoto = nullptr;
	}
	if (m_listView)
	{
		delete m_listView;
		m_listView = nullptr;
	}
	if (m_extInfoWindow)
	{
		delete m_extInfoWindow;
		m_extInfoWindow = nullptr;
	}
	
	
	m_selectedPerson = nullptr;
	
}


void ApplicationViews::activateCashView(CSqlFramework* sqlConnection)
{
	if (!m_personPhoto)
	{
		RECT mainRC;
		GetClientRect(m_parentForViews, &mainRC);
		RECT clientRectWithoutControlPanel;
		clientRectWithoutControlPanel.left = mainRC.left;
		clientRectWithoutControlPanel.right = mainRC.right;
		clientRectWithoutControlPanel.bottom = mainRC.bottom;
		clientRectWithoutControlPanel.top = mainRC.top + heightOfControlPanelForApp;

		int imageXPos = clientRectWithoutControlPanel.left + offsetsBetweenWindow;
		int imageYPos = clientRectWithoutControlPanel.top + offsetsBetweenWindow;
		int imageWidth = imageWidthForApplication;
		int imageHeight = imageHeightForApplication;
		TCHAR* defaultImageForPerson = TEXT("D:\\Clients\\defaultImage.bmp");

		//int imageXPos, int imageYPos, int imageWidth, int imageHeight, HWND parent, TCHAR* imageLocation
		m_personPhoto = new ImageTemplate(imageXPos, imageYPos, imageWidth, imageHeight, m_parentForViews, defaultImageForPerson);
	}
	if (!m_listView)
	{
		RECT mainRC;
		GetClientRect(m_parentForViews, &mainRC);
		RECT clientRectWithoutControlPanel;
		clientRectWithoutControlPanel.left = mainRC.left;
		clientRectWithoutControlPanel.right = mainRC.right;
		clientRectWithoutControlPanel.bottom = mainRC.bottom;
		clientRectWithoutControlPanel.top = mainRC.top + heightOfControlPanelForApp;

		int listXPos = imageWidthForApplication + 2 * offsetsBetweenWindow;
		int listYPos = clientRectWithoutControlPanel.top + offsetsBetweenWindow;
		int listWidth = listViewWidth;
		int listHeight = clientRectWithoutControlPanel.bottom - clientRectWithoutControlPanel.top - 2 * offsetsBetweenWindow;
		m_listView = new ListView(m_parentForViews, listXPos, listYPos, listWidth, listHeight, sqlConnection);
	}
	if (!m_extInfoWindow)
	{
		RECT mainRC;
		GetClientRect(m_parentForViews, &mainRC);
		RECT clientRectWithoutControlPanel;
		clientRectWithoutControlPanel.left = mainRC.left;
		clientRectWithoutControlPanel.right = mainRC.right;
		clientRectWithoutControlPanel.bottom = mainRC.bottom;
		clientRectWithoutControlPanel.top = mainRC.top + heightOfControlPanelForApp;

		int extInfoXPos = clientRectWithoutControlPanel.left + offsetsBetweenWindow;
		int extInfoYPos = clientRectWithoutControlPanel.top + imageHeightForApplication + 2*offsetsBetweenWindow;
		int extInfoWidth = imageWidthForApplication;
		int extInfoHeight = (clientRectWithoutControlPanel.bottom - clientRectWithoutControlPanel.top) - imageHeightForApplication - 3 * offsetsBetweenWindow;
		m_extInfoWindow = new ExtendedInfoAboutPerson(m_parentForViews, extInfoXPos, extInfoYPos, extInfoWidth, extInfoHeight);
	}
	TCHAR* sqlCommand = TEXT("select Nickname,Фамилия,Имя,Отчество from dbo.Clients where (ClientState = 1)");
	m_personPhoto->loadDefaultImage();
	m_listView->GetDataFromDatabase(sqlCommand);
	m_extInfoWindow->createClientExtendedInfoControls();
	if (!m_selectedClient)
	{
		m_selectedClient = new Client(sqlConnection);
		m_selectedPerson = m_selectedClient;
	}
	else
	{
		m_selectedPerson = m_selectedClient;
	}
}

void ApplicationViews::activateClientsView(CSqlFramework* sqlConnection)
{
	if (!m_personPhoto)
	{
		RECT mainRC;
		GetClientRect(m_parentForViews, &mainRC);
		RECT clientRectWithoutControlPanel;
		clientRectWithoutControlPanel.left = mainRC.left;
		clientRectWithoutControlPanel.right = mainRC.right;
		clientRectWithoutControlPanel.bottom = mainRC.bottom;
		clientRectWithoutControlPanel.top = mainRC.top + heightOfControlPanelForApp;

		int imageXPos = clientRectWithoutControlPanel.left + offsetsBetweenWindow;
		int imageYPos = clientRectWithoutControlPanel.top + offsetsBetweenWindow;
		int imageWidth = imageWidthForApplication;
		int imageHeight = imageHeightForApplication;
		TCHAR* defaultImageForPerson = TEXT("D:\\Clients\\defaultImage.bmp");

		//int imageXPos, int imageYPos, int imageWidth, int imageHeight, HWND parent, TCHAR* imageLocation
		m_personPhoto = new ImageTemplate(imageXPos, imageYPos, imageWidth, imageHeight, m_parentForViews, defaultImageForPerson);
	}
	if (!m_listView)
	{
		RECT mainRC;
		GetClientRect(m_parentForViews, &mainRC);
		RECT clientRectWithoutControlPanel;
		clientRectWithoutControlPanel.left = mainRC.left;
		clientRectWithoutControlPanel.right = mainRC.right;
		clientRectWithoutControlPanel.bottom = mainRC.bottom;
		clientRectWithoutControlPanel.top = mainRC.top + heightOfControlPanelForApp;

		int listXPos = imageWidthForApplication + 2 * offsetsBetweenWindow;
		int listYPos = clientRectWithoutControlPanel.top + offsetsBetweenWindow;
		int listWidth = listViewWidth;
		int listHeight = clientRectWithoutControlPanel.bottom - clientRectWithoutControlPanel.top - 2 * offsetsBetweenWindow;
		m_listView = new ListView(m_parentForViews, listXPos, listYPos, listWidth, listHeight, sqlConnection);
	}
	if (!m_extInfoWindow)
	{
		RECT mainRC;
		GetClientRect(m_parentForViews, &mainRC);
		RECT clientRectWithoutControlPanel;
		clientRectWithoutControlPanel.left = mainRC.left;
		clientRectWithoutControlPanel.right = mainRC.right;
		clientRectWithoutControlPanel.bottom = mainRC.bottom;
		clientRectWithoutControlPanel.top = mainRC.top + heightOfControlPanelForApp;

		int extInfoXPos = clientRectWithoutControlPanel.left + offsetsBetweenWindow;
		int extInfoYPos = clientRectWithoutControlPanel.top + imageHeightForApplication + 2 * offsetsBetweenWindow;
		int extInfoWidth = imageWidthForApplication;
		int extInfoHeight = (clientRectWithoutControlPanel.bottom - clientRectWithoutControlPanel.top) - imageHeightForApplication - 3 * offsetsBetweenWindow;
		m_extInfoWindow = new ExtendedInfoAboutPerson(m_parentForViews, extInfoXPos, extInfoYPos, extInfoWidth, extInfoHeight);
	}
	TCHAR* sqlCommand = TEXT("select Nickname,Фамилия,Имя,Отчество from dbo.Clients");
	m_personPhoto->loadDefaultImage();
	m_listView->GetDataFromDatabase(sqlCommand);
	m_extInfoWindow->createClientExtendedInfoControls();
	if (!m_selectedClient)
	{
		m_selectedClient = new Client(sqlConnection);
		m_selectedPerson = m_selectedClient;
	}
	else
	{
		m_selectedPerson = m_selectedClient;
	}
}

void ApplicationViews::activateEmployeesView(CSqlFramework* sqlConnection)
{
	if (!m_personPhoto)
	{
		RECT mainRC;
		GetClientRect(m_parentForViews, &mainRC);
		RECT clientRectWithoutControlPanel;
		clientRectWithoutControlPanel.left = mainRC.left;
		clientRectWithoutControlPanel.right = mainRC.right;
		clientRectWithoutControlPanel.bottom = mainRC.bottom;
		clientRectWithoutControlPanel.top = mainRC.top + heightOfControlPanelForApp;

		int imageXPos = clientRectWithoutControlPanel.left + offsetsBetweenWindow;
		int imageYPos = clientRectWithoutControlPanel.top + offsetsBetweenWindow;
		int imageWidth = imageWidthForApplication;
		int imageHeight = imageHeightForApplication;
		TCHAR* defaultImageForPerson = TEXT("D:\\Clients\\defaultImage.bmp");

		//int imageXPos, int imageYPos, int imageWidth, int imageHeight, HWND parent, TCHAR* imageLocation
		m_personPhoto = new ImageTemplate(imageXPos, imageYPos, imageWidth, imageHeight, m_parentForViews, defaultImageForPerson);
	}
	if (!m_listView)
	{
		RECT mainRC;
		GetClientRect(m_parentForViews, &mainRC);
		RECT clientRectWithoutControlPanel;
		clientRectWithoutControlPanel.left = mainRC.left;
		clientRectWithoutControlPanel.right = mainRC.right;
		clientRectWithoutControlPanel.bottom = mainRC.bottom;
		clientRectWithoutControlPanel.top = mainRC.top + heightOfControlPanelForApp;

		int listXPos = imageWidthForApplication + 2 * offsetsBetweenWindow;
		int listYPos = clientRectWithoutControlPanel.top + offsetsBetweenWindow;
		int listWidth = listViewWidth;
		int listHeight = clientRectWithoutControlPanel.bottom - clientRectWithoutControlPanel.top - 2 * offsetsBetweenWindow;
		m_listView = new ListView(m_parentForViews, listXPos, listYPos, listWidth, listHeight, sqlConnection);
	}
	if (!m_extInfoWindow)
	{
		RECT mainRC;
		GetClientRect(m_parentForViews, &mainRC);
		RECT clientRectWithoutControlPanel;
		clientRectWithoutControlPanel.left = mainRC.left;
		clientRectWithoutControlPanel.right = mainRC.right;
		clientRectWithoutControlPanel.bottom = mainRC.bottom;
		clientRectWithoutControlPanel.top = mainRC.top + heightOfControlPanelForApp;

		int extInfoXPos = clientRectWithoutControlPanel.left + offsetsBetweenWindow;
		int extInfoYPos = clientRectWithoutControlPanel.top + imageHeightForApplication + 2 * offsetsBetweenWindow;
		int extInfoWidth = imageWidthForApplication;
		int extInfoHeight = (clientRectWithoutControlPanel.bottom - clientRectWithoutControlPanel.top) - imageHeightForApplication - 3 * offsetsBetweenWindow;
		m_extInfoWindow = new ExtendedInfoAboutPerson(m_parentForViews, extInfoXPos, extInfoYPos, extInfoWidth, extInfoHeight);
	}
	TCHAR* sqlCommand = TEXT("Select Lastname,Firstname,Patronymicname,Posts.Должность from dbo.Employees join Posts on Posts.PostID = Employees.PostID order BY Posts.Должность");
	m_personPhoto->loadDefaultImage();
	m_listView->GetDataFromDatabase(sqlCommand);
	m_extInfoWindow->createEmployeeExtendedInfoControls();
	if (!m_selectedEmployee)
	{
		m_selectedEmployee = new Employee(sqlConnection);
		m_selectedPerson = m_selectedEmployee;
	}
	else
	{
		m_selectedPerson = m_selectedEmployee;
	}
}


BOOL ApplicationViews::showInfoAboutSelectedPerson()
{
	if (m_listView->getSelectedClient(*m_selectedPerson))
	{
		m_selectedPerson->getInfoForCurrentPerson(TEXT("27/01/2018"));
		m_personPhoto->setNewImageLocationAndLoadIt(m_selectedPerson->getImageLocation());
		m_extInfoWindow->setExtendedInfoAboutPerson(m_selectedPerson);
		return TRUE;
	}
	else
	{
		m_selectedPerson->FreeAllField();
		m_personPhoto->loadDefaultImage();
		m_extInfoWindow->clearExtendedInfoWindow();
		return FALSE;
	}
}

void ApplicationViews::clearInfoWindows()
{
	m_personPhoto->loadDefaultImage();
	m_extInfoWindow->clearExtendedInfoWindow();
}

HWND ApplicationViews::getListHandle() const
{
	return m_listView->getHandleOfList();
}

Person* ApplicationViews::getSelectedPerson()
{
	return m_selectedPerson;
}

void ApplicationViews::setFocusOnList()
{
	m_listView->setFocusOnItem();
}

void ApplicationViews::deletePersonFromList()
{
	m_listView->deleteSelectedPerson();
}