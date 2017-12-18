#include "Client.h"


Client::Client()
{
	//set all pointers to not valid value
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
	FreeAllField();    //clear all field in class

	//Get info about client from vector
	auto iter = selectedClient->begin();
	nickname = *iter++;
	lastname = *iter++;
	firstname = *iter++;
	patronymicname = *iter;
	//init parameter array for query with parametr((index of parameter+1) in parameterArray = number of parameter in query)
	SQLTCHAR* parametrArray[4] = { nickname, lastname, firstname, patronymicname };
	//query with parameter, where parameter is ?
	SQLTCHAR* sqlCommand = TEXT("SELECT ImageLocation,ClientID FROM dbo.Clients WHERE (Nickname = ? AND Фамилия = ? AND Имя = ? AND Отчество = ?)");
	extern CSqlFramework* sqlODBC;                                                          //allocating in main.cpp for working with database
	SQLHANDLE statementHandle = sqlODBC->ExecutePrepearedQuery(sqlCommand, parametrArray);  //send query with parameter and parameter array to database
	Binding* pBinding = sqlODBC->GetBinding();                                              //get bindig with data after execute query

	//Fetching result to pBinding
	while (SQLFetch(statementHandle) == SQL_SUCCESS)
	{
		FillAllClientField(pBinding);   //fill all field of Client class
	}
	sqlODBC->FreeBinding(statementHandle);  //free all resource after working
	LoadMainInfo();                         //load info to client view
}

void  Client::FillAllClientField(Binding*pBinding)
{
	Binding* tempBinding = pBinding;    
	while (tempBinding)
	{
		if (_tcscmp(tempBinding->GetColumnName(), TEXT("ImageLocation")) == 0)   //if column name is "ImageLocation"
		{
			//save description to imageLocation 
			size_t len = _tcslen(tempBinding->GetDescription()) + 1;                  //get lenght of description
			imageLocation = new SQLTCHAR[len];                                        //allocate memory for saving
			memset(imageLocation, 0, len*sizeof(SQLTCHAR));                           //fill pointer by /0
			_tcscat_s(imageLocation, len, tempBinding->GetDescription());             //copy data from binding to imageLocation
			tempBinding = tempBinding->GetNextBinding();                              //set to next element for continue 
		}
		else
		{
			tempBinding = tempBinding->GetNextBinding();  //set to next element for continue
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
	extern LPTSTR szClassName;       //window class name of main window(init in main.cpp)
	extern LPTSTR szWindowName;      //title of main window(init in main.cpp)
	HWND mainWnd = FindWindow(szClassName, szWindowName);    //Get handler to main window
	if (imageLocation)      //If imageLocation is valid
	{
		HWND imageWnd = GetDlgItem(mainWnd, ID_IMAGE_WND);       //get window for image in client view
		if (_tcscmp(imageLocation, TEXT(" ")) == 0)  
		{
			//create standart bitmap and set it
			HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, TEXT("D:\\Clients\\Безымянный1.bmp"), IMAGE_BITMAP, imageWidth, imageHeight, LR_LOADFROMFILE);
			SendMessage(imageWnd, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);
		}
		else
		{
			//create bitmap from imageLocation and set it
			HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, imageLocation, IMAGE_BITMAP, imageWidth, imageHeight, LR_LOADFROMFILE);
			SendMessage(imageWnd, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);
			ShowWindow(imageWnd, SW_NORMAL);
			UpdateWindow(imageWnd);
		}
	}
}