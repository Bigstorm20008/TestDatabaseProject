#include "Client.h"


Client::Client(CSqlFramework* sqlConnection)
	:Person(sqlConnection)
{
	//set all pointers to not valid value
	m_nickname = nullptr;
	m_lastname = nullptr;
	m_firstname = nullptr;
	m_patronymicname = nullptr;
	m_imageLocation = nullptr;
	m_birthDay = nullptr;
	m_phoneNumbers = nullptr;
	m_lastVisit = nullptr;
	m_registrationDate = nullptr;
}


Client::~Client()
{
	FreeAllField();
}

void Client::FreeAllField()
{	
	if (m_nickname)
	{
		delete[]m_nickname;
		m_nickname = nullptr;
	}
	if (m_lastname)
	{
		delete[]m_lastname;
		m_lastname = nullptr;
	}
	if (m_firstname)
	{
		delete[]m_firstname;
		m_firstname = nullptr;
	}
	if (m_patronymicname)
	{
		delete[]m_patronymicname;
		m_patronymicname = nullptr;
	}
	if (m_imageLocation)
	{
		delete[]m_imageLocation;
		m_imageLocation = nullptr;
	}
	if (m_birthDay)
	{
		delete[]m_birthDay;
		m_birthDay = nullptr;
	}
	if (m_status)
	{
		delete[]m_status;
		m_status = nullptr;
	}
	if (m_phoneNumbers)
	{
		deleteAllPhoneNumbers();
		delete m_phoneNumbers;
		m_phoneNumbers = nullptr;
	}
	if (m_lastVisit)
	{
		delete[]m_lastVisit;
		m_lastVisit = nullptr;
	}
	if (m_registrationDate)
	{
		delete[]m_registrationDate;
		m_registrationDate = nullptr;
	}
}


/*void Client::cashIn(HWND infoFrom, TCHAR* currentDate)
{
	HWND dollarEditWnd = GetDlgItem(infoFrom, ID_EDITBOX_FOR_DOLLARS_VALUE);
	size_t len = GetWindowTextLength(dollarEditWnd) + 1;
	TCHAR* dollarValue = new TCHAR[len];
	memset(dollarValue, 0, len*sizeof(TCHAR));
	GetWindowText(dollarEditWnd, dollarValue, len);

	HWND euroEditWnd = GetDlgItem(infoFrom, ID_EDITBOX_FOR_EURO_VALUE);
	len = GetWindowTextLength(euroEditWnd) + 1;
	TCHAR* euroValue = new TCHAR[len];
	memset(euroValue, 0, len*sizeof(TCHAR));
	GetWindowText(euroEditWnd, euroValue, len);

	HWND grivnaEditWnd = GetDlgItem(infoFrom, ID_EDITBOX_FOR_GRIVNA_VALUE);
	len = GetWindowTextLength(grivnaEditWnd) + 1;
	TCHAR* grivnaValue = new TCHAR[len];
	memset(grivnaValue, 0, len*sizeof(TCHAR));
	GetWindowText(grivnaEditWnd, grivnaValue, len);

	CurrencyExchange* exchange = new CurrencyExchange;

	int sum = _tstof(dollarValue) + exchange->convertEurToUsd(_tstof(euroValue)) + exchange->convertUahToUsd(_tstof(grivnaValue));
	//TCHAR stringConvertedValue[MAX_PATH];
	//TCHAR* format = TEXT("%.*f");
	//_stprintf_s(stringConvertedValue, format, 2, result);

	SQLTCHAR* sqlCommand = TEXT("INSERT INTO [dbo].[AllCashIn] ([ClientID],[CashInValue]) VALUES (?,?)");
	int parameterArray[] = { clientID, sum };
	extern CSqlFramework* sqlODBC;  
	SQLHANDLE statementHandle = sqlODBC->ExecutePrepearedQuery(sqlCommand, parameterArray);
	sqlODBC->FreeBinding(statementHandle);

	getCustomerFinancialStatistics(currentDate);

	delete[] dollarValue;
	dollarValue = nullptr;
	delete[]euroValue;
	euroValue = nullptr;
	delete[]grivnaValue;
	grivnaValue = nullptr;
	delete exchange;
	exchange = nullptr;
}

void Client::cashOut(HWND infoFrom, TCHAR* currentDate)
{
	HWND dollarEditWnd = GetDlgItem(infoFrom, ID_EDITBOX_FOR_DOLLARS_VALUE);
	size_t len = GetWindowTextLength(dollarEditWnd) + 1;
	TCHAR* dollarValue = new TCHAR[len];
	memset(dollarValue, 0, len*sizeof(TCHAR));
	GetWindowText(dollarEditWnd, dollarValue, len);

	HWND euroEditWnd = GetDlgItem(infoFrom, ID_EDITBOX_FOR_EURO_VALUE);
	len = GetWindowTextLength(euroEditWnd) + 1;
	TCHAR* euroValue = new TCHAR[len];
	memset(euroValue, 0, len*sizeof(TCHAR));
	GetWindowText(euroEditWnd, euroValue, len);

	HWND grivnaEditWnd = GetDlgItem(infoFrom, ID_EDITBOX_FOR_GRIVNA_VALUE);
	len = GetWindowTextLength(grivnaEditWnd) + 1;
	TCHAR* grivnaValue = new TCHAR[len];
	memset(grivnaValue, 0, len*sizeof(TCHAR));
	GetWindowText(grivnaEditWnd, grivnaValue, len);

	CurrencyExchange* exchange = new CurrencyExchange;

	int sum = _tstof(dollarValue) + exchange->convertEurToUsd(_tstof(euroValue)) + exchange->convertUahToUsd(_tstof(grivnaValue));
	//TCHAR stringConvertedValue[MAX_PATH];
	//TCHAR* format = TEXT("%.*f");
	//_stprintf_s(stringConvertedValue, format, 2, result);

	SQLTCHAR* sqlCommand = TEXT("INSERT INTO [dbo].[AllCashOut] ([ClientID],[CashOutValue]) VALUES (?,?)");
	int parameterArray[] = { clientID, sum };
	extern CSqlFramework* sqlODBC;
	SQLHANDLE statementHandle = sqlODBC->ExecutePrepearedQuery(sqlCommand, parameterArray);
	sqlODBC->FreeBinding(statementHandle);
	getCustomerFinancialStatistics(currentDate);

	delete[] dollarValue;
	dollarValue = nullptr;
	delete[]euroValue;
	euroValue = nullptr;
	delete[]grivnaValue;
	grivnaValue = nullptr;
	delete exchange;
	exchange = nullptr;
}*/


void Client::getInfoForCurrentPerson(SQLTCHAR* currentDay)
{
	
	//init parameter array for query with parametr((index of parameter+1) in parameterArray = number of parameter in query)
	SQLTCHAR* parametrArray[] = { m_nickname, m_lastname, m_firstname, m_patronymicname };
	//query with parameter, where parameter is ?
	SQLTCHAR* sqlCommand = TEXT("SELECT [ImageLocation],Clients.ClientID, [Status].Статус, ClientState, LastVisit = FORMAT([LastVisit], 'dd/MM/yyyy'), [Дата рождения] = (CASE WHEN [Дата рождения] IS NULL THEN '' ELSE CONVERT(varchar,[Дата рождения]) END) FROM dbo.Clients join [Status] on  [Status].StatusID = Clients.Статус WHERE (Nickname = ? AND Фамилия = ? AND Имя = ? AND Отчество = ?)");
                                                         //allocating in main.cpp for working with database
	SQLHANDLE statementHandle = m_sqlConnection->ExecutePrepearedQuery(sqlCommand, parametrArray);  //send query with parameter and parameter array to database
	Binding* pBinding = m_sqlConnection->GetBinding();                                              //get bindig with data after execute query

	//Fetching result to pBinding
	while (SQLFetch(statementHandle) == SQL_SUCCESS)
	{
		fillAllPersonField(pBinding);   //fill all field of Client class
	}
	m_sqlConnection->FreeBinding(statementHandle);  //free all resource after working

	getPhoneNumbersFromDatabase(TEXT("SELECT PhoneNumber FROM ClientsPhoneNumbers WHERE ClientID = ?"));
	//getCustomerFinancialStatistics(currentDay);
}

void  Client::fillAllPersonField(Binding*pBinding)
{
	Binding* tempBinding = pBinding;    
	while (tempBinding)
	{
		if (_tcscmp(tempBinding->GetColumnName(), TEXT("ImageLocation")) == 0)   //if column name is "ImageLocation"
		{
			//save description to imageLocation 
			size_t len = _tcslen(tempBinding->GetDescription()) + 1;                  //get lenght of description
			m_imageLocation = new SQLTCHAR[len];                                        //allocate memory for saving
			memset(m_imageLocation, 0, len*sizeof(SQLTCHAR));                           //fill pointer by /0
			_tcscat_s(m_imageLocation, len, tempBinding->GetDescription());             //copy data from binding to imageLocation
			tempBinding = tempBinding->GetNextBinding();                              //set to next element for continue 
			continue;
		}
		if (_tcscmp(tempBinding->GetColumnName(), TEXT("ClientState")) == 0)   //if column name is "ClientState"
		{
			if (_tcscmp(tempBinding->GetDescription(), TEXT("0")) == 0)
			{
				m_clientState = FALSE;
			}
			else
			{
				m_clientState = TRUE;
			}
			tempBinding = tempBinding->GetNextBinding();                              //set to next element for continue 
			continue;
		}
		if (_tcscmp(tempBinding->GetColumnName(), TEXT("ClientID")) == 0)
		{
			                
			m_personID = tempBinding->getIntegerData();
			tempBinding = tempBinding->GetNextBinding();                              //set to next element for continue 
			continue;
		}
		if (_tcscmp(tempBinding->GetColumnName(), TEXT("Статус")) == 0)
		{
			size_t len = _tcslen(tempBinding->GetDescription()) + 1;                  //get lenght of description
			m_status = new SQLTCHAR[len];                                        //allocate memory for saving
			memset(m_status, 0, len*sizeof(SQLTCHAR));                           //fill pointer by /0
			_tcscat_s(m_status, len, tempBinding->GetDescription());             //copy data from binding to imageLocation
			tempBinding = tempBinding->GetNextBinding();                              //set to next element for continue 
			continue;
		}
		if (_tcscmp(tempBinding->GetColumnName(), TEXT("Дата рождения")) == 0)   //if column name is "ImageLocation"
		{
			//save description to birthday
			size_t len = _tcslen(tempBinding->GetDescription()) + 1;                  //get lenght of description
			if (len == 0)
			{
				m_birthDay = TEXT("");
				tempBinding = tempBinding->GetNextBinding();                              //set to next element for continue 
				continue;
			}
			else
			{
				m_birthDay = new SQLTCHAR[len];                                        //allocate memory for saving
				memset(m_birthDay, 0, len*sizeof(SQLTCHAR));                           //fill pointer by /0
				_tcscat_s(m_birthDay, len, tempBinding->GetDescription());             //copy data from binding to imageLocation
				tempBinding = tempBinding->GetNextBinding();                              //set to next element for continue 
				continue;
			}
		} 
		if (_tcscmp(tempBinding->GetColumnName(), TEXT("LastVisit")) == 0)
		{
			size_t len = _tcslen(tempBinding->GetDescription()) + 1;                  
			m_lastVisit = new SQLTCHAR[len];                                        
			memset(m_lastVisit, 0, len*sizeof(SQLTCHAR));                           
			_tcscat_s(m_lastVisit, len, tempBinding->GetDescription());             
			tempBinding = tempBinding->GetNextBinding();                              
			continue;
		}
		tempBinding = tempBinding->GetNextBinding();  //set to next element for continue
	}
}

/*void Client::changeClientState(UINT exitOrEntranceBtnIdentifier)
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
}*/


/*SQLTCHAR* Client::GetDataFromEdit(HWND textFrom)
{
	size_t len = GetWindowTextLength(textFrom);
	SQLTCHAR* destinationBuf = new SQLTCHAR[len+1];
	memset(destinationBuf, 0, (len + 1)*sizeof(SQLTCHAR));
	GetWindowText(textFrom, destinationBuf, len + 1);
	return destinationBuf;
}*/

void Client::saveDataFromList(TCHAR* columnName, TCHAR* dataFromList)
{
	if (_tcscmp(columnName, TEXT("Nickname")) == 0)
	{
		size_t len = _tcslen(dataFromList);
		m_nickname = new TCHAR[len + 1];
		memset(m_nickname, 0, (len + 1)*sizeof(TCHAR));
		_tcscat_s(m_nickname, len + 1, dataFromList);
	}

	if ((_tcscmp(columnName, TEXT("Фамилия")) == 0) || (_tcscmp(columnName, TEXT("Lastname")) == 0))
	{
		size_t len = _tcslen(dataFromList);
		m_lastname = new TCHAR[len + 1];
		memset(m_lastname, 0, (len + 1)*sizeof(TCHAR));
		_tcscat_s(m_lastname, len + 1, dataFromList);
	}

	if ((_tcscmp(columnName, TEXT("Имя")) == 0) || (_tcscmp(columnName, TEXT("Firstname")) == 0))
	{
		size_t len = _tcslen(dataFromList);
		m_firstname = new TCHAR[len + 1];
		memset(m_firstname, 0, (len + 1)*sizeof(TCHAR));
		_tcscat_s(m_firstname, len + 1, dataFromList);
	}
	
	if ((_tcscmp(columnName, TEXT("Отчество")) == 0) || (_tcscmp(columnName, TEXT("Patronymicname")) == 0))
	{
		size_t len = _tcslen(dataFromList);
		m_patronymicname = new TCHAR[len + 1];
		memset(m_patronymicname, 0, (len + 1)*sizeof(TCHAR));
		_tcscat_s(m_patronymicname, len + 1, dataFromList);
	}
	else
	{
		return;
	}
}

SQLTCHAR* Client::getNickname() const
{
	return m_nickname;
}

SQLTCHAR* Client::getStatus() const
{
	return m_status;
}

int Client::getDrop() const
{
	return m_drop;
}
int Client::getResult() const
{
	return m_result;
}
BOOL Client::getClientState() const
{
	return m_clientState;
}
TCHAR* Client::getLastVisit() const
{
	return m_lastVisit;
}

void Client::setClientState(BOOL clientState)
{
	m_clientState = clientState;
}

void Client::setLastVisit(TCHAR* date)
{
	if (m_lastVisit)
	{
		delete m_lastVisit;
		m_lastVisit = nullptr;
	}
	size_t len = _tcslen(date) + 1;
	m_lastVisit = new TCHAR[len];
	memset(m_lastVisit, 0, len*sizeof(TCHAR));
	_tcscpy_s(m_lastVisit, len, date);
}
/*void Client::getCustomerFinancialStatistics(SQLTCHAR* currentDate)
{
	SQLTCHAR* sqlCommand = TEXT("SELECT SUM(AllCashIn.CashInValue)  FROM AllCashIn WHERE  ClientID = ? AND CashInDate = ?");

	TCHAR stringClientID[20];
	_itot_s(clientID, stringClientID, 20, 10);
	SQLTCHAR* parameterArray[] = { stringClientID,currentDate };
	//int parameterArray[] = { clientID };
	
	extern CSqlFramework* sqlODBC;                                                          //allocating in main.cpp for working with database
	SQLHANDLE statementHandle = sqlODBC->ExecutePrepearedQuery(sqlCommand, parameterArray); //send query with parameter and parameter array to database
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

	sqlCommand = TEXT("SELECT SUM(AllCashOut.CashOutValue)  FROM AllCashOut WHERE  ClientID = ? AND CashOutDate = ?");
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

	
	sqlCommand = TEXT("SELECT [Drop].[DropValue] FROM [dbo].[Drop] WHERE ClientID = ? AND DropDate = ?");
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

	if ((result < 0) && (abs(result) > drop))
	{
		if (drop == 0)
		{
			drop = (abs(result));
			sqlCommand = TEXT("INSERT INTO [dbo].[Drop] ([ClientID] ,[DropValue]) VALUES (?,?)");
			int parameterArray[] = { clientID, drop };
			statementHandle = sqlODBC->ExecutePrepearedQuery(sqlCommand, parameterArray);  
			sqlODBC->FreeBinding(statementHandle);
			
		}
		else
		{
			drop = (abs(result));
			TCHAR stringDrop[20];
			_itot_s(drop, stringDrop, 20, 10);
			sqlCommand = TEXT("UPDATE [dbo].[Drop] SET [DropValue] = ? WHERE DropDate = ? AND ClientID = ?");
			SQLTCHAR* paramArrayForUpdateDrop[] = {stringDrop,currentDate, stringClientID };
			statementHandle = sqlODBC->ExecutePrepearedQuery(sqlCommand, paramArrayForUpdateDrop);
			sqlODBC->FreeBinding(statementHandle);
			
		}
	}
}
*/