#include "stdafx.h"
#include "GameInput.h"
#include "GameManager.h"

CGameManager::CGameManager()
{
	m_hMainWnd = NULL;
	m_pActive = NULL;
	m_dwHotkey = 0;
	m_bForeground = FALSE;
	m_nDelayTick = 0;
}

CGameManager::~CGameManager()
{
	Clear();
}

CGameData* CGameManager::GetActive()
{
	return m_pActive;
}

CSchemeData* CGameManager::GetActiveScheme()
{
	return m_pActive ? m_pActive->GetActive() : NULL;
}

void CGameManager::SetActive(CGameData *pData)
{
	if (pData == m_pActive)
		return;

	if (pData == NULL)
	{
		m_pActive = pData;
	}
	else
	{
		int nIndex = m_games.Find(pData);
		if (nIndex != -1)
			m_pActive = pData;
	}
}

void CGameManager::DeleteGame(CGameData *pData)
{
	if (pData == NULL)
		return;

	int nIndex = m_games.Find(pData);
	if (nIndex == -1)
		return;

	if (m_pActive == pData)
		m_pActive = NULL;

	m_games.RemoveAt(nIndex);
	delete pData;
}

CGameData* CGameManager::AddGame(LPCTSTR lpszName, LPCTSTR lpszTitle, LPCTSTR lpszClass)
{
	CGameData* pData = new CGameData(lpszName, lpszTitle, lpszClass);
	m_games.Add(pData);
	SetActive(pData);
	return pData;	
}

int CGameManager::GetGameCount() const
{
	return m_games.GetSize();
}

CGameData* CGameManager::GetGame(int nIndex)
{
	if (nIndex >= 0 && nIndex < m_games.GetSize())
		return m_games[nIndex];
	return NULL;
}

void CGameManager::Load()
{
	Clear();

	CIni ini(AfxGetAppEx()->GetAppDir() + _T("\\GameInput.ini"));
	m_dwHotkey = ini.GetUInt(_T("General"), _T("Hotkey"), VK_PAUSE);
	m_bForeground = ini.GetInt(_T("General"), _T("Foreground"), FALSE);
	int nActive = ini.GetInt(_T("General"), _T("Active"), 0);
	int nCount = ini.GetInt(_T("General"), _T("Games"), 0);	

	for (int i = 0; i < nCount; i++)
	{
		CString sSect;
		sSect.Format(_T("Game%d"), i + 1);
		CGameData* p = new CGameData;	
		if (p->Load(ini, sSect))
		{
			m_games.Add(p);
		}
		else
		{
			delete p;
			break;
		}

		if (nActive == i)
			m_pActive = p;
	}
}

void CGameManager::Reset()
{
	Stop();
	Clear();
	m_bForeground = FALSE;
	m_games.Add(new CGameData(_T("Ä§ÊÞÊÀ½ç"), NULL, _T("GxWindowClass")));
	m_games.Add(new CGameData(_T("°µºÚÆÆ»µÉñ3"), NULL, _T("D3 Main Window Class")));
	m_pActive = m_games[0];
}

DWORD CGameManager::GetHotkey() const
{
	return m_dwHotkey;
}

void CGameManager::SetHotkey(DWORD dwHotkey)
{
	m_dwHotkey = dwHotkey;
}

void CGameManager::Clear()
{
	m_pActive = NULL;
	for (int i = 0; i < m_games.GetSize(); i++)
	{
		m_games[i]->Clear();
		delete m_games[i];
	}
	m_games.RemoveAll();	
}

void CGameManager::Save() const
{
	CString sIniPath = AfxGetAppEx()->GetAppDir() + _T("\\GameInput.ini");
	::DeleteFile(sIniPath);
	CIni ini(sIniPath);
	ini.WriteUInt(_T("General"), _T("Hotkey"), m_dwHotkey);
	ini.WriteInt(_T("General"), _T("Foreground"), m_bForeground);
	int nCount = m_games.GetSize();
	ini.WriteInt(_T("General"), _T("Games"), nCount);
	
	for (int i = 0; i < nCount; i++)
	{	
		CGameData* pGame = m_games[i];
		if (m_pActive == pGame)
			ini.WriteInt(_T("General"), _T("Active"), i);

		CString sSect;
		sSect.Format(_T("Game%d"), i + 1);
		pGame->Save(ini, sSect);		
	}
}

BOOL CGameManager::Start()
{
	m_nDelayTick = 0;

	if (m_pActive == NULL)
		return FALSE;

	if (!m_pActive->UpdateGameWnd())
		return FALSE;
	
	if (!m_pActive->IsForeground())
		return FALSE;

	CSchemeData* pScheme = m_pActive->GetActive();
	if (pScheme == NULL)
		return FALSE;

	return pScheme->Start();
}

void CGameManager::Stop()
{
	CSchemeData* pScheme = GetActiveScheme();
	if (pScheme)
		pScheme->Stop();	
}

BOOL CGameManager::OnTick()
{
	if (m_pActive == NULL)
		return FALSE;

	CSchemeData* pScheme = GetActiveScheme();
	if (pScheme == NULL)
		return FALSE;

	if (m_pActive->IsForeground())
		return pScheme->OnTick();

	// By reaching here our game window isn't foreground
	m_nDelayTick++;
	if (m_nDelayTick % 30)
		return TRUE; // only process once every 30 ticks

	if (m_pActive->IsWindow())
	{
		if (m_bForeground)
			m_pActive->SetForeground();
	}
	else
	{		
		m_pActive->UpdateGameWnd();
	}	

	return TRUE;
}

void CGameManager::SetMainWnd(HWND hWnd)
{
	m_hMainWnd = hWnd;
}

BOOL CGameManager::RegisterHotkey()
{
	if (m_hMainWnd == NULL || m_dwHotkey == 0)
		return FALSE;
	
	UnregisterHotkey();

	if (!::RegisterHotKey(m_hMainWnd, 0, 0, m_dwHotkey))
		return FALSE;

	::RegisterHotKey(m_hMainWnd, 1, MOD_ALT, m_dwHotkey);
	::RegisterHotKey(m_hMainWnd, 2, MOD_ALT | MOD_CONTROL, m_dwHotkey);
	::RegisterHotKey(m_hMainWnd, 3, MOD_ALT | MOD_SHIFT, m_dwHotkey);
	::RegisterHotKey(m_hMainWnd, 4, MOD_ALT | MOD_CONTROL | MOD_SHIFT, m_dwHotkey);
	::RegisterHotKey(m_hMainWnd, 5, MOD_CONTROL, m_dwHotkey);
	::RegisterHotKey(m_hMainWnd, 6, MOD_CONTROL | MOD_SHIFT, m_dwHotkey);
	::RegisterHotKey(m_hMainWnd, 7, MOD_SHIFT, m_dwHotkey);
	
	return TRUE;
}

void CGameManager::UnregisterHotkey()
{
	if (m_hMainWnd == NULL)
		return;

	for (int i = 0; i < 8; i++)
		::UnregisterHotKey(m_hMainWnd, i);
}

BOOL CGameManager::GetAutoForeground() const
{
	return m_bForeground;
}

void CGameManager::SetAutoForeground(BOOL bForeground)
{
	m_bForeground = bForeground;
}