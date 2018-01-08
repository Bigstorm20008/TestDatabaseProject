#include "Client.h"


Client::Client()
{
	//set all pointers to not valid value
	nickname = nullptr;
	lastname = nullptr;
	firstname = nullptr;
	patronymicname = nullptr;
	imageLocation = nullptr;
	birthDay = nullptr;
	phoneNumbers = nullptr;
	//clientState = nullptr;
}


Client::~Client()
{
	FreeAllField();
}

void Client::FreeAllField()
{	
	if (nickname)
	{
		delete[]nickname;
		nickname = nullptr;
	}
	if (lastname)
	{
		delete[]lastname;
		lastname = nullptr;
	}
	if (firstname)
	{
		delete[]firstname;
		firstname = nullptr;
	}
	if (patronymicname)
	{
		delete[]patronymicname;
		patronymicname = nullptr;
	}
	if (imageLocation)
	{
		delete[]imageLocation;
		imageLocation = nullptr;
	}
	if (birthDay)
	{
		delete[]birthDay;
		birthDay = nullptr;
	}
	if (status)
	{
		delete[]status;
		status = nullptr;
	}
	if (phoneNumbers)
	{
		deleteAllPhoneNumbers();
		delete phoneNumbers;
		phoneNumbers = nullptr;
	}
	//if (clientState)
	//{
		//delete clientState;
		//clientState = nullptr;
	//}
}

void Client::getPhoneNumbersFromDatabase()
{
	
	SQLTCHAR* sqlCommand = TEXT("SELECT PhoneNumber FROM ClientsPhoneNumbers WHERE ClientID = ?");
	int parameterArray[] = {clientID};
	extern CSqlFramework* sqlODBC;                                                          //allocating in main.cpp for working with database
	SQLHANDLE statementHandle = sqlODBC->ExecutePrepearedQuery(sqlCommand, parameterArray);  //send query with parameter and parameter array to database
	size_t vectorLenght = 0;
	Binding* pBinding = sqlODBC->GetBinding();                                              //get bindig with data after execute query

	//Fetching result to pBinding
	if (phoneNumbers)
	{
		deleteAllPhoneNumbers();
		delete phoneNumbers;
		phoneNumbers = nullptr;
	}
	phoneNumbers = new std::vector<SQLTCHAR*>;
	while (SQLFetch(statementHandle) == SQL_SUCCESS)
	{
		Binding* tempBinding = pBinding;
		while (tempBinding)
		{
			size_t phoneLen = _tcslen(tempBinding->GetDescription()) + 1;
			SQLTCHAR* phoneNumber = new SQLTCHAR[phoneLen];
			memset(phoneNumber, 0, phoneLen*sizeof(SQLTCHAR));                           //fill pointer by /0
			_tcscat_s(phoneNumber, phoneLen, tempBinding->GetDescription());             //copy data from binding to imageLocation
			phoneNumbers->push_back(phoneNumber);
			tempBinding = tempBinding->GetNextBinding();
		}
	}
	sqlODBC->FreeBinding(statementHandle);  //free all resource after working
	if (phoneNumbers->empty())
	{
		delete phoneNumbers;
		phoneNumbers = nullptr;
	}
}
void Client::GetInfoForCurrentClient()
{
	
	//init parameter array for query with parametr((index of parameter+1) in parameterArray = number of parameter in query)
	SQLTCHAR* parametrArray[] = { nickname, lastname, firstname, patronymicname };
	//query with parameter, where parameter is ?
	SQLTCHAR* sqlCommand = TEXT("SELECT [ImageLocation],Clients.ClientID, [Status].Статус, ClientState, [Дата рождения] = (CASE WHEN [Дата рождения] IS NULL THEN '' ELSE CONVERT(varchar,[Дата рождения]) END) FROM dbo.Clients join [Status] on  [Status].StatusID = Clients.Статус WHERE (Nickname = ? AND Фамилия = ? AND Имя = ? AND Отчество = ?)");
	extern CSqlFramework* sqlODBC;                                                          //allocating in main.cpp for working with database
	SQLHANDLE statementHandle = sqlODBC->ExecutePrepearedQuery(sqlCommand, parametrArray);  //send query with parameter and parameter array to database
	Binding* pBinding = sqlODBC->GetBinding();                                              //get bindig with data after execute query

	//Fetching result to pBinding
	while (SQLFetch(statementHandle) == SQL_SUCCESS)
	{
		FillAllClientField(pBinding);   //fill all field of Client class
	}
	sqlODBC->FreeBinding(statementHandle);  //free all resource after working

	getPhoneNumbersFromDatabase();
	getCustomerFinancialStatistics();
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
			continue;
		}
		if (_tcscmp(tempBinding->GetColumnName(), TEXT("ClientState")) == 0)   //if column name is "ClientState"
		{
			if (_tcscmp(tempBinding->GetDescription(), TEXT("0")) == 0)
			{
				clientState = FALSE;
			}
			else
			{
				clientState = TRUE;
			}
			tempBinding = tempBinding->GetNextBinding();                              //set to next element for continue 
			continue;
		}
		if (_tcscmp(tempBinding->GetColumnName(), TEXT("ClientID")) == 0)
		{
			                
			clientID = tempBinding->getIntegerData();
			tempBinding = tempBinding->GetNextBinding();                              //set to next element for continue 
			continue;
		}
		if (_tcscmp(tempBinding->GetColumnName(), TEXT("Статус")) == 0)
		{
			size_t len = _tcslen(tempBinding->GetDescription()) + 1;                  //get lenght of description
			status = new SQLTCHAR[len];                                        //allocate memory for saving
			memset(status, 0, len*sizeof(SQLTCHAR));                           //fill pointer by /0
			_tcscat_s(status, len, tempBinding->GetDescription());             //copy data from binding to imageLocation
			tempBinding = tempBinding->GetNextBinding();                              //set to next element for continue 
			continue;
		}
		if (_tcscmp(tempBinding->GetColumnName(), TEXT("Дата рождения")) == 0)   //if column name is "ImageLocation"
		{
			//save description to birthday
			size_t len = _tcslen(tempBinding->GetDescription()) + 1;                  //get lenght of description
			if (len == 0)
			{
				birthDay = TEXT("");
				tempBinding = tempBinding->GetNextBinding();                              //set to next element for continue 
				continue;
			}
			else
			{
				birthDay = new SQLTCHAR[len];                                        //allocate memory for saving
				memset(birthDay, 0, len*sizeof(SQLTCHAR));                           //fill pointer by /0
				_tcscat_s(birthDay, len, tempBinding->GetDescription());             //copy data from binding to imageLocation
				tempBinding = tempBinding->GetNextBinding();                              //set to next element for continue 
				continue;
			}
		} 
		tempBinding = tempBinding->GetNextBinding();  //set to next element for continue
	}
}

void Client::changeClientState(UINT exitOrEntranceBtnIdentifier)
{
	extern CSqlFramework* sqlODBC;   //allocating in main.cpp for working with database
	//init parameter array for query with parametr((index of parameter+1) in parameterArray = number of parameter in query)
	SQLTCHAR* parametrArray[] = { nickname, lastname, firstname, patronymicname };
	//query with parameter, where parameter is ?
	if (exitOrEntranceBtnIdentifier == ID_EXIT_FROM_CASINO_BTN)
	{
		SQLTCHAR* sqlCommand = TEXT("UPDATE [dbo].[Clients] SET [ClientState] = 'False' WHERE (Nickname = ? AND Фамилия = ? AND Имя = ? AND Отчество = ?)");
		SQLHANDLE statementHandle = sqlODBC->ExecutePrepearedQuery(sqlCommand, parametrArray);  //send query with parameter and parameter array to database
		clientState = FALSE;
		sqlODBC->FreeBinding(statementHandle);
	}
	if (exitOrEntranceBtnIdentifier == ID_ENTRANCE_IN_CASINO_BTN)
	{
		if (clientState == TRUE)
		{
			MessageBox(NULL, TEXT("Клиент уже в казино"), TEXT("Информация"), MB_OK);
		}
		else
		{
			SQLTCHAR* sqlCommand = TEXT("UPDATE [dbo].[Clients] SET [ClientState] = 'True' WHERE (Nickname = ? AND Фамилия = ? AND Имя = ? AND Отчество = ?)");
			SQLHANDLE statementHandle = sqlODBC->ExecutePrepearedQuery(sqlCommand, parametrArray);  //send query with parameter and parameter array to database
			clientState = TRUE;
			sqlODBC->FreeBinding(statementHandle);
		}
	}
	
}


BOOL Client::addNewClientToDatabase(HWND infoFrom)
{
	HWND nicknameWnd = GetDlgItem(infoFrom, ID_EDITBOX_FOR_NICKNAME);
	nickname = GetDataFromEdit(nicknameWnd);
	if ((!nickname) || (_tcscmp(nickname, TEXT("")) == 0))
	{
		MessageBox(infoFrom, TEXT("Введите Nickname для нового клиента"), TEXT("Ошибка при добавлении клиента в БД"), MB_OK);
		return FALSE;
	}
	HWND imageLocWnd = GetDlgItem(infoFrom, ID_EDITBOX_FOR_IMAGE);
	//SendMessage(imageLocWnd, EM_SETREADONLY, (WPARAM)FALSE, 0);
	imageLocation = GetDataFromEdit(imageLocWnd);
	if ((!imageLocation) || (_tcscmp(imageLocation, TEXT("")) == 0))
	{
		MessageBox(infoFrom, TEXT("Выберите фотографию для нового клиента"), TEXT("Ошибка при добавлении клиента в БД"), MB_OK);
		return FALSE;
	}
	else
	{
		HWND lastNameWnd = GetDlgItem(infoFrom, ID_EDITBOX_FOR_LASTNAME);
		lastname = GetDataFromEdit(lastNameWnd);
		HWND firstnameWnd = GetDlgItem(infoFrom, ID_EDITBOX_FOR_FIRSTNAME);
		firstname = GetDataFromEdit(firstnameWnd);
		HWND patronymicWnd = GetDlgItem(infoFrom, ID_EDITBOX_FOR_PATRONYMIC);
		patronymicname = GetDataFromEdit(patronymicWnd);
		HWND birthDayWnd = GetDlgItem(infoFrom, ID_EDITBOX_FOR_BIRTHDAY);
		birthDay = GetDataFromEdit(birthDayWnd);
		if (_tcslen(birthDay) == 0)
		{
			delete[]birthDay;
			birthDay = nullptr;
		}
		SQLTCHAR* sqlCommand = TEXT("INSERT INTO [dbo].[Clients]([Nickname],[Фамилия],[Имя],[Отчество],[ImageLocation],[Дата рождения])VALUES(?,?,?,?,?,?)");
		SQLTCHAR* parametrArray[] = { nickname, lastname, firstname, patronymicname, imageLocation, birthDay };
		extern CSqlFramework* sqlODBC;
		SQLHANDLE statementHandle = sqlODBC->ExecutePrepearedQuery(sqlCommand, parametrArray);
		sqlODBC->FreeBinding(statementHandle);
		return TRUE;
	}
}
SQLTCHAR* Client::getImageLocation()
{
	if (_tcscmp(imageLocation, TEXT("")) == 0)
	{
		return nullptr;
	}
	else
	{
		return imageLocation;
	}
}

SQLTCHAR* Client::GetDataFromEdit(HWND textFrom)
{
	size_t len = GetWindowTextLength(textFrom);
	SQLTCHAR* destinationBuf = new SQLTCHAR[len+1];
	memset(destinationBuf, 0, (len + 1)*sizeof(SQLTCHAR));
	GetWindowText(textFrom, destinationBuf, len + 1);
	return destinationBuf;
}

void Client::saveDataFromList(TCHAR* columnName, TCHAR* dataFromList)
{
	if (_tcscmp(columnName, TEXT("Nickname")) == 0)
	{
		size_t len = _tcslen(dataFromList);
		nickname = new TCHAR[len + 1];
		memset(nickname, 0, (len + 1)*sizeof(TCHAR));
		_tcscat_s(nickname, len + 1, dataFromList);
	}

	if (_tcscmp(columnName, TEXT("Фамилия")) == 0)
	{
		size_t len = _tcslen(dataFromList);
		lastname = new TCHAR[len + 1];
		memset(lastname, 0, (len + 1)*sizeof(TCHAR));
		_tcscat_s(lastname, len + 1, dataFromList);
	}

	if (_tcscmp(columnName, TEXT("Имя")) == 0)
	{
		size_t len = _tcslen(dataFromList);
		firstname = new TCHAR[len + 1];
		memset(firstname, 0, (len + 1)*sizeof(TCHAR));
		_tcscat_s(firstname, len + 1, dataFromList);
	}
	
	if (_tcscmp(columnName, TEXT("Отчество")) == 0)
	{
		size_t len = _tcslen(dataFromList);
		patronymicname = new TCHAR[len + 1];
		memset(patronymicname, 0, (len + 1)*sizeof(TCHAR));
		_tcscat_s(patronymicname, len + 1, dataFromList);
	}
}

SQLTCHAR* Client::getNickname() const
{
	return nickname;
}
SQLTCHAR* Client::getLastname() const
{
	return lastname;
}

SQLTCHAR* Client::getFirstname() const
{
	return firstname;
}

SQLTCHAR* Client::getPatronymic() const
{
	return patronymicname;
}

SQLTCHAR* Client::getBirthDay() const
{
	return birthDay;
}

SQLTCHAR* Client::getStatus() const
{
	return status;
}

int Client::getDrop() const
{
	return drop;
}
int Client::getResult() const
{
	return result;
}

std::vector<SQLTCHAR*>* Client::getPhoneNumbers() const
{
	return phoneNumbers;
}
void Client::deleteAllPhoneNumbers()
{
	auto iter = phoneNumbers->begin();
	for (iter; iter < phoneNumbers->end();iter++)
	{
		delete *iter;
		*iter = nullptr;
	}
}

void Client::getCustomerFinancialStatistics()
{
	SQLTCHAR* sqlCommand = TEXT("SELECT SUM(AllCashIn.CashInValue)  FROM AllCashIn WHERE  ClientID = ?");

	TCHAR ClientID[20];
	_itot_s(clientID, ClientID, 20, 10);
	SQLTCHAR* parameterArray[] = { ClientID };
	
	extern CSqlFramework* sqlODBC;                                                          //allocating in main.cpp for working with database
	SQLHANDLE statementHandle = sqlODBC->ExecutePrepearedQuery(sqlCommand, parameterArray);  //send query with parameter and parameter array to database
	Binding* pBinding = sqlODBC->GetBinding();                                              //get bindig with data after execute query

	//Fetching result to pBinding

	while (SQLFetch(statementHandle) == SQL_SUCCESS)
	{
		Binding* tempBinding = pBinding;
		while (tempBinding)
		{
			this->cashInSum = tempBinding->getIntegerData();
			tempBinding = tempBinding->GetNextBinding();
		}
	}
	sqlODBC->FreeBinding(statementHandle);  //free all resource after working

	sqlCommand = TEXT("SELECT SUM(AllCashOut.CashOutValue)  FROM AllCashOut WHERE  ClientID = ?");
	statementHandle = sqlODBC->ExecutePrepearedQuery(sqlCommand, parameterArray);  //send query with parameter and parameter array to database
	pBinding = sqlODBC->GetBinding();                                              //get bindig with data after execute query

	//Fetching result to pBinding

	while (SQLFetch(statementHandle) == SQL_SUCCESS)
	{
		Binding* tempBinding = pBinding;
		while (tempBinding)
		{
			this->cashOutSum = tempBinding->getIntegerData();
			tempBinding = tempBinding->GetNextBinding();
		}
	}
	sqlODBC->FreeBinding(statementHandle);  //free all resource after working

	this->result = this->cashOutSum - this->cashInSum;

	sqlCommand = TEXT("SELECT [Drop].[DropValue] FROM [dbo].[Drop] WHERE ClientID = ?");
	statementHandle = sqlODBC->ExecutePrepearedQuery(sqlCommand, parameterArray);  //send query with parameter and parameter array to database
	pBinding = sqlODBC->GetBinding();                                              //get bindig with data after execute query

	//Fetching result to pBinding

	while (SQLFetch(statementHandle) == SQL_SUCCESS)
	{
		Binding* tempBinding = pBinding;
		while (tempBinding)
		{
			this->drop = tempBinding->getIntegerData();
			tempBinding = tempBinding->GetNextBinding();
		}
	}
	sqlODBC->FreeBinding(statementHandle);  //free all resource after working
}
/*Client& Client::operator=(const Client& client)
{
	delete[]nickname;
	nickname = new TCHAR[_tcslen(client.nickname) + 1];
	_tcscpy_s(this->nickname, _tcslen(client.nickname) + 1, client.nickname);

	delete[]lastname;
	lastname = new TCHAR[_tcslen(client.lastname) + 1];
	_tcscpy_s(this->lastname, _tcslen(client.lastname) + 1, client.lastname);

	delete[]firstname;
	firstname = new TCHAR[_tcslen(client.firstname) + 1];
	_tcscpy_s(this->firstname, _tcslen(client.firstname) + 1, client.firstname);

	delete[]patronymicname;
	patronymicname = new TCHAR[_tcslen(client.patronymicname) + 1];
	_tcscpy_s(this->patronymicname, _tcslen(client.patronymicname) + 1, client.patronymicname);

	return *this;
}*/