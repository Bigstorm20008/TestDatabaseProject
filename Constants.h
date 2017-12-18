#pragma once
//This H.file include all defined variable used in program

#define controlPanelWnd 1000
#define autorizationWnd 1001

//For AutentificationClass
#define ID_USER_NAME 1002             //ID for "EDIT" window where user enter username
#define ID_PASS 1003                  //ID for "EDIT" window where user enter pass
#define ID_OKBTN 1004                 //ID for continue button in Autentification window
#define ID_CANCELBTN 1005             //ID for cancel button in Autentification window


//For ClientView
#define imageWidth 364                //Image Width in ClientView
#define imageHeight 273               //Image Height in ClientView
#define listViewWidth 500             //ListView Width in ClientView
#define ID_IMAGE_WND 1006             //ID for Image Window in ClientView
#define ID_LIST_FOR_CLIENTVIEW 1007   //ID for LISTVIEW in ClientView
#define ID_ADD_NEW_CLIENT_BTN 1008    //ID for button "Add new Client" in ClientView
#define ID_ENTRANCE_CASINO_BTN 1009   //ID for button "Entrance to the casino" in ClientView
#define ID_EDIT_CLIENT_BTN 1010       //ID for button "Edit client" in ClientView

#define ID_CASHIER_PANEL 1011
#define ID_CASH_BTN      1012
#define ID_CLIENT_BTN    1013
#define ID_DILER_BTN     1014

//For AuxiliaryWindows
#define ID_ADD_NEW_CLIENT_WND      1015
#define ID_STATIC_CAPTION          1016
#define ID_ADD_TO_BASE_BTN         1017
#define ID_CANCEL_ADD_TO_BASE_BTN  1018
#define ID_EDITBOX_FOR_NICKNAME    1019
#define ID_STATIC_DESCRIPTION      1020

//My messages
#define WM_LISTVIEW_CLICKED (WM_USER+1)         //Message for controlpanel(mouse clicked in listview for ClienView)