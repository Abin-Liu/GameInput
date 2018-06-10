// EditDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GameInput.h"
#include "EditDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditDlg dialog


CEditDlg::CEditDlg(const ACTIONDATA* pAction, BOOL bRunOnce, CWnd* pParent /*=NULL*/)
	: CDialog(CEditDlg::IDD, pParent)
{
	if (pAction)
	{
		::memcpy(&m_action, pAction, sizeof(ACTIONDATA));
		if (m_action.nType < ACTION_KEY_STROKE || m_action.nType > ACTION_MOUSE_DOWN )
			m_action.nType = ACTION_KEY_STROKE;		
	}
	else
	{
		::memset(&m_action, 0, sizeof(ACTIONDATA));
		m_action.nInterval = 1000;
	}
	
	//{{AFX_DATA_INIT(CEditDlg)
	m_sDesc = m_action.szDesc;
	m_nMouseBtn = m_action.nButton;	
	m_bAlt = (m_action.nMods & MOD_ALT) != 0;
	m_bCtrl = (m_action.nMods & MOD_CONTROL) != 0;
	m_bShift = (m_action.nMods & MOD_SHIFT) != 0;
	m_nType = m_action.nType;
	m_nInterval = m_action.nInterval;
	m_nPostDelay = m_action.nPostDelay;
	//}}AFX_DATA_INIT

	m_bRunOnce = bRunOnce;
}


void CEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditDlg)
	DDX_Control(pDX, IDC_INTERVALLBL2, m_wndIntLbl2);
	DDX_Control(pDX, IDC_INTERVALLBL1, m_wndIntLbl1);
	DDX_Control(pDX, IDC_TYPE, m_wndType);
	DDX_Control(pDX, IDC_MOUSEBTNS, m_wndMouseBtns);
	DDX_Control(pDX, IDC_CODE, m_wndCode);
	DDX_Control(pDX, IDC_DESC, m_wndDesc);
	DDX_Control(pDX, IDC_INTERVAL, m_wndInterval);
	DDX_Control(pDX, IDC_POSTWAIT, m_wndPostWait);
	DDX_Text(pDX, IDC_DESC, m_sDesc);
	DDV_MaxChars(pDX, m_sDesc, 32);
	DDX_CBIndex(pDX, IDC_MOUSEBTNS, m_nMouseBtn);
	DDX_Check(pDX, IDC_ALT, m_bAlt);
	DDX_Check(pDX, IDC_CTRL, m_bCtrl);
	DDX_Check(pDX, IDC_SHIFT, m_bShift);
	DDX_CBIndex(pDX, IDC_TYPE, m_nType);
	DDX_Text(pDX, IDC_INTERVAL, m_nInterval);
	DDV_MinMaxInt(pDX, m_nInterval, 0, 10000000);
	DDX_Text(pDX, IDC_POSTWAIT, m_nPostDelay);
	DDV_MinMaxInt(pDX, m_nPostDelay, 0, 60000);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEditDlg, CDialog)
	//{{AFX_MSG_MAP(CEditDlg)
	ON_CBN_SELCHANGE(IDC_TYPE, OnSelchangeType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditDlg message handlers

BOOL CEditDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_wndType.SetItemHeight(0, 17);
	m_wndMouseBtns.SetItemHeight(0, 17);
	AfxAddComboLine(&m_wndMouseBtns, _T("×ó¼ü"), SIM_MOUSE_LEFT);
	AfxAddComboLine(&m_wndMouseBtns, _T("ÓÒ¼ü"), SIM_MOUSE_RIGHT);
	AfxAddComboLine(&m_wndMouseBtns, _T("ÖÐ¼ü"), SIM_MOUSE_MIDDLE);
	AfxFindComboByData(&m_wndMouseBtns, m_action.nButton, TRUE);

	m_wndCode.SetRules(-1, 0);
	m_wndCode.SetHotKey(m_action.nKeyCode);
	m_wndMouseBtns.ShowWindow(m_nType == ACTION_MOUSE_CLICK || m_nType == ACTION_MOUSE_DOWN ? SW_SHOW : SW_HIDE);
	m_wndCode.ShowWindow(m_nType == ACTION_KEY_STROKE || m_nType == ACTION_KEY_DOWN ? SW_SHOW : SW_HIDE);

	m_wndInterval.EnableWindow(!m_bRunOnce && (m_nType == ACTION_KEY_STROKE || m_nType == ACTION_MOUSE_CLICK));
	m_wndIntLbl1.EnableWindow(!m_bRunOnce && (m_nType == ACTION_KEY_STROKE || m_nType == ACTION_MOUSE_CLICK));
	m_wndIntLbl2.EnableWindow(!m_bRunOnce && (m_nType == ACTION_KEY_STROKE || m_nType == ACTION_MOUSE_CLICK));
	
	if (m_bRunOnce)
		m_wndInterval.EnableWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEditDlg::OnOK() 
{
	// TODO: Add extra validation here
	if (!UpdateData(TRUE))
		return;

	m_action.nType = m_nType;	
	m_action.nKeyCode = m_wndCode.GetHotKey();
	m_action.nButton = AfxGetComboSelectedData(&m_wndMouseBtns);

	m_action.nMods = 0;

	if (m_bAlt && m_action.nKeyCode != VK_MENU)
		m_action.nMods |= MOD_ALT;

	if (m_bShift && m_action.nKeyCode != VK_SHIFT)
		m_action.nMods |= MOD_SHIFT;

	if (m_bCtrl && m_action.nKeyCode != VK_CONTROL)
		m_action.nMods |= MOD_CONTROL;
	
	m_action.nInterval = m_nInterval;
	m_action.nPostDelay = m_nPostDelay;	

	m_sDesc.TrimLeft();
	m_sDesc.TrimRight();
	_tcsncpy(m_action.szDesc, m_sDesc, 32);
	EndDialog(IDOK);
}

void CEditDlg::OnSelchangeType() 
{
	// TODO: Add your control notification handler code here
	int nType = m_wndType.GetCurSel();
	m_wndMouseBtns.ShowWindow(nType == ACTION_MOUSE_CLICK || nType == ACTION_MOUSE_DOWN ? SW_SHOW : SW_HIDE);
	m_wndCode.ShowWindow(nType == ACTION_KEY_STROKE || nType == ACTION_KEY_DOWN ? SW_SHOW : SW_HIDE);
	m_wndInterval.EnableWindow(!m_bRunOnce && (nType == ACTION_KEY_STROKE || nType == ACTION_MOUSE_CLICK));
	m_wndIntLbl1.EnableWindow(!m_bRunOnce && (nType == ACTION_KEY_STROKE || nType == ACTION_MOUSE_CLICK));
	m_wndIntLbl2.EnableWindow(!m_bRunOnce && (nType == ACTION_KEY_STROKE || nType == ACTION_MOUSE_CLICK));
}
