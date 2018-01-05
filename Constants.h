#pragma once
//This H.file include all defined variable used in program

//For AutentificationClass
#define ID_AUTENTIFICATION_WND 2001
#define ID_AUTHORISATION_WND 1001
#define ID_USER_NAME 1002             //ID for "EDIT" window where user enter username
#define ID_PASS 1003                  //ID for "EDIT" window where user enter pass
#define ID_OKBTN 1004                 //ID for continue button in Autentification window
#define ID_CANCELBTN 1005             //ID for cancel button in Autentification window



//For UserInterfaceClass
#define offsetBetweenWindow 5
#define contolPanelHeight 50
#define imageWidth 364                    //Image Width
#define imageHeight 273                   //Image Height
#define listViewWidth 500
#define ID_CONTROL_PANEL_WND 1000
#define ID_CLIENT_AREA 1006
#define ID_IMAGE_WND   1007
#define ID_LISTVIEW_WND 1008
#define ID_EXT_INFO_WND 1009

//For AuxiliaryWindows
#define ID_ADD_NEW_CLIENT_WND       1015
#define ID_STATIC_CAPTION           1016
#define ID_ADD_TO_BASE_BTN          1017
#define ID_CANCEL_ADD_TO_BASE_BTN   1018
#define ID_EDITBOX_FOR_NICKNAME     1019
#define ID_EDITBOX_FOR_LASTNAME     1020
#define ID_EDITBOX_FOR_FIRSTNAME    1021
#define ID_DESCRIPTION_NICKNAME     1022
#define ID_DESCRIPTION_LASTNAME     1023
#define ID_DESCRIPTION_FIRSTNAME    1024
#define ID_EDITBOX_FOR_PATRONYMIC   1025
#define ID_DESCRIPTION_PATRONYMIC   1026
#define ID_EDITBOX_FOR_BIRTHDAY     1027
#define ID_DESCRIPTION_BIRTHDAY     1028
#define ID_CB_STATUS_SELECT         1029
#define ID_BTN_ADD_PHONE            1030
#define ID_LB_FOR_PHONENUMBER       1031
#define ID_EDITBOX_FOR_PHONE        1032
#define ID_IMAGE_WND_FOR_NEW_CLIENT 1033
#define ID_BTN_ADD_PHOTO            1034
#define ID_EDITBOX_FOR_IMAGE        1035

//ExtPersonInfo class

//ButtonsForViews class
#define ID_CASH_IN_BTN  1036

//
#define INF_DATABASE_CONNECTED (WM_USER+1)
#define WM_LISTVIEW_CLICKED (WM_USER+2)         //Message for controlpanel(mouse clicked in listview for ClienView)
#define INF_OPERATION_COMPLETE (WM_USER+3)