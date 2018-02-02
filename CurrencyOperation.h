#pragma once

#include "SqlFramework.h"
class CurrencyOperation
{
public:
	CurrencyOperation(CSqlFramework* sqlConnection);
	~CurrencyOperation();

	TCHAR* getDollarRate() const;
	TCHAR* getEuroRate() const;
	void setNewDollarRate(TCHAR* newRateValue);
	void setNewEuroRate(TCHAR* newRateValue);
	double convertEuroToDollar(double euroValue);
	double convertGrivnaToDollar(double grivnaValue);
private:
	CSqlFramework* m_sqlConnection;
	TCHAR* m_dateInCasino;

	void getCurrencyRates();
	void getDateInCasino();
	void getDollarRateFromDatabase();
	void getEuroRateFromDatabase();
	void getCurrencyIdFromDatabase(SQLTCHAR* sqlCommandForGetId,TCHAR bufferForSaveId[4]);
	TCHAR* getCurrencyRateFromDatabase(TCHAR* stringCurrencyId);

	TCHAR m_stringDollarID[4];
	TCHAR m_stringEuroID[4];
	TCHAR* m_stringValueOfDollarRate;
	TCHAR* m_stringValueofEuroRate;

};

