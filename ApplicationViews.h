#pragma once

#include "ImageTemplate.h"
#include "ListView.h"
#include "Employee.h"
#include "ExtendedInfoAboutPerson.h"

class ApplicationViews
{
public:
	ApplicationViews(HWND parentForViews);
	~ApplicationViews();

	void activateCashView(CSqlFramework* sqlConnection);
	void activateClientsView(CSqlFramework* sqlConnection);
	void activateEmployeesView(CSqlFramework* sqlConnection);
	BOOL showInfoAboutSelectedPerson();
	void setFocusOnList();
	void deletePersonFromList();
	void clearInfoWindows();

	HWND getListHandle() const;
	Person* getSelectedPerson();
private:
	Person* m_selectedPerson;
	Client* m_selectedClient;
	Employee* m_selectedEmployee;
	HWND m_parentForViews;

	ImageTemplate* m_personPhoto;
	ExtendedInfoAboutPerson* m_extInfoWindow;
	ListView* m_listView;
};

