#pragma once
#include <Windows.h>
#include "Constants.h"
#include "Client.h"

class CExtPersonInfo
{
private:
	HWND parentWnd;
	HWND extentedInfoWnd;

	HWND descForLastname;
	HWND descForFirstname;
	HWND descForPatronymic;
	HWND descForBirthday;
	HWND descForStatus;
	HWND descForLastVisit;
	HWND descForVisitsInThisMounth;
	HWND descForAllVisits;
	HWND descForDropToday;
	HWND descForResultToday;
	HWND descForDropMonth;
	HWND descForResultMounth;
	HWND phoneNumbersWnd;
	HWND extInfoAboutPerson;

	HWND createStaticWithStaticDescription(int staticXPos, int staticYPos, int staticWidth, int staticHeight, TCHAR* staticText, UINT descriptionIdentifier);
public:
	CExtPersonInfo(HWND parent, UINT imageIdentifier);
	void showExtInfoWnd();
	void clearExtInfoWnd();
	void setExtInfoAboutPerson(Client* currentPerson);
	~CExtPersonInfo();
};

