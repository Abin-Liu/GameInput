// Scheme.cpp: implementation of the CScheme class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GameInput.h"
#include "Scheme.h"
#include "Includes\InputThread.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CScheme::CScheme()
{
	::memset(m_szName, 0, SCHEME_NAME_LEN + 1);	
}

CScheme::CScheme(LPCSTR lpszName)
{
	::memset(m_szName, 0, SCHEME_NAME_LEN + 1);
	::memcpy(m_szName, lpszName, SCHEME_NAME_LEN);
}

CScheme::CScheme(const CScheme& rhs)
{
	::memcpy(m_szName, rhs.m_szName, SCHEME_NAME_LEN + 1);
	m_aData.Copy(rhs.m_aData);
}

CScheme::~CScheme()
{
}

const CScheme& CScheme::operator=(const CScheme& rhs)
{
	::memcpy(m_szName, rhs.m_szName, SCHEME_NAME_LEN + 1);
	m_aData.Copy(rhs.m_aData);
	return *this;
}

LPCSTR CScheme::GetName() const
{
	return m_szName;
}

int CScheme::GetCount() const
{
	return m_aData.GetSize();
}

SCHEMEDATA& CScheme::GetData(int nIndex)
{
	return m_aData.ElementAt(nIndex);
}

int CScheme::AddData(const SCHEMEDATA& data)
{	
	return m_aData.Add(data);
}

BOOL CScheme::DeleteData(int nIndex)
{
	if (nIndex < 0 || nIndex >= m_aData.GetSize())
		return FALSE;

	m_aData.RemoveAt(nIndex);
	return TRUE;
}

BOOL CScheme::MoveData(int nIndex, BOOL bMoveUp)
{
	if (nIndex < 0 || nIndex >= m_aData.GetSize())
		return FALSE;

	int nTarget = bMoveUp ? nIndex - 1 : nIndex + 1;
	if (nTarget < 0 || nTarget >= m_aData.GetSize())
		return FALSE;
	
	SCHEMEDATA data = m_aData[nTarget];
	m_aData[nTarget] = m_aData[nIndex];
	m_aData[nIndex] = data;
	return TRUE;
}

BOOL CScheme::Load(int nIndex)
{
	::memset(m_szName, 0, SCHEME_NAME_LEN + 1);
	m_aData.RemoveAll();

	CIni& ini = AfxGetIni();

	CString sSection;
	sSection.Format(_T("Scheme %d"), nIndex);
	ini.GetString(sSection, _T("Name"), m_szName, SCHEME_NAME_LEN);

	int nCount = min(ini.GetInt(sSection, _T("Actions"), 0), SCHEME_MAX);
	CStringArray arr;
	CString sKey;
	for (int i = 0; i < nCount; i++)
	{
		sKey.Format(_T("Action %d"), i);		
		ini.GetArray(sSection, sKey, &arr, _T("|"));
		int nSegs = arr.GetSize();
		if (nSegs < 5)
			break;

		SCHEMEDATA data = { 0 };
		data.nAction = _ttoi(arr[0]);
		data.dwCode = _tcstoul(arr[1], NULL, 10);
		data.dwInterval = _tcstoul(arr[2], NULL, 10);
		data.dwPreWait = _tcstoul(arr[3], NULL, 10);
		data.dwPostWait = _tcstoul(arr[4], NULL, 10);

		if (nSegs > 5)
			_tcsncpy(data.szDesc, arr[5], SCHEME_NAME_LEN);		

		if (data.nAction < 0 || data.nAction >= NUM_SCHEME_ACTIONS)
			data.nAction = 0;

		m_aData.Add(data);
	}

	return TRUE;
}

BOOL CScheme::Save(int nIndex)
{
	int nCount = m_aData.GetSize();

	CIni& ini = AfxGetIni();

	CString sSection;
	sSection.Format(_T("Scheme %d"), nIndex);
	ini.WriteString(sSection, _T("Name"), m_szName);
	ini.WriteInt(sSection, _T("Actions"), nCount);	

	CString sKey, sLine;
	for (int i = 0; i < nCount; i++)
	{
		sKey.Format(_T("Action %d"), i);
		SCHEMEDATA& data = m_aData.ElementAt(i);
		sLine.Format(_T("%d|%u|%u|%u|%u|%s"), data.nAction, data.dwCode, data.dwInterval, data.dwPreWait, data.dwPostWait, data.szDesc);
		ini.WriteString(sSection, sKey, sLine);
	}
	
	return TRUE;
}

DWORD CScheme::PreExecuteAction(const SCHEMEDATA &data)
{
	if (data.dwLastProc + data.dwInterval > ::GetTickCount())
		return -1;

	return data.dwPreWait;
}

DWORD CScheme::ExecuteAction(SCHEMEDATA &data)
{
	CInputThread::ReleaseAllKeys();
	
	if (data.nAction == 0)
	{
		// 0: Key stroke
		CInputThread::KeyStroke(data.dwCode);
	}
	else
	{
		// 1, 2, 3: Mouse left, right, middle
		WORD wMod = HIWORD(data.dwCode);
		if (wMod)
			CInputThread::KeyDown(wMod, 0);

		if (data.nAction <= 3)
		{
			int nButton;
			if (data.nAction == 2)
				nButton = CInputThread::MOUSE_RIGHT;
			else if (data.nAction == 3)
				nButton = CInputThread::MOUSE_MIDDLE;
			else
				nButton = CInputThread::MOUSE_LEFT;

			CInputThread::MouseClick(nButton);
		}
		else
		{
			CInputThread::MouseWheel(data.nAction == 4);
		}

		if (wMod)
			CInputThread::KeyUp(wMod, 0);
	}	
	
	data.dwLastProc = ::GetTickCount();
	return data.dwPostWait;
}

CSchemeManager::CSchemeManager()
{
	m_nActive = -1;
	::memset(&m_selGame, 0, sizeof(m_selGame));
	m_dwHotkey = VK_PAUSE;
}

CSchemeManager::~CSchemeManager()
{
}

BOOL CSchemeManager::Load()
{
	CIni& ini = AfxGetIni();
	m_dwHotkey = ini.GetInt(_T("General"), _T("Hotkey"), VK_PAUSE);
	
	m_aGameData.RemoveAll();
	int i = 0;

	::memset(&m_selGame, 0, sizeof(m_selGame));
	int nCount = min(ini.GetInt(_T("General"), _T("Game Count"), 0), SCHEME_MAX);

	if (nCount > 0)
	{
		for (i = 1; i <= nCount; i++)
		{
			GAMEDATA game = { 0 };
			CString sSection;
			sSection.Format(_T("Game %d"), i);
			ini.GetString(sSection, _T("Name"), game.szName, GAME_TEXT_LEN);
			ini.GetString(sSection, _T("Title"), game.szTitle, GAME_TEXT_LEN);
			ini.GetString(sSection, _T("Class"), game.szClass, GAME_TEXT_LEN);	
			m_aGameData.Add(game);
		}

		SelectGame(ini.GetString(_T("General"), _T("Selected Game")));
	}
	else
	{
		ResetGames();
	}	

	m_aSchemes.RemoveAll();	
	nCount = min(ini.GetInt(_T("General"), _T("Scheme Count"), 0), SCHEME_MAX);

	for (i = 1; i <= nCount; i++)
	{
		CScheme scheme;
		scheme.Load(i);
		m_aSchemes.Add(scheme);
	}

	m_nActive = AfxGetIni().GetInt(_T("General"), _T("Selected Scheme Index"), -1);
	if (m_nActive < 0 || m_nActive >= nCount)
		m_nActive = -1;	
	
	return TRUE;
}

void CSchemeManager::Save()
{	
	CIni& ini = AfxGetIni();
	::DeleteFile(ini.GetPathName());

	ini.WriteInt(_T("General"), _T("Hotkey"), m_dwHotkey);

	int i  = 0;
	int nCount = m_aGameData.GetSize();
	ini.WriteInt(_T("General"), _T("Game Count"), nCount);
	ini.WriteString(_T("General"), _T("Selected Game"), m_selGame.szName);

	for (i = 1; i <= nCount; i++)
	{
		const GAMEDATA& game = m_aGameData[i - 1];
		CString sSection;
		sSection.Format(_T("Game %d"), i);
		ini.WriteString(sSection, _T("Name"), game.szName);
		ini.WriteString(sSection, _T("Title"), game.szTitle);
		ini.WriteString(sSection, _T("Class"), game.szClass);		
	}

	nCount = m_aSchemes.GetSize();
	ini.WriteInt(_T("General"), _T("Scheme Count"), nCount);
	ini.WriteInt(_T("General"), _T("Selected Scheme Index"), m_nActive);

	for (i = 1; i <= nCount; i++)
		m_aSchemes[i - 1].Save(i);	
}

int CSchemeManager::GetActive() const
{
	return m_nActive;
}

BOOL CSchemeManager::SetActive(int nIndex)
{
	if (nIndex < 0 || nIndex >= m_aSchemes.GetSize())
		return FALSE;

	m_nActive = nIndex;
	return TRUE;
}

CScheme* CSchemeManager::GetActiveData()
{
	if (m_nActive < 0 || m_nActive >= m_aSchemes.GetSize())
		return NULL;

	return &m_aSchemes.ElementAt(m_nActive);
}

CSchemeArray& CSchemeManager::GetSchemes()
{
	return m_aSchemes;
}

CGameDataArray& CSchemeManager::GetGames()
{
	return m_aGameData;
}

BOOL CSchemeManager::AddGame(LPCTSTR lpszName, LPCTSTR lpszTitle, LPCTSTR lpszClass)
{
	GAMEDATA game = { 0 };
	_tcsncpy(game.szName, lpszName, GAME_TEXT_LEN);
	_tcsncpy(game.szTitle, lpszTitle, GAME_TEXT_LEN);
	_tcsncpy(game.szClass, lpszClass, GAME_TEXT_LEN);
	m_aGameData.Add(game);
	return TRUE;
}

void CSchemeManager::SelectGame(LPCTSTR lpszName)
{
	if (_tcsicmp(m_selGame.szName, lpszName) == 0)
		return;

	int nIndex = FindGame(lpszName);
	if (nIndex != -1)
		m_selGame = m_aGameData[nIndex];
}

const GAMEDATA& CSchemeManager::GetSelectedGame() const
{
	return m_selGame;
}

BOOL CSchemeManager::DeleteGame(LPCTSTR lpszName)
{
	int nIndex = FindGame(lpszName);
	if (nIndex == -1)
		return FALSE;

	GAMEDATA game = m_aGameData[nIndex];
	m_aGameData.RemoveAt(nIndex);

	if (_tcsicmp(m_selGame.szName, lpszName) == 0)
		::memset(&m_selGame, 0, sizeof(GAMEDATA));	

	return TRUE;
}

void CSchemeManager::ResetGames()
{
	m_aGameData.RemoveAll();
	AddGame(_T("魔兽世界"), _T(""), _T("GxWindowClass"));
	AddGame(_T("Diablo III"), _T(""), _T("D3 Main Window Class"));
	SelectGame(_T("魔兽世界"));
}

BOOL CSchemeManager::EditGame(LPCTSTR lpszName, LPCTSTR lpszNewName, LPCTSTR lpszTitle, LPCTSTR lpszClass)
{
	int nIndex = FindGame(lpszName);
	if (nIndex == -1)
		return FALSE;

	GAMEDATA& game = m_aGameData.ElementAt(nIndex);
	_tcsncpy(game.szName, lpszNewName, GAME_TEXT_LEN);
	_tcsncpy(game.szTitle, lpszTitle, GAME_TEXT_LEN);
	_tcsncpy(game.szClass, lpszClass, GAME_TEXT_LEN);

	if (_tcsicmp(m_selGame.szName, lpszName) == 0)
		m_selGame = game;

	return TRUE;
}

int CSchemeManager::FindGame(LPCTSTR lpszName) const
{
	for (int i = 0; i < m_aGameData.GetSize(); i++)
	{
		if (_tcsicmp(m_aGameData[i].szName, lpszName) == 0)
			return i;
	}
	return -1;
}

int CSchemeManager::GetGameCount() const
{
	return m_aGameData.GetSize();
}

BOOL CSchemeManager::GetGameData(int nIndex, LPGAMEDATA pData) const
{
	if (nIndex < 0 || nIndex >= m_aGameData.GetSize())
		return FALSE;

	if (pData)
		*pData = m_aGameData[nIndex];
	
	return TRUE;
}

void CSchemeManager::SetHotey(DWORD dwHotkey)
{
	m_dwHotkey = dwHotkey;
}

DWORD CSchemeManager::GetHotkey() const
{
	return m_dwHotkey;
}
