#pragma once

#define offsetsBetweenWindow 5
#define heightOfControlPanelForApp 50
#define windowCaptionHeight  20
#define descriptionForControlHeight 15
#define imageWidthForApplication 364                   
#define imageHeightForApplication 273 
#define listViewWidth 500


//For ControlPanel
#define ID_CLIENT_BTN 1000
#define ID_CASH_BTN 1001
#define ID_EMPLOYEE_BTN 1002
#define ID_OPEN_CASINO_BTN 1003

//For AuxiliaryTemplate
#define ID_CANCEL_AUXILIARY_BTN 1500
#define ID_AUXILIARY_CAPTION    1501

//For AddClientToDatabaseForm
#define ID_OK_BTN                        1600
#define ID_ADD_CLIENT_TO_BASE_BTN        1601
#define ID_OPEN_WINDOW_EXPLORER          1602
#define ID_ADD_PHONE_NUMBER_TO_LIST      1603
#define ID_REMOVE_PHONE_NUMBER_FROM_LIST 1604


#define ID_CONTINUE_AUTENTIFICATION_BTN  1700

//For ControlsForViews
#define captionHeightForGroupButton      20
#define ID_CHANGE_DOLLAR_RATE            1800
#define ID_CHANGE_EURO_RATE              1801
#define ID_ENTRANCE_TO_CASINO_BUTTON     1802
#define ID_CASH_IN_BUTTON                1803
#define ID_CASH_OUT_BUTTON               1804
#define ID_ADD_CLIENT_TO_DATABASE_BTN    1805

//For changeCurrencyRateForm
#define ID_CHANGE_CURRENCY_RATE          1900


//For CashInCashOutForm
#define ID_EXIT_FROM_CASINO_BUTTON       2000
#define ID_SAVE_CASHIN_IN_DATABASE_BUTTON 2001
#define ID_SAVE_CASHOUT_IN_DATABASE_BUTTON 2002

#define INF_DATABASE_CONNECTED (WM_USER+1)
#define INF_OPERATION_COMPLETE (WM_USER+2)
#define INF_CASHIN_CASHOUT_COMPLETE (WM_USER+3)


//#define ID_BUTTON 2000
