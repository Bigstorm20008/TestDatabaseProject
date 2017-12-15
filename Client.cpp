#include "Client.h"


Client::Client()
{
	nickname = nullptr;
	lastname = nullptr;
	firstname = nullptr;
	imageLocation = nullptr;
}


Client::~Client()
{
	FreeAllField();
}

void Client::FreeAllField()
{	
		nickname = nullptr;	
		lastname = nullptr;	
		firstname = nullptr;	
		patronymicname = nullptr;	
		if (imageLocation)
		{
			delete[]imageLocation;
			imageLocation = nullptr;
		}
}

void Client::GetInfoForCurrentClient(std::vector<SQLTCHAR*>* selectedClient)
{
	FreeAllField();
	auto iter = selectedClient->begin();
	nickname = *iter++;
	lastname = *iter++;
	firstname = *iter++;
	patronymicname = *iter;
	SQLTCHAR* parametrArray[4] = { nickname, lastname, firstname, patronymicname };
	SQLTCHAR* sqlCommand = TEXT("SELECT ImageLocation,ClientID FROM dbo.Clients WHERE (Nickname = ? AND Фамилия = ? AND Имя = ? AND Отчество = ?)");
	extern CSqlFramework* sqlODBC;
	SQLHANDLE statementHandle = sqlODBC->ExecutePrepearedQuery(sqlCommand, parametrArray);
	Binding* pBinding = sqlODBC->GetBinding();
	while (SQLFetch(statementHandle) == SQL_SUCCESS)
	{
		FillAllClientField(pBinding);
	}
	sqlODBC->FreeBinding(statementHandle);
	LoadMainInfo();
}

void  Client::FillAllClientField(Binding*pBinding)
{
	Binding* tempBinding = pBinding;
	while (tempBinding)
	{
		if (_tcscmp(tempBinding->GetColumnName(), TEXT("ImageLocation")) == 0)
		{
			size_t len = _tcslen(tempBinding->GetDescription()) + 1;
			imageLocation = new SQLTCHAR[len];
			memset(imageLocation, 0, len*sizeof(SQLTCHAR));
			_tcscat_s(imageLocation, len, tempBinding->GetDescription());
			tempBinding = tempBinding->GetNextBinding();
		}
		else
		{
			tempBinding = tempBinding->GetNextBinding();
		}
		/*if (_tcscmp(tempBinding->GetColumnName(), TEXT("ClientID")) == 0)
		{
			clientID = (int)*(tempBinding->GetDescription());
			tempBinding = tempBinding->GetNextBinding();
		}*/
	}
}

void Client::LoadMainInfo()
{
	extern LPTSTR szClassName;
	extern LPTSTR szWindowName;
	HWND mainWnd = FindWindow(szClassName, szWindowName);
	if (imageLocation)
	{
		HWND imageWnd = GetDlgItem(mainWnd, ID_IMAGE_WND);
		if (_tcscmp(imageLocation, TEXT(" ")) == 0)
		{
			HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, TEXT("D:\\Clients\\Безымянный1.bmp"), IMAGE_BITMAP, imageWidth, imageHeight, LR_LOADFROMFILE);
			SendMessage(imageWnd, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);
		}
		else
		{
			HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, imageLocation, IMAGE_BITMAP, imageWidth, imageHeight, LR_LOADFROMFILE);
			SendMessage(imageWnd, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);
			ShowWindow(imageWnd, SW_NORMAL);
			UpdateWindow(imageWnd);
		}
	}
}