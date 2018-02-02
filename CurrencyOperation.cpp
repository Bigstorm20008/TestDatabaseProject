#include "CurrencyOperation.h"


CurrencyOperation::CurrencyOperation(CSqlFramework* sqlConnection)
{
	m_sqlConnection = sqlConnection;
	getDateInCasino();
	getCurrencyRates();
}


CurrencyOperation::~CurrencyOperation()
{
	m_sqlConnection = nullptr;
	if (m_dateInCasino)
	{
		delete[] m_dateInCasino;
		m_dateInCasino = nullptr;
	}
	if (m_stringValueOfDollarRate)
	{
		delete[]m_stringValueOfDollarRate;
		m_stringValueOfDollarRate = nullptr;
	}
	if (m_stringValueofEuroRate)
	{
		delete[] m_stringValueofEuroRate;
		m_stringValueofEuroRate = nullptr;
	}
}

void CurrencyOperation::getCurrencyRates()
{
	getDollarRateFromDatabase();
	getEuroRateFromDatabase();
}

void CurrencyOperation::getDateInCasino()
{
	TCHAR* sqlCommand = TEXT("SELECT [Date] FROM [dbo].[DateInCasino]");
	SQLHANDLE statementHandle = m_sqlConnection->SendQueryToDatabase(sqlCommand);
	Binding* pBinding = m_sqlConnection->GetBinding();
	while (SQLFetch(statementHandle) != SQL_NO_DATA)
	{

		Binding* tempBinding = pBinding;
		while (tempBinding)
		{
			size_t len = _tcslen(tempBinding->GetDescription()) + 1;
			m_dateInCasino = new TCHAR[len];
			memset(m_dateInCasino, 0, len*sizeof(TCHAR));
			_tcscpy_s(m_dateInCasino, len, tempBinding->GetDescription());
			tempBinding = tempBinding->GetNextBinding(); //set pointer to next element
		}
	}
	m_sqlConnection->FreeBinding(statementHandle);
}

void CurrencyOperation::getDollarRateFromDatabase()
{
	TCHAR* sqlCommand = TEXT("SELECT CurrencyID FROM [dbo].[Наименование валют] WHERE (currencyName = 'Доллары')");
	getCurrencyIdFromDatabase(sqlCommand, m_stringDollarID);

	m_stringValueOfDollarRate = getCurrencyRateFromDatabase(m_stringDollarID);

}

void CurrencyOperation::getEuroRateFromDatabase()
{
	TCHAR* sqlCommand = TEXT("SELECT CurrencyID FROM [dbo].[Наименование валют] WHERE (currencyName = 'Евро')");
	getCurrencyIdFromDatabase(sqlCommand, m_stringEuroID);

    m_stringValueofEuroRate = getCurrencyRateFromDatabase(m_stringEuroID);
}

void CurrencyOperation::getCurrencyIdFromDatabase(SQLTCHAR* sqlCommandForGetId, TCHAR bufferForSaveId[4])
{
	SQLHANDLE statementHandle = m_sqlConnection->SendQueryToDatabase(sqlCommandForGetId);
	Binding* pBinding = m_sqlConnection->GetBinding();
	while (SQLFetch(statementHandle) != SQL_NO_DATA)
	{

		Binding* tempBinding = pBinding;
		while (tempBinding)
		{
			_itot_s(tempBinding->getIntegerData(), bufferForSaveId,4, 10);
			tempBinding = tempBinding->GetNextBinding(); //set pointer to next element
		}
	}
	m_sqlConnection->FreeBinding(statementHandle);
}

TCHAR* CurrencyOperation::getCurrencyRateFromDatabase(TCHAR* stringCurrencyId)
{
	TCHAR* stringValueRate = nullptr;
	SQLTCHAR* sqlCommand = TEXT("SELECT CurrencyRateValue FROM [dbo].[ExchangeRates] WHERE (CurrencyID = ? AND DateOfCurrencyRate = ?)");
	SQLTCHAR* parameterArray[] = { stringCurrencyId, m_dateInCasino };
	SQLHANDLE statementHandle = m_sqlConnection->ExecutePrepearedQuery(sqlCommand, parameterArray);
	Binding* pBinding = m_sqlConnection->GetBinding();
	while (SQLFetch(statementHandle) != SQL_NO_DATA)
	{

		Binding* tempBinding = pBinding;
		while (tempBinding)
		{
			size_t len = _tcslen(tempBinding->GetDescription()) + 1;
			stringValueRate = new TCHAR[len];
			memset(stringValueRate, 0, len*sizeof(TCHAR));
			_tcscpy_s(stringValueRate, len, tempBinding->GetDescription());
			tempBinding = tempBinding->GetNextBinding(); //set pointer to next element
		}
	}
	m_sqlConnection->FreeBinding(statementHandle);
	return stringValueRate;
}
TCHAR* CurrencyOperation::getDollarRate() const
{
	return m_stringValueOfDollarRate;
}


TCHAR* CurrencyOperation::getEuroRate() const
{
	return m_stringValueofEuroRate;
}


void CurrencyOperation::setNewDollarRate(TCHAR* newRateValue)
{
	TCHAR* sqlCommand = TEXT("UPDATE [dbo].[ExchangeRates] SET [CurrencyRateValue] = ? WHERE (CurrencyID = ? AND DateOfCurrencyRate = ?)");
	SQLTCHAR* parameterArray[] = { newRateValue, m_stringDollarID, m_dateInCasino };
	SQLHANDLE statementHandle = m_sqlConnection->ExecutePrepearedQuery(sqlCommand, parameterArray);
	m_sqlConnection->FreeBinding(statementHandle);

	delete[]m_stringValueOfDollarRate;
	m_stringValueOfDollarRate = nullptr;
	m_stringValueOfDollarRate = getCurrencyRateFromDatabase(m_stringDollarID);
}


void CurrencyOperation::setNewEuroRate(TCHAR* newRateValue)
{
	TCHAR* sqlCommand = TEXT("UPDATE [dbo].[ExchangeRates] SET [CurrencyRateValue] = ? WHERE (CurrencyID = ? AND DateOfCurrencyRate = ?)");
	SQLTCHAR* parameterArray[] = { newRateValue, m_stringEuroID, m_dateInCasino };
	SQLHANDLE statementHandle = m_sqlConnection->ExecutePrepearedQuery(sqlCommand, parameterArray);
	m_sqlConnection->FreeBinding(statementHandle);

	delete[]m_stringValueofEuroRate;
	m_stringValueofEuroRate = nullptr;
	m_stringValueofEuroRate = getCurrencyRateFromDatabase(m_stringEuroID);
}


double CurrencyOperation::convertEuroToDollar(double euroValue)
{
	return NULL;
}


double CurrencyOperation::convertGrivnaToDollar(double grivnaValue)
{
	return NULL;
}
