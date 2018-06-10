// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "GameInput.h"

#include "MainFrm.h"
#include "ConfigDlg.h"
#include <Mmsystem.h>
#pragma comment(lib, "Winmm.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define WM_TRAY_NOTIFY	(WM_APP + 100)

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CTrayFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CTrayFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_COMMAND(ID_POPUP_CONFIG, OnConfig)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_COMMAND(ID_POPUP_RESET, OnPopupReset)
	//}}AFX_MSG_MAP
	ON_TRAY_MESSAGE(WM_TRAY_NOTIFY)
	ON_MESSAGE(WM_HOTKEY, OnHotKey)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	m_bStarted = FALSE;
	m_nActions = 0;
}

CMainFrame::~CMainFrame()
{	
}

void CMainFrame::OnConfig() 
{
	// TODO: Add your command handler code here
	Stop();
	CConfigDlg dlg(m_hWnd);
	DoModal(&dlg);
	DisplayBalloon();
}

void CMainFrame::OnAppAbout() 
{
	// TODO: Add your command handler code here
	CAboutDlg dlg;
	DoModal(&dlg);
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CTrayFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	CreateTray(WM_TRAY_NOTIFY, IDR_MAINFRAME, _T("GameInput"));
	DisplayBalloon();

	AfxGetManager().SetMainWnd(m_hWnd);
	if (!AfxGetManager().RegisterHotkey())
		MessageBox(_T("�޷�ע���趨�Ĵ����������뵽���ý����������á�"), NULL, MB_ICONEXCLAMATION);

	return 0;
}

void CMainFrame::Start()
{
	if (m_bStarted)
		return;

	if (!AfxGetManager().Start())
		return;
	
	::PlaySound(NULL, NULL, SND_NODEFAULT);
	::PlaySound(MAKEINTRESOURCE(IDR_SND_START), NULL, SND_RESOURCE | SND_NODEFAULT | SND_ASYNC);

	m_bStarted = TRUE;		
	SetTimer(ID_TMR_MAIN, 100, NULL);
}

void CMainFrame::Stop()
{
	if (!m_bStarted)
		return;
	
	KillTimer(ID_TMR_MAIN);
	AfxGetManager().Stop();	
	m_bStarted = FALSE;	

	::PlaySound(NULL, NULL, SND_NODEFAULT);
	::PlaySound(MAKEINTRESOURCE(IDR_SND_STOP), NULL, SND_RESOURCE | SND_NODEFAULT | SND_ASYNC);
}

LRESULT CMainFrame::OnHotKey(WPARAM wParam, LPARAM lParam)
{
	if (m_bStarted)
		Stop();
	else
		Start();
	return 0;
}

void CMainFrame::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == ID_TMR_MAIN)
	{
		if (!AfxGetManager().OnTick())
			Stop();
	}

	CTrayFrameWnd::OnTimer(nIDEvent);
}

void CMainFrame::OnDestroy() 
{
	AfxGetManager().UnregisterHotkey();
	Stop();
	CTrayFrameWnd::OnDestroy();
}

void CMainFrame::OnPopupReset() 
{
	// TODO: Add your command handler code here
	if (MessageBox(_T("�˲����������������ӵ����ݲ��ָ���Ĭ��״̬��ȷ����"), NULL, MB_ICONEXCLAMATION | MB_OKCANCEL) != IDOK)
		return;

	AfxGetManager().Reset();
	DisplayBalloon();
	MessageBox(_T("�������������ݡ�"));
}

void CMainFrame::DisplayBalloon()
{
	CString sGame = _T("��"), sScheme = _T("��");
	int nActions = 0;
	CGameData* pGame = AfxGetManager().GetActive();
	if (pGame)
	{
		sGame = pGame->GetName();
		CSchemeData* pScheme = pGame->GetActive();
		if (pScheme)
		{
			sScheme = pScheme->GetName();
			nActions = pScheme->GetActionCount();
		}
	}

	if (sGame == m_sGame && sScheme == m_sScheme && nActions == m_nActions)
		return;

	m_sGame = sGame;
	m_sScheme = sScheme;
	m_nActions = nActions;
	
	CString sText;
	sText.Format(_T("��Ϸ��%s\n������%s\n������%d"), (LPCTSTR)sGame, (LPCTSTR)sScheme, nActions);	
	ShowTrayBalloon(sText, _T("GameInput"));
	SetTrayTooltipText(CString(_T("GameInput\n")) + sText);
}
