#pragma once

#include <Windows.h>
#include "Constatnts.h"
#include "Client.h"
#include "Employee.h"

class ExtendedInfoAboutPerson
{
public:
	ExtendedInfoAboutPerson(HWND parent, int xPos, int yPos, int width, int height);
	~ExtendedInfoAboutPerson();

	void createClientExtendedInfoControls();
	void createEmployeeExtendedInfoControls();

	void setExtendedInfoAboutPerson(Person* selectedPerson);
	//void setExtendedInfoAboutPerson(Employee* selectedEmployee);
	void clearExtendedInfoWindow();
private:
	HWND m_parentOfExtInfoWindow;
	HWND m_extendedInfoWindow;

	HWND m_windowForNickname;
	HWND m_windowForLastname;
	HWND m_windowForFirstname;
	HWND m_windowForPatronymic;
	HWND m_windowForStatus;
	HWND m_windowForLastVisitDate;
	HWND m_windowForThisMounthVisitsCount;
	HWND m_windowForDropToday;
	HWND m_windowForResultToday;
	HWND m_windowForDropInCurrentMounth;
	HWND m_windowForResultInCurrentMounth;

	LONG_PTR m_ExtInfoWindowProc;
	static LRESULT CALLBACK ExtInfoWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT RealExtInfoWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	void destroyAllControls();
	void createInfoWindowWithDescription(int descriptionXPos, int descriptionYPos, int descriptionWidth, int descriptionHeight, TCHAR* descriptionText, HWND& windowWithInfo);
};

