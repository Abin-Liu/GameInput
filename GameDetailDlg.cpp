// GameDetailDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GameInput.h"
#include "GameDetailDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGameDetailDlg dialog


CGameDetailDlg::CGameDetailDlg(LPCTSTR lpszName, LPCTSTR lpszTitle, LPCTSTR lpszClass, CWnd* pParent /*=NULL*/)
	: CDialog(CGameDetailDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGameDetailDlg)
	m_sName = lpszName;
	m_sText = lpszTitle;
	m_sClass = lpszClass;
	//}}AFX_DATA_INIT
}


void CGameDetailDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGameDetailDlg)
	DDX_Control(pDX, IDC_CLASS, m_wndClass);
	DDX_Control(pDX, IDC_TEXT, m_wndText);
	DDX_Control(pDX, IDC_NAME, m_wndName);
	DDX_Text(pDX, IDC_NAME, m_sName);
	DDV_MaxChars(pDX, m_sName, 64);
	DDX_Text(pDX, IDC_TEXT, m_sText);
	DDV_MaxChars(pDX, m_sText, 64);
	DDX_Text(pDX, IDC_CLASS, m_sClass);
	DDV_MaxChars(pDX, m_sClass, 64);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGameDetailDlg, CDialog)
	//{{AFX_MSG_MAP(CGameDetailDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGameDetailDlg message handlers

void CGameDetailDlg::OnOK() 
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

	if (ValidateTitleClass())
		EndDialog(IDOK);
}

BOOL CGameDetailDlg::ValidateTitleClass()
{
	m_sText.TrimLeft();
	m_sText.TrimRight();
	m_sClass.TrimLeft();
	m_sClass.TrimRight();

	if (m_sText.IsEmpty() && m_sClass.IsEmpty())
	{
		MessageBox(_T("标题文字与窗口类名不能全部为空。"), _T("无效输入"), MB_ICONEXCLAMATION);
		m_wndText.SetFocus();
		m_wndText.Highlight();
		return FALSE;
	}

	return TRUE;
}