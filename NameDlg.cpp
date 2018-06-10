// NameDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GameInput.h"
#include "NameDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNameDlg dialog


CNameDlg::CNameDlg(LPCTSTR lpszName, BOOL bRunOnce, CWnd* pParent /*=NULL*/)
	: CDialog(CNameDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNameDlg)
	m_sName = lpszName;
	m_nType = bRunOnce ? 1 : 0;
	//}}AFX_DATA_INIT
}


void CNameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNameDlg)
	DDX_Control(pDX, IDC_EDIT1, m_wndName);
	DDX_Text(pDX, IDC_EDIT1, m_sName);
	DDX_Radio(pDX, IDC_TYPE, m_nType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNameDlg, CDialog)
	//{{AFX_MSG_MAP(CNameDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNameDlg message handlers

void CNameDlg::OnOK() 
{
	// TODO: Add extra validation here
	if (!UpdateData(TRUE))
		return;

	m_sName.TrimLeft();
	m_sName.TrimRight();
	if (m_sName.IsEmpty())
	{
		m_wndName.SetFocus();
		m_wndName.Highlight();
		return;
	}

	if (m_sName.CompareNoCase(_T("General")) == 0)
	{
		MessageBox(_T("\"General\"为系统保留词，不允许作为方案名称。"), _T("无效方案名称"), MB_ICONEXCLAMATION);
		m_wndName.SetFocus();
		m_wndName.Highlight();
		return;
	}

	EndDialog(IDOK);
}
