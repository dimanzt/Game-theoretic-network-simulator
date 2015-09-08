; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMANETView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "MANET.h"
LastPage=0

ClassCount=14
Class1=CMANETApp
Class2=CMANETDoc
Class3=CMANETView
Class4=CMainFrame

ResourceCount=22
Resource1=IDD_DIALOG_SIMULATION
Class5=CAboutDlg
Class6=CRouter
Resource2=IDR_MENU_ROUTER
Class7=CRouterDialog
Resource3=IDR_MENU_LINK
Class8=CCaptionDialog
Resource4=IDD_ABOUTBOX
Resource5=IDD_DIALOG_TRAFFIC
Resource6=IDD_DIALOG_LINK
Resource7=IDD_DIALOG_ROUTER
Class9=CTrafficDialog
Class10=CLinkDialog
Resource8=IDD_DIALOG_CAPTION
Class11=CSimDlg
Resource9=IDR_MAINFRAME
Class12=CEnd2End
Resource10=IDD_DIALOG_End2End
Resource11=IDD_DIALOG_ROUTER (English (U.S.))
Resource12=IDD_DIALOG_SIMULATION (English (U.S.))
Resource13=IDR_MENU_LINK (English (U.S.))
Resource14=IDR_MENU_ROUTER (English (U.S.))
Resource15=IDD_DIALOG_End2End (English (U.S.))
Resource16=IDD_DIALOG_CAPTION (English (U.S.))
Resource17=IDD_DIALOG_RandomTraffic
Resource18=IDD_DIALOG_TRAFFIC (English (U.S.))
Resource19=IDD_DIALOG_LINK (English (U.S.))
Resource20=IDD_ABOUTBOX (English (U.S.))
Class13=RandomTraffic
Resource21=IDR_MAINFRAME (English (U.S.))
Class14=CStat
Resource22=IDD_DIALOG_Stat

[CLS:CMANETApp]
Type=0
HeaderFile=MANET.h
ImplementationFile=MANET.cpp
Filter=N
LastObject=ID_VIEW_TOOLBAR

[CLS:CMANETDoc]
Type=0
HeaderFile=MANETDoc.h
ImplementationFile=MANETDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=CMANETDoc

[CLS:CMANETView]
Type=0
HeaderFile=MANETView.h
ImplementationFile=MANETView.cpp
Filter=C
LastObject=CMANETView
BaseClass=CView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=ID_SIMULATION_STATISTICS
BaseClass=CFrameWnd
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=MANET.cpp
ImplementationFile=MANET.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_SEND_MAIL
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_VIEW_TOOLBAR
Command16=ID_VIEW_STATUS_BAR
Command17=ID_NETWORK_ROUTER_SELFGENERATE_1
Command18=ID_NETWORK_ROUTER_SELFGENERATE_2
Command19=ID_NETWORK_ROUTER_SELFGENERATE_5
Command20=ID_NETWORK_ROUTER_SELFGENERATE_10
Command21=ID_NETWORK_ROUTER_SELFGENERATE_20
Command22=ID_NETWORK_ROUTER_SELFGENERATE_50
Command23=ID_NETWORK_ROUTER_SELFGENERATE_100
Command24=ID_NETWORK_ROUTER_ADD
Command25=ID_NETWORK_ROUTER_EDIT
Command26=ID_NETWORK_ROUTER_DELETE
Command27=ID_NETWORK_ROUTER_PREFERENCES
Command28=ID_NETWORK_LINK_SELFGENERATE
Command29=ID_NETWORK_LINK_ADD
Command30=ID_NETWORK_LINK_EDIT
Command31=ID_NETWORK_LINK_DELETE
Command32=ID_NETWORK_LINK_ROUTERSCLICK
Command33=ID_NETWORK_LINK_UPDATEREDLINKS
Command34=ID_NETWORK_LINK_CREATEBLUELINKS
Command35=ID_NETWORK_LINK_REMOVEREDLINKS
Command36=ID_NETWORK_LINK_DEFAULTPREFERENCES
Command37=ID_NETWORK_TRAFFIC_SELFGENERATE
Command38=ID_NETWORK_TRAFFIC_ADD
Command39=ID_NETWORK_TRAFFIC_EDIT
Command40=ID_NETWORK_TRAFFIC_DELETE
Command41=ID_NETWORK_TRAFFIC_DEFAULTPREFERENCES
Command42=ID_SIMULATE_RUN
Command43=ID_SIMULATION_STATISTICS_NUMBEROFRREQS
Command44=ID_SIMULATION_STATISTICS_NUMBEROFRREPS
Command45=ID_SIMULATION_STATISTICS_NUMBEROFDATAPACKETS
Command46=ID_HELP_FINDER
Command47=ID_APP_ABOUT
CommandCount=47

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
Command15=ID_CONTEXT_HELP
Command16=ID_HELP
CommandCount=16

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
Command9=ID_CONTEXT_HELP
CommandCount=9

[CLS:CRouter]
Type=0
HeaderFile=Router.h
ImplementationFile=Router.cpp
BaseClass=CButton
Filter=W
VirtualFilter=BWC
LastObject=CRouter

[DLG:IDD_DIALOG_ROUTER]
Type=1
Class=CRouterDialog
ControlCount=24
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT_CAPTION,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_COVERAGE,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT_DELAY,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT_BUFFER,edit,1350631552
Control9=IDC_STATIC,static,1342308352
Control10=IDC_EDIT_IMAGE,edit,1350631552
Control11=IDC_STATIC,static,1342308352
Control12=IDC_EDIT_X,edit,1350631552
Control13=IDC_STATIC,static,1342308352
Control14=IDC_EDIT_Y,edit,1350631552
Control15=IDC_STATIC,static,1342308352
Control16=IDC_EDIT_LENGTH,edit,1350631552
Control17=IDC_STATIC,static,1342308352
Control18=IDC_EDIT_WIDTH,edit,1350631552
Control19=IDOK,button,1342242817
Control20=IDCANCEL,button,1342242816
Control21=IDC_STATIC,button,1342177287
Control22=IDC_RADIO_Adhoc,button,1342308361
Control23=IDC_RADIO_Malicious,button,1342177289
Control24=IDC_RADIO_Selfish,button,1342177289

[CLS:CRouterDialog]
Type=0
HeaderFile=RouterDialog.h
ImplementationFile=RouterDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_RADIO2
VirtualFilter=dWC

[DLG:IDD_DIALOG_CAPTION]
Type=1
Class=CCaptionDialog
ControlCount=4
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT_CAPTION,edit,1350631552
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816

[CLS:CCaptionDialog]
Type=0
HeaderFile=CaptionDialog.h
ImplementationFile=CaptionDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CCaptionDialog

[DLG:IDD_DIALOG_LINK]
Type=1
Class=CLinkDialog
ControlCount=11
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT_IN,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_OUT,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT_FREQUENCY,edit,1350631552
Control7=IDC_STATIC,button,1342177287
Control8=IDC_RADIO_FULL,button,1342308361
Control9=IDC_RADIO_HALF,button,1342177289
Control10=IDOK,button,1342242817
Control11=IDCANCEL,button,1342242816

[MNU:IDR_MENU_ROUTER]
Type=1
Class=CMANETView
Command1=ID_ROUTER_ADD
Command2=ID_ROUTER_EDIT
Command3=ID_ROUTER_DELETE
CommandCount=3

[MNU:IDR_MENU_LINK]
Type=1
Class=?
Command1=ID_LINK_LINKFROMHERE
Command2=ID_LINK_LINKTOHERE
CommandCount=2

[DLG:IDD_DIALOG_TRAFFIC]
Type=1
Class=CTrafficDialog
ControlCount=12
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT_SOURCE,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_DESTINATION,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT_START,edit,1350631552
Control7=IDC_STATIC,button,1342177287
Control8=IDC_RADIO_ELMAR,button,1342308361
Control9=IDC_RADIO_AODV,button,1342177289
Control10=IDC_RADIO_DSR,button,1342177289
Control11=IDOK,button,1342242817
Control12=IDCANCEL,button,1342242816

[CLS:CLinkDialog]
Type=0
HeaderFile=LinkDialog.h
ImplementationFile=LinkDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CLinkDialog

[CLS:CTrafficDialog]
Type=0
HeaderFile=trafficdialog.h
ImplementationFile=trafficdialog.cpp
BaseClass=CDialog
LastObject=CTrafficDialog
Filter=D
VirtualFilter=dWC

[DLG:IDD_DIALOG_SIMULATION]
Type=1
Class=CSimDlg
ControlCount=11
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,static,1342308352
Control3=IDC_SLIDER_MasterSpeed,msctls_trackbar32,1342242840
Control4=IDC_STATIC,static,1342308352
Control5=IDC_SLIDER_SlaveSpeed1,msctls_trackbar32,1342242840
Control6=IDC_SLIDER_SlaveSpeed2,msctls_trackbar32,1342242840
Control7=IDC_STATIC,button,1342177287
Control8=IDC_LIST_EVENTS,listbox,1352728835
Control9=IDOK,button,1342242817
Control10=IDC_BUTTON_ResumeStop,button,1342242816
Control11=IDCANCEL,button,1342242816

[CLS:CSimDlg]
Type=0
HeaderFile=SimDlg.h
ImplementationFile=SimDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_BUTTON_ResumeStop

[DLG:IDD_DIALOG_End2End]
Type=1
Class=CEnd2End
ControlCount=6
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT_ROUTER1,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_ROUTER2,edit,1350631552
Control5=IDOK,button,1342242817
Control6=IDCANCEL,button,1342242816

[CLS:CEnd2End]
Type=0
HeaderFile=End2End.h
ImplementationFile=End2End.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CEnd2End

[DLG:IDD_DIALOG_CAPTION (English (U.S.))]
Type=1
Class=CCaptionDialog
ControlCount=4
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT_CAPTION,edit,1350631552
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816

[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
Command9=ID_CONTEXT_HELP
CommandCount=9

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_SEND_MAIL
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_VIEW_TOOLBAR
Command16=ID_VIEW_STATUS_BAR
Command17=ID_NETWORK_ROUTER_SELFGENERATE_1
Command18=ID_NETWORK_ROUTER_SELFGENERATE_2
Command19=ID_NETWORK_ROUTER_SELFGENERATE_5
Command20=ID_NETWORK_ROUTER_SELFGENERATE_10
Command21=ID_NETWORK_ROUTER_SELFGENERATE_20
Command22=ID_NETWORK_ROUTER_SELFGENERATE_50
Command23=ID_NETWORK_ROUTER_SELFGENERATE_100
Command24=ID_NETWORK_ROUTER_ADD
Command25=ID_NETWORK_ROUTER_EDIT
Command26=ID_NETWORK_ROUTER_DELETE
Command27=ID_NETWORK_ROUTER_PREFERENCES
Command28=ID_NETWORK_LINK_SELFGENERATE
Command29=ID_NETWORK_LINK_ADD
Command30=ID_NETWORK_LINK_EDIT
Command31=ID_NETWORK_LINK_DELETE
Command32=ID_NETWORK_LINK_ROUTERSCLICK
Command33=ID_NETWORK_LINK_UPDATEREDLINKS
Command34=ID_NETWORK_LINK_CREATEBLUELINKS
Command35=ID_NETWORK_LINK_REMOVEREDLINKS
Command36=ID_NETWORK_LINK_DEFAULTPREFERENCES
Command37=ID_NETWORK_TRAFFIC_SELFGENERATE
Command38=ID_NETWORK_TRAFFIC_ADD
Command39=ID_NETWORK_TRAFFIC_EDIT
Command40=ID_NETWORK_TRAFFIC_DELETE
Command41=ID_NETWORK_TRAFFIC_DEFAULTPREFERENCES
Command42=ID_SIMULATE_RUN
Command43=ID_SIMULATION_STATISTICS
Command44=ID_HELP_FINDER
Command45=ID_APP_ABOUT
CommandCount=45

[MNU:IDR_MENU_ROUTER (English (U.S.))]
Type=1
Class=?
Command1=ID_ROUTER_ADD
Command2=ID_ROUTER_EDIT
Command3=ID_ROUTER_DELETE
CommandCount=3

[MNU:IDR_MENU_LINK (English (U.S.))]
Type=1
Class=?
Command1=ID_LINK_LINKFROMHERE
Command2=ID_LINK_LINKTOHERE
CommandCount=2

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
Command15=ID_CONTEXT_HELP
Command16=ID_HELP
CommandCount=16

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352

[DLG:IDD_DIALOG_ROUTER (English (U.S.))]
Type=1
Class=CRouterDialog
ControlCount=24
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT_CAPTION,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_COVERAGE,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT_DELAY,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT_BUFFER,edit,1350631552
Control9=IDC_STATIC,static,1342308352
Control10=IDC_EDIT_IMAGE,edit,1350631552
Control11=IDC_STATIC,static,1342308352
Control12=IDC_EDIT_X,edit,1350631552
Control13=IDC_STATIC,static,1342308352
Control14=IDC_EDIT_Y,edit,1350631552
Control15=IDC_STATIC,static,1342308352
Control16=IDC_EDIT_LENGTH,edit,1350631552
Control17=IDC_STATIC,static,1342308352
Control18=IDC_EDIT_WIDTH,edit,1350631552
Control19=IDOK,button,1342242817
Control20=IDCANCEL,button,1342242816
Control21=IDC_STATIC,button,1342177287
Control22=IDC_RADIO_Adhoc,button,1342308361
Control23=IDC_RADIO_Malicious,button,1342177289
Control24=IDC_RADIO_Selfish,button,1342177289

[DLG:IDD_DIALOG_LINK (English (U.S.))]
Type=1
Class=CLinkDialog
ControlCount=11
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT_IN,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_OUT,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT_FREQUENCY,edit,1350631552
Control7=IDC_STATIC,button,1342177287
Control8=IDC_RADIO_FULL,button,1342308361
Control9=IDC_RADIO_HALF,button,1342177289
Control10=IDOK,button,1342242817
Control11=IDCANCEL,button,1342242816

[DLG:IDD_DIALOG_TRAFFIC (English (U.S.))]
Type=1
Class=CTrafficDialog
ControlCount=12
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT_SOURCE,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_DESTINATION,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT_START,edit,1350631552
Control7=IDC_STATIC,button,1342177287
Control8=IDC_RADIO_ELMAR,button,1342308361
Control9=IDC_RADIO_AOMDV,button,1342177289
Control10=IDC_RADIO_DSR,button,1342177289
Control11=IDOK,button,1342242817
Control12=IDCANCEL,button,1342242816

[DLG:IDD_DIALOG_SIMULATION (English (U.S.))]
Type=1
Class=CSimDlg
ControlCount=11
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,static,1342308352
Control3=IDC_SLIDER_MasterSpeed,msctls_trackbar32,1342242840
Control4=IDC_STATIC,static,1342308352
Control5=IDC_SLIDER_SlaveSpeed1,msctls_trackbar32,1342242840
Control6=IDC_SLIDER_SlaveSpeed2,msctls_trackbar32,1342242840
Control7=IDC_STATIC,button,1342177287
Control8=IDC_LIST_EVENTS,listbox,1352728835
Control9=IDOK,button,1342242817
Control10=IDC_BUTTON_ResumeStop,button,1342242816
Control11=IDCANCEL,button,1342242816

[DLG:IDD_DIALOG_End2End (English (U.S.))]
Type=1
Class=CEnd2End
ControlCount=6
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT_ROUTER1,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_ROUTER2,edit,1350631552
Control5=IDOK,button,1342242817
Control6=IDCANCEL,button,1342242816

[DLG:IDD_DIALOG_RandomTraffic]
Type=1
Class=RandomTraffic
ControlCount=12
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT_Connection,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_Range,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT_DataRate,edit,1350631552
Control7=IDC_STATIC,button,1342177287
Control8=IDC_RADIO_ELMAR,button,1342308361
Control9=IDC_RADIO_AOMDV,button,1342177289
Control10=IDC_RADIO_DSR,button,1342177289
Control11=IDOK,button,1342242817
Control12=IDCANCEL,button,1342242816

[CLS:RandomTraffic]
Type=0
HeaderFile=RandomTraffic.h
ImplementationFile=RandomTraffic.cpp
BaseClass=CDialog
Filter=D
LastObject=RandomTraffic
VirtualFilter=dWC

[DLG:IDD_DIALOG_Stat]
Type=1
Class=CStat
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_ProcessedPackets,edit,1350633600
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT2,edit,1350631552

[CLS:CStat]
Type=0
HeaderFile=Stat.h
ImplementationFile=Stat.cpp
BaseClass=CDialog
Filter=D
LastObject=CStat
VirtualFilter=dWC

