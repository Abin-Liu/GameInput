// SchemeListDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GameInput.h"
#include "SchemeListDlg.h"
#include "NameDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSchemeListDlg dialog


CSchemeListDlg::CSchemeListDlg(CGameData* pGame, CWnd* pParent /*=NULL*/)
	: CDialog(CSchemeListDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSchemeListDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_pGame = pGame;
	m_bChanged = FALSE;
}


void CSchemeListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSchemeListDlg)
	DDX_Control(pDX, IDC_REMOVE, m_wndRemove);
	DDX_Control(pDX, IDC_LIST1, m_wndList);
	DDX_Control(pDX, IDC_EDIT, m_wndEdit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSchemeListDlg, CDialog)
	//{{AFX_MSG_MAP(CSchemeListDlg)
	ON_BN_CLICKED(IDC_EDIT, OnEdit)
	ON_BN_CLICKED(IDC_REMOVE, OnRemove)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	//}}AFX_MSG_MAP
	ON_LVEX_MESSAGE(OnListNotify)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSchemeListDlg message handlers

BOOL CSchemeListDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CString sTitle;
	sTitle.Format(_T("方案列表：%s"), (LPCTSTR)(m_pGame ? m_pGame->GetName() : _T("")));
	SetWindowText(sTitle);
	m_wndList.AddColumn(_T("方案名称"), 220);
	m_wndList.AddColumn(_T("执行方式"), 75);

	if (m_pGame)
	{
		for (int i = 0; i < m_pGame->GetSchemeCount(); i++)
		{
			CSchemeData* p = m_pGame->GetScheme(i);
			int nIndex = m_wndList.AddItem(p->GetName(), (DWORD)p);
			m_wndList.SetFieldText(nIndex, 1, p->IsRunOnce() ? _T("一次性") : _T("循环"));
		}
	}	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

LRESULT CSchemeListDlg::OnListNotify(WPARAM wParam, LPARAM lParam)
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

void CSchemeListDlg::OnAdd() 
{
	// TODO: Add your control notification handler code here
	if (m_pGame == NULL)
		return;

	CNameDlg dlg(NULL, FALSE, this);
	if (dlg.DoModal() != IDOK)
		return;

	CSchemeData* pNewData = m_pGame->AddScheme(dlg.m_sName);	
	int nIndex = m_wndList.AddItem(dlg.m_sName, (DWORD)pNewData);
	m_wndList.SetFieldText(nIndex, 1, pNewData->IsRunOnce() ? _T("一次性") : _T("循环"));
	m_bChanged = TRUE;
	EndDialog(IDOK);
}

void CSchemeListDlg::OnEdit() 
{
	// TODO: Add your control notification handler code here
	if (m_pGame == NULL)
		return;
	
	int nSel = m_wndList.GetSelection();
	if (nSel == -1)
		return;

	CSchemeData* p = (CSchemeData*)m_wndList.GetItemData(nSel);
	if (p == NULL)
		return;

	CString sName = m_wndList.GetFieldText(nSel, 0);
	CNameDlg dlg(p->GetName(),p->IsRunOnce(), this);
	if (dlg.DoModal() != IDOK)
		return;

	p->SetName(dlg.m_sName);
	p->SetRunOnce(dlg.m_nType);
	m_wndList.SetFieldText(nSel, 0, dlg.m_sName);
	m_wndList.SetFieldText(nSel, 1, p->IsRunOnce() ? _T("一次性") : _T("循环"));
	m_bChanged = TRUE;
	EndDialog(IDOK);
}

void CSchemeListDlg::OnRemove() 
{
	// TODO: Add your control notification handler code here
	if (m_pGame == NULL)
		return;

	int nSel = m_wndList.GetSelection();
	if (nSel == -1)
		return;

	CSchemeData* p = (CSchemeData*)m_wndList.GetItemData(nSel);
	if (p == NULL)
		return;

	CString sName = m_wndList.GetFieldText(nSel, 0);
	CString sMsg;
	sMsg.Format(_T("即将删除方案\"%s\"，所有隶属于此方案的动作都将被一起删除，且无法恢复。确定要删除吗？"), (LPCTSTR)sName);
	if (MessageBox(sMsg, _T("删除确认"), MB_ICONEXCLAMATION | MB_YESNO | MB_DEFBUTTON2) != IDYES)
		return;

	m_pGame->DeleteScheme(p);
	m_wndList.DeleteItem(nSel);
	m_bChanged = TRUE;
}