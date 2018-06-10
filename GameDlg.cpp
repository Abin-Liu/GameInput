// GameDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GameInput.h"
#include "GameDlg.h"
#include "GameDetailDlg.h"
#include "CaptureDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGameDlg dialog


CGameDlg::CGameDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGameDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGameDlg)
	//}}AFX_DATA_INIT
	m_bChanged = FALSE;
}


void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGameDlg)
	DDX_Control(pDX, IDC_EDIT, m_wndEdit);
	DDX_Control(pDX, IDC_REMOVE, m_wndRemove);
	DDX_Control(pDX, IDC_LIST1, m_wndList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGameDlg, CDialog)
	//{{AFX_MSG_MAP(CGameDlg)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_REMOVE, OnRemove)
	ON_BN_CLICKED(IDC_EDIT, OnEdit)
	ON_BN_CLICKED(IDC_CAPTURE, OnCapture)
	//}}AFX_MSG_MAP
	ON_LVEX_MESSAGE(OnListNotify)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGameDlg message handlers

BOOL CGameDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_wndList.AddColumn(_T("程序名"), 150);
	m_wndList.AddColumn(_T("标题栏文字"), 220);
	m_wndList.AddColumn(_T("窗口类名"), 150);
	FillList();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CGameDlg::OnAdd() 
{
	// TODO: Add your control notification handler code here
	CGameDetailDlg dlg(NULL, NULL, NULL, this);
	if (dlg.DoModal() != IDOK)
		return;

	CGameData* pNewGame = AfxGetManager().AddGame(dlg.m_sName, dlg.m_sText, dlg.m_sClass);

	int nIndex = m_wndList.AddItem(dlg.m_sName, (DWORD)pNewGame);
	m_wndList.SetFieldText(nIndex, 1, dlg.m_sText);
	m_wndList.SetFieldText(nIndex, 2, dlg.m_sClass);
	m_wndList.SelectItem(nIndex);
	m_wndList.SetFocus();
	m_bChanged = TRUE;
}

void CGameDlg::OnRemove()
{
	// TODO: Add your control notification handler code here
	int nSel = m_wndList.GetSelection();
	if (nSel == -1)
		return;

	CGameData* p = (CGameData*)m_wndList.GetItemData(nSel);
	if (p == NULL)
		return;

	CString sMsg;
	sMsg.Format(_T("即将删除游戏\"%s\"，所有在此游戏下创建的方案及动作都将被一起删除，且无法恢复。确定要删除吗？"), (LPCTSTR)p->GetName());
	if (MessageBox(sMsg, _T("删除确认"), MB_ICONEXCLAMATION | MB_YESNO | MB_DEFBUTTON2) != IDYES)
		return;

	AfxGetManager().DeleteGame(p);	
	m_wndList.DeleteItem(nSel);
	m_bChanged = TRUE;
}

void CGameDlg::OnEdit() 
{
	// TODO: Add your control notification handler code here
	int nSel = m_wndList.GetSelection();
	if (nSel == -1)
		return;

	CGameData* p = (CGameData*)m_wndList.GetItemData(nSel);
	if (p == NULL)
		return;	
	
	CGameDetailDlg dlg(p->GetName(), p->GetTitle(), p->GetClass(), this);
	if (dlg.DoModal() != IDOK)
		return;	

	p->Edit(dlg.m_sName, dlg.m_sText, dlg.m_sClass);	
	m_wndList.SetFieldText(nSel, 0, dlg.m_sName);
	m_wndList.SetFieldText(nSel, 1, dlg.m_sText);
	m_wndList.SetFieldText(nSel, 2, dlg.m_sClass);
	m_wndList.SetFocus();
	m_bChanged = TRUE;
}

void CGameDlg::FillList()
{
	m_wndList.DeleteAllItems();
	for (int i = 0; i < AfxGetManager().GetGameCount(); i++)
	{
		CGameData* p = AfxGetManager().GetGame(i);
		int nIndex = m_wndList.AddItem(p->GetName(), (DWORD)p);
		m_wndList.SetFieldText(nIndex, 1, p->GetTitle());
		m_wndList.SetFieldText(nIndex, 2, p->GetClass());
	}	
}

LRESULT CGameDlg::OnListNotify(WPARAM wParam, LPARAM lParam)
{
	LPLVEXNOTIFY lpvn = (LPLVEXNOTIFY)wParam;
	ASSERT(lpvn);

	switch (lpvn->nNotifyType)
	{
	case LVEX_WM_SELCHANGE:		
		m_wndEdit.EnableWindow(lpvn->nItem >= 0);
		m_wndRemove.EnableWindow(lpvn->nItem >= 0);
		break;
		
	case LVEX_WM_DBLCLICK:
		OnEdit();
		break;	

	default:
		break;
	}

	return (LRESULT)0;
}

void CGameDlg::OnCapture() 
{
	// TODO: Add your control notification handler code here
	CCaptureDlg capdlg(this);
	if (capdlg.DoModal() != IDOK)
		return;

	HWND hWnd = ::GetForegroundWindow();
	SetForegroundWindow();
	
	if (hWnd == m_hWnd || hWnd == ::GetDesktopWindow())
	{
		MessageBox(_T("没有发现置于前台的任何程序窗口。"));
		return;
	}

	TCHAR szTitle[256] = _T("");
	TCHAR szClass[256] = _T("");

	::GetWindowText(hWnd, szTitle, 255);		
	::GetClassName(hWnd, szClass, 255);

	CGameDetailDlg dlg(szTitle, szTitle, szClass, this);
	if (dlg.DoModal() != IDOK)
		return;

	CGameData* pNewGame = AfxGetManager().AddGame(dlg.m_sName, dlg.m_sText, dlg.m_sClass);
	
	int nIndex = m_wndList.AddItem(dlg.m_sName, (DWORD)pNewGame);
	m_wndList.SetFieldText(nIndex, 1, dlg.m_sText);
	m_wndList.SetFieldText(nIndex, 2, dlg.m_sClass);
	m_wndList.SelectItem(nIndex);
	m_wndList.SetFocus();
	m_bChanged = TRUE;
}
