// HotkeyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GameInput.h"
#include "HotkeyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHotkeyDlg dialog


CHotkeyDlg::CHotkeyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHotkeyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHotkeyDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_dwHotkey = AfxGetManager().GetHotkey();
}


void CHotkeyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHotkeyDlg)
	DDX_Control(pDX, IDC_COMBO1, m_wndComboi);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHotkeyDlg, CDialog)
	//{{AFX_MSG_MAP(CHotkeyDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHotkeyDlg message handlers

BOOL CHotkeyDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	m_wndComboi.SetItemHeight(0, 17);

	// Fill hotkeys
	for (int i = 0; i < 12; i++)
	{
		CString sKey;
		sKey.Format(_T("F%d"), i + 1);
		AddHotkey(VK_F1 + i, sKey);
	}

	AddHotkey(VK_PAUSE, _T("Pause"));
	AddHotkey(VK_HOME, _T("Home"));
	AddHotkey(VK_END, _T("End"));

	AfxFindComboByData(&m_wndComboi, m_dwHotkey, TRUE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

int CHotkeyDlg::AddHotkey(DWORD dwKeyCode, LPCTSTR lpszName)
{
	int nIndex = m_wndComboi.AddString(lpszName);
	m_wndComboi.SetItemData(nIndex, dwKeyCode);
	return nIndex;
}

void CHotkeyDlg::OnOK() 
{
	// TODO: Add extra validation here
	m_dwHotkey = AfxGetComboSelectedData(&m_wndComboi);
	EndDialog(IDOK);
}
