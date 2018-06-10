; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CConfigDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "GameInput.h"
LastPage=0

ClassCount=12
Class1=CGameInputApp
Class3=CMainFrame
Class4=CAboutDlg

ResourceCount=10
Resource1=IDD_EDITDLG
Class2=CChildView
Resource2=IDD_CONFIGDLG
Class5=CConfigDlg
Resource3=IDD_NAMEDLG
Resource4=IDD_GAMEDETAILDLG
Class6=CNameDlg
Class7=CEditDlg
Resource5=IDD_ABOUTBOX
Class8=CGameDlg
Resource6=IDD_GAMEDLG
Class9=CGameDetailDlg
Resource7=IDD_SCHEMELISTDLG
Class10=CSchemeListDlg
Resource8=IDR_MAINFRAME
Class11=CCaptureDlg
Resource9=IDD_CAPTUREDLG
Class12=CHotkeyDlg
Resource10=IDD_HOTKEYDLG

[CLS:CGameInputApp]
Type=0
HeaderFile=GameInput.h
ImplementationFile=GameInput.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=CGameInputApp

[CLS:CChildView]
Type=0
HeaderFile=ChildView.h
ImplementationFile=ChildView.cpp
Filter=N

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CTrayFrameWnd
VirtualFilter=fWC
LastObject=ID_POPUP_RESET




[CLS:CAboutDlg]
Type=0
HeaderFile=GameInput.cpp
ImplementationFile=GameInput.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_POPUP_CONFIG
Command2=ID_POPUP_RESET
Command3=ID_APP_ABOUT
Command4=ID_APP_EXIT
CommandCount=4

[DLG:IDD_CONFIGDLG]
Type=1
Class=CConfigDlg
ControlCount=20
Control1=IDC_LIST1,SysListView32,1350664205
Control2=IDC_ADD,button,1476460544
Control3=IDC_EDIT,button,1476460544
Control4=IDC_DELETE,button,1476460544
Control5=IDC_UP,button,1476460544
Control6=IDC_DOWN,button,1476460544
Control7=IDC_STATIC,button,1342177287
Control8=IDC_STATIC,static,1342308352
Control9=IDC_SELHOTKEY,button,1342242816
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_GAMES,combobox,1344339971
Control15=IDC_SELGAME,button,1342242816
Control16=IDC_FOREGROUND,button,1342242819
Control17=IDC_STATIC,static,1342308352
Control18=IDC_SCHEMES,combobox,1344339971
Control19=IDC_MANAGESCHEME,button,1476460544
Control20=IDC_STATIC,static,1342308352

[CLS:CConfigDlg]
Type=0
HeaderFile=ConfigDlg.h
ImplementationFile=ConfigDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_ADD
VirtualFilter=dWC

[DLG:IDD_EDITDLG]
Type=1
Class=CEditDlg
ControlCount=19
Control1=IDC_STATIC,static,1342308352
Control2=IDC_TYPE,combobox,1344339971
Control3=IDC_STATIC,static,1342308352
Control4=IDC_MOUSEBTNS,combobox,1344339971
Control5=IDC_CODE,edit,1350631552
Control6=IDC_STATIC,static,1342308352
Control7=IDC_CTRL,button,1342242819
Control8=IDC_SHIFT,button,1342242819
Control9=IDC_ALT,button,1342242819
Control10=IDC_INTERVALLBL1,static,1342308352
Control11=IDC_INTERVAL,edit,1350631552
Control12=IDC_INTERVALLBL2,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_POSTWAIT,edit,1350631552
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_DESC,edit,1350631552
Control18=IDOK,button,1342242817
Control19=IDCANCEL,button,1342242816

[DLG:IDD_NAMEDLG]
Type=1
Class=CNameDlg
ControlCount=7
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT1,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_TYPE,button,1342308361
Control5=IDC_RADIO2,button,1342177289
Control6=IDOK,button,1342242817
Control7=IDCANCEL,button,1342242816

[CLS:CNameDlg]
Type=0
HeaderFile=NameDlg.h
ImplementationFile=NameDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CNameDlg
VirtualFilter=dWC

[CLS:CEditDlg]
Type=0
HeaderFile=EditDlg.h
ImplementationFile=EditDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CEditDlg
VirtualFilter=dWC

[DLG:IDD_GAMEDLG]
Type=1
Class=CGameDlg
ControlCount=6
Control1=IDC_LIST1,SysListView32,1350664461
Control2=IDC_ADD,button,1342242816
Control3=IDC_EDIT,button,1476460544
Control4=IDC_REMOVE,button,1476460544
Control5=IDC_CAPTURE,button,1342242816
Control6=IDCANCEL,button,1342242816

[CLS:CGameDlg]
Type=0
HeaderFile=GameDlg.h
ImplementationFile=GameDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_EDIT

[DLG:IDD_GAMEDETAILDLG]
Type=1
Class=CGameDetailDlg
ControlCount=8
Control1=IDC_STATIC,static,1342308352
Control2=IDC_NAME,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_TEXT,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_CLASS,edit,1350631552
Control7=IDOK,button,1342242817
Control8=IDCANCEL,button,1342242816

[CLS:CGameDetailDlg]
Type=0
HeaderFile=GameDetailDlg.h
ImplementationFile=GameDetailDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDOK

[CLS:CSchemeListDlg]
Type=0
HeaderFile=SchemeListDlg.h
ImplementationFile=SchemeListDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CSchemeListDlg
VirtualFilter=dWC

[DLG:IDD_SCHEMELISTDLG]
Type=1
Class=CSchemeListDlg
ControlCount=5
Control1=IDCANCEL,button,1342242816
Control2=IDC_LIST1,SysListView32,1350664205
Control3=IDC_ADD,button,1342242816
Control4=IDC_EDIT,button,1476460544
Control5=IDC_REMOVE,button,1476460544

[DLG:IDD_CAPTUREDLG]
Type=1
Class=CCaptureDlg
ControlCount=3
Control1=IDC_STATIC,static,1342308352
Control2=IDC_COUNTDOWN,static,1342308353
Control3=IDCANCEL,button,1342242816

[CLS:CCaptureDlg]
Type=0
HeaderFile=CaptureDlg.h
ImplementationFile=CaptureDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CCaptureDlg
VirtualFilter=dWC

[DLG:IDD_HOTKEYDLG]
Type=1
Class=CHotkeyDlg
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_COMBO1,combobox,1344339971
Control5=IDC_STATIC,static,1342308352

[CLS:CHotkeyDlg]
Type=0
HeaderFile=HotkeyDlg.h
ImplementationFile=HotkeyDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

