// CaptureDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GameInput.h"
#include "CaptureDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCaptureDlg dialog


CCaptureDlg::CCaptureDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCaptureDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCaptureDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_nRemain = 0;
}


void CCaptureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCaptureDlg)
	DDX_Control(pDX, IDC_COUNTDOWN, m_wndCountDown);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCaptureDlg, CDialog)
	//{{AFX_MSG_MAP(CCaptureDlg)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCaptureDlg message handlers

BOOL CCaptureDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_nRemain = 6000;
	SetTimer(ID_TMR_COUNTDOWN, 200, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCaptureDlg::OnDestroy() 
{
	KillTimer(ID_TMR_COUNTDOWN);
	CDialog::OnDestroy();	
}

void CCaptureDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == ID_TMR_COUNTDOWN)
	{
		m_nRemain -= 200;
		if (m_nRemain > 0)
		{
			CString sText;
			sText.Format(_T(" £”‡%d√Î"), m_nRemain / 1000);
			m_wndCountDown.SetWindowText(sText);
		}
		else
		{
			KillTimer(ID_TMR_COUNTDOWN);
			EndDialog(IDOK);
		}
	}
	CDialog::OnTimer(nIDEvent);
}
