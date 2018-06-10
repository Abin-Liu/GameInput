// GameInput.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "GameInput.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGameInputApp

BEGIN_MESSAGE_MAP(CGameInputApp, CWinApp)
	//{{AFX_MSG_MAP(CGameInputApp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGameInputApp construction

CGameInputApp::CGameInputApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CGameInputApp object

CGameInputApp theApp;

CGameManager& AfxGetManager()
{
	return theApp.m_manager;
}

int AfxFindComboByData(CComboBox* pCombo, DWORD dwData, BOOL bSelect)
{
	for (int i = 0; i < pCombo->GetCount(); i++)
	{
		if (pCombo->GetItemData(i) == dwData)
		{
			if (bSelect)
				pCombo->SetCurSel(i);
			return i;
		}
	}
	return -1;
}

DWORD AfxGetComboSelectedData(CComboBox* pCombo)
{
	int nSel = pCombo->GetCurSel();
	if (nSel == -1)
		return 0;

	return pCombo->GetItemData(nSel);
}

int AfxAddComboLine(CComboBox* pCombo, LPCTSTR lpszText, DWORD dwData)
{
	int nIndex = pCombo->AddString(lpszText);
	if (dwData)
		pCombo->SetItemData(nIndex, dwData);
	return nIndex;
}

/////////////////////////////////////////////////////////////////////////////
// CGameInputApp initialization

BOOL CGameInputApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	SetInstanceUniqueID(_T("{EE6BE41D-6D86-4150-A4CB-A750A4C716DF}"));
	if (!IsInstanceUnique())
		return FALSE;

	SetRegistryKey(_T("Abin"));
	m_manager.Load();

	CMainFrame* pFrame = new CMainFrame;
	m_pMainWnd = pFrame;
	pFrame->LoadFrame(IDR_MAINFRAME, WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL, NULL);
	return TRUE;
}

int CGameInputApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	m_manager.Save();
	return CWinApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// CGameInputApp message handlers

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD, GetDesktopWindow())
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()