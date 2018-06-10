// ConfigDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GameInput.h"
#include "ConfigDlg.h"
#include "Includes\SystemTray.h"
#include "Includes\HotKeyCtrlEx.h"
#include "EditDlg.h"
#include "NameDlg.h"
#include "GameDlg.h"
#include "SchemeListDlg.h"
#include "HotkeyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigDlg dialog


CConfigDlg::CConfigDlg(HWND hParentWnd)
	: CDialog(CConfigDlg::IDD, GetDesktopWindow())
{
	//{{AFX_DATA_INIT(CConfigDlg)
	m_bForeground = AfxGetManager().GetAutoForeground();
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hParentWnd = hParentWnd;
}

void CConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigDlg)
	DDX_Control(pDX, IDC_SELHOTKEY, m_wndSelHotkey);
	DDX_Control(pDX, IDC_FOREGROUND, m_wndForeground);
	DDX_Control(pDX, IDC_MANAGESCHEME, m_wndManageSchemes);
	DDX_Control(pDX, IDC_GAMES, m_wndGames);
	DDX_Control(pDX, IDC_LIST1, m_wndActionList);
	DDX_Control(pDX, IDC_DELETE, m_wndDelAction);
	DDX_Control(pDX, IDC_DOWN, m_wndDownAction);
	DDX_Control(pDX, IDC_EDIT, m_wndEditAction);
	DDX_Control(pDX, IDC_SCHEMES, m_wndSchemes);
	DDX_Control(pDX, IDC_UP, m_wndUpAction);
	DDX_Control(pDX, IDC_ADD, m_wndAddAction);
	DDX_Check(pDX, IDC_FOREGROUND, m_bForeground);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigDlg, CDialog)
	//{{AFX_MSG_MAP(CConfigDlg)
	ON_CBN_SELCHANGE(IDC_SCHEMES, OnSelchangeSchemes)
	ON_BN_CLICKED(IDC_ADD, OnAddAction)
	ON_BN_CLICKED(IDC_EDIT, OnEditAction)
	ON_BN_CLICKED(IDC_DELETE, OnDelAction)
	ON_BN_CLICKED(IDC_UP, OnUpAction)
	ON_BN_CLICKED(IDC_DOWN, OnDownAction)
	ON_BN_CLICKED(IDC_SELGAME, OnSelgame)
	ON_CBN_SELCHANGE(IDC_GAMES, OnSelchangeGames)
	ON_BN_CLICKED(IDC_MANAGESCHEME, OnManagescheme)
	ON_BN_CLICKED(IDC_FOREGROUND, OnForeground)
	ON_BN_CLICKED(IDC_SELHOTKEY, OnSelhotkey)
	//}}AFX_MSG_MAP
	ON_LVEX_MESSAGE(OnListMsg)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigDlg message handlers

BOOL CConfigDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	m_wndGames.SetItemHeight(0, 17);
	m_wndSchemes.SetItemHeight(0, 17);
	m_wndSelHotkey.SetWindowText(CHotKeyCtrlEx::GetHotKeyString(AfxGetManager().GetHotkey()));

	m_wndActionList.AddColumn(_T("动作类型"), 75);
	m_wndActionList.AddColumn(_T("键值"), 150, LVEX_FMT_TEXT, LVCFMT_CENTER);
	m_wndActionList.AddColumn(_T("执行频率"), 65, LVEX_FMT_DOUBLE);
	m_wndActionList.AddColumn(_T("事后等待"), 65, LVEX_FMT_DOUBLE);
	m_wndActionList.AddColumn(_T("注释"), 150);		

	LoadGameList();
	LoadSchemeList();
	LoadActionList();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

LRESULT CConfigDlg::OnListMsg(WPARAM wParam, LPARAM lParam)
{
	LPLVEXNOTIFY p = (LPLVEXNOTIFY)wParam;
	if (p->nNotifyType == LVEX_WM_SELCHANGE)
	{
		int nSel = p->nItem;
		m_wndEditAction.EnableWindow(nSel != -1);
		m_wndDelAction.EnableWindow(nSel != -1);
		m_wndUpAction.EnableWindow(nSel != -1);
		m_wndDownAction.EnableWindow(nSel != -1);
		m_wndUpAction.EnableWindow(nSel > 0);
		m_wndDownAction.EnableWindow(nSel != -1 && nSel < m_wndActionList.GetItemCount() - 1);
	}
	else if (p->nNotifyType == LVEX_WM_DBLCLICK)
	{
		OnEditAction();
	}
	return 0;
}

void CConfigDlg::OnAddAction() 
{
	// TODO: Add your control notification handler code here
	CSchemeData* pScheme = (CSchemeData*)AfxGetComboSelectedData(&m_wndSchemes);
	if (pScheme == NULL)
		return;

	CEditDlg dlg(NULL, pScheme->IsRunOnce(), this);
	if (dlg.DoModal() != IDOK)
		return;

	pScheme->AddAction(dlg.m_action);
	int nIndex = m_wndActionList.AddItem(NULL);
	UpdateActionRow(nIndex, dlg.m_action, pScheme->IsRunOnce());
	m_wndActionList.SelectItem(nIndex);
	m_wndActionList.SetFocus();
}

void CConfigDlg::OnEditAction() 
{
	// TODO: Add your control notification handler code here
	int nSel = m_wndActionList.GetSelection();
	if (nSel == -1)
		return;

	CSchemeData* pScheme = (CSchemeData*)AfxGetComboSelectedData(&m_wndSchemes);
	if (pScheme == NULL)
		return;

	ACTIONDATA& action = pScheme->GetAction(nSel);
	CEditDlg dlg(&action, pScheme->IsRunOnce(), this);
	if (dlg.DoModal() != IDOK)
		return;

	action = dlg.m_action;
	UpdateActionRow(nSel, dlg.m_action, pScheme->IsRunOnce());	
}

void CConfigDlg::OnDelAction() 
{
	// TODO: Add your control notification handler code here
	int nSel = m_wndActionList.GetSelection();
	if (nSel == -1)
		return;

	CSchemeData* pScheme = (CSchemeData*)AfxGetComboSelectedData(&m_wndSchemes);
	if (pScheme == NULL)
		return;

	pScheme->DeleteAction(nSel);
	m_wndActionList.DeleteItem(nSel);

	if (nSel >= m_wndActionList.GetItemCount())
		nSel--;

	m_wndActionList.SelectItem(nSel);
	m_wndActionList.SetFocus();	
}

void CConfigDlg::OnSelgame() 
{
	// TODO: Add your control notification handler code here
	CGameDlg dlg(this);
	dlg.DoModal();
	if (dlg.m_bChanged)
		LoadGameList();
}

void CConfigDlg::OnSelchangeGames() 
{
	// TODO: Add your control notification handler code here
	CGameData* pGame = (CGameData*)AfxGetComboSelectedData(&m_wndGames);
	AfxGetManager().SetActive(pGame);
	m_wndSchemes.ResetContent();
	m_wndActionList.DeleteAllItems();
	LoadSchemeList();	
}

void CConfigDlg::OnSelchangeSchemes() 
{
	// TODO: Add your control notification handler code here
	CGameData* pGame = AfxGetManager().GetActive();
	if (pGame == NULL)
		return;
	
	CSchemeData* pScheme = (CSchemeData*)AfxGetComboSelectedData(&m_wndSchemes);
	pGame->SetActive(pScheme);

	m_wndActionList.DeleteAllItems();
	LoadActionList();	
	m_wndActionList.SetFocus();
	m_wndAddAction.EnableWindow(pScheme != NULL);
}

void CConfigDlg::LoadGameList()
{
	m_wndGames.ResetContent();

	for (int i = 0; i < AfxGetManager().GetGameCount(); i++)
	{
		CGameData* p = AfxGetManager().GetGame(i);
		int nIndex = m_wndGames.AddString(p->GetName());
		m_wndGames.SetItemData(nIndex, (DWORD)p);
	}

	AfxFindComboByData(&m_wndGames, (DWORD)AfxGetManager().GetActive(), TRUE);

	LoadSchemeList();
	LoadActionList();
}

void CConfigDlg::LoadSchemeList()
{
	m_wndSchemes.ResetContent();

	CGameData* pGame = AfxGetManager().GetActive();
	if (pGame == NULL)
		return;

	for (int i = 0; i < pGame->GetSchemeCount(); i++)
	{
		CSchemeData* p = pGame->GetScheme(i);
		int nIndex = m_wndSchemes.AddString(p->GetName());
		m_wndSchemes.SetItemData(nIndex, (DWORD)p);
	}

	AfxFindComboByData(&m_wndSchemes, (DWORD)pGame->GetActive(), TRUE);
	LoadActionList();
	
	m_wndAddAction.EnableWindow(pGame != NULL && pGame->GetActive() != NULL);
	m_wndManageSchemes.EnableWindow(pGame != NULL);
}

void CConfigDlg::LoadActionList()
{
	m_wndActionList.DeleteAllItems();
	m_wndEditAction.EnableWindow(FALSE);

	CSchemeData* pScheme = (CSchemeData*)AfxGetComboSelectedData(&m_wndSchemes);
	if (pScheme == NULL)
		return;

	for (int i = 0; i < pScheme->GetActionCount(); i++)
	{
		ACTIONDATA& action = pScheme->GetAction(i);
		m_wndActionList.AddItem(NULL);
		UpdateActionRow(i, action, pScheme->IsRunOnce());
	}	
}

void CConfigDlg::UpdateActionRow(int nIndex, const ACTIONDATA &action, BOOL bRunOnce)
{
	if (action.nType == ACTION_KEY_STROKE)
		m_wndActionList.SetFieldText(nIndex, 0, _T("键盘击键"));
	else if (action.nType == ACTION_KEY_DOWN)
		m_wndActionList.SetFieldText(nIndex, 0, _T("键盘长按"));
	else if (action.nType == ACTION_MOUSE_CLICK)
		m_wndActionList.SetFieldText(nIndex, 0, _T("鼠标点击"));
	else if (action.nType == ACTION_MOUSE_DOWN)
		m_wndActionList.SetFieldText(nIndex, 0, _T("鼠标长按"));

	CString sMods, sKeyName;

	if (action.nMods & MOD_CONTROL)
		sMods = _T("Ctrl + ");

	if (action.nMods & MOD_SHIFT)
		sMods += _T("Shift + ");

	if (action.nMods & MOD_ALT)
		sMods += _T("Alt + ");

	if (action.nType == ACTION_MOUSE_CLICK || action.nType == ACTION_MOUSE_DOWN)
	{
		if (action.nButton == SIM_MOUSE_RIGHT)
			sKeyName = _T("右键");
		else if (action.nButton == SIM_MOUSE_MIDDLE)
			sKeyName = _T("中键");
		else
			sKeyName = _T("左键");
	}
	else
	{
		sKeyName = CHotKeyCtrlEx::GetHotKeyString((WORD)action.nKeyCode, 0);
	}

	m_wndActionList.SetFieldText(nIndex, 1, sMods + sKeyName);

	if (!bRunOnce && (action.nType == ACTION_KEY_STROKE || action.nType == ACTION_MOUSE_CLICK))
		m_wndActionList.SetFieldLong(nIndex, 2, action.nInterval);
	else
		m_wndActionList.SetFieldText(nIndex, 2, NULL);

	m_wndActionList.SetFieldLong(nIndex, 3, action.nPostDelay);
	m_wndActionList.SetFieldText(nIndex, 4, action.szDesc);
}

void CConfigDlg::OnUpAction() 
{
	// TODO: Add your control notification handler code here
	CSchemeData* pScheme = (CSchemeData*)AfxGetComboSelectedData(&m_wndSchemes);
	if (pScheme == NULL)
		return;

	int nIdx = m_wndActionList.GetSelection();
	if (pScheme->SwapActions(nIdx, nIdx - 1))
		m_wndActionList.SwapItems(nIdx, nIdx - 1);

	m_wndActionList.SetFocus();
}

void CConfigDlg::OnDownAction() 
{
	// TODO: Add your control notification handler code here	
	CSchemeData* pScheme = (CSchemeData*)AfxGetComboSelectedData(&m_wndSchemes);
	if (pScheme == NULL)
		return;

	int nIdx = m_wndActionList.GetSelection();
	if (pScheme->SwapActions(nIdx, nIdx + 1))
		m_wndActionList.SwapItems(nIdx, nIdx + 1);

	m_wndActionList.SetFocus();
}

void CConfigDlg::OnManagescheme() 
{
	// TODO: Add your control notification handler code here
	CGameData* pGame = (CGameData*)AfxGetComboSelectedData(&m_wndGames);
	if (pGame == NULL)
		return;

	CSchemeListDlg dlg(AfxGetManager().GetActive(), this);
	dlg.DoModal();

	if (dlg.m_bChanged)
		LoadSchemeList();
}

void CConfigDlg::OnForeground() 
{
	// TODO: Add your control notification handler code here
	m_bForeground = m_wndForeground.GetCheck();
	AfxGetManager().SetAutoForeground(m_bForeground);
}

void CConfigDlg::OnSelhotkey() 
{
	// TODO: Add your control notification handler code here
	CHotkeyDlg dlg(this);
	if (dlg.DoModal() != IDOK || AfxGetManager().GetHotkey() == dlg.m_dwHotkey)
		return;

	CString sKeyName = CHotKeyCtrlEx::GetHotKeyString(dlg.m_dwHotkey);
	AfxGetManager().SetHotkey(dlg.m_dwHotkey);

	if (AfxGetManager().RegisterHotkey())
	{
		m_wndSelHotkey.SetWindowText(sKeyName);
	}
	else
	{
		CString sMsg;
		sMsg.Format(_T("快捷键\"%s\"已被其它程序占用，请另选快捷键。"), (LPCTSTR)sKeyName);
		MessageBox(sMsg, NULL, MB_ICONEXCLAMATION);
	}	
}
