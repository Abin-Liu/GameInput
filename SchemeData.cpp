#include "stdafx.h"
#include "GameInput.h"
#include "SchemeData.h"
#include "Includes\InputSimulate.h"

#define INPUT_DELAY	25

CSchemeData::CSchemeData()
{
	m_dwBlockUntil = 0;
	m_bRunOnce = FALSE;
}

CSchemeData::~CSchemeData()
{
	Clear();
}

void CSchemeData::Clear()
{
	m_actions.RemoveAll();
}

CString CSchemeData::GetName() const
{
	return m_sName;
}

BOOL CSchemeData::Load(CIni &ini, LPCTSTR lpszSect)
{	
	Clear();
	m_sName = ini.GetString(lpszSect, _T("Name"));
	if (m_sName.IsEmpty())
		return FALSE;

	m_bRunOnce = ini.GetBool(lpszSect, _T("RunOnce"), FALSE);

	int nCount = ini.GetInt(lpszSect, _T("Actions"), 0);
	for (int i = 0; i < nCount; i++)
	{
		CString sKey;
		sKey.Format(_T("Action%d"), i + 1);
		if (!LoadAction(ini.GetString(lpszSect, sKey)))
			break;
	}

	return TRUE;
}

BOOL CSchemeData::LoadAction(CString sLine)
{
	if (sLine.IsEmpty())
		return FALSE;

	ACTIONDATA action = { 0 };

	// Format: type,keyCode,mouseBtn,modifiers,interval,postDelay,desc
	int nStart = 0;
	if (!Extract(sLine, nStart, action.nType))
		return FALSE;

	if (!Extract(sLine, nStart, action.nKeyCode))
		return FALSE;

	if (!Extract(sLine, nStart, action.nButton))
		return FALSE;

	if (!Extract(sLine, nStart, action.nMods))
		return FALSE;

	if (!Extract(sLine, nStart, action.nInterval))
		return FALSE;

	if (!Extract(sLine, nStart, action.nPostDelay))
		return FALSE;

	CString sDesc = sLine.Mid(nStart);
	_tcsncpy(action.szDesc, sDesc, 32);

	m_actions.Add(action);
	return TRUE;
}

BOOL CSchemeData::Extract(const CString &sLine, int& nStart, int& nValue)
{
	int nPos = sLine.Find(_T(','), nStart);
	if (nPos == -1)
		return FALSE;

	CString sSeg = sLine.Mid(nStart, nPos - nStart);
	LPTSTR p = NULL;
	nValue = _tcstol(sSeg, &p, 10);
	if (*p)
		return FALSE;

	nStart = nPos + 1;
	return TRUE;
}

void CSchemeData::Save(CIni &ini, LPCTSTR lpszSect) const
{
	ini.WriteString(lpszSect, _T("Name"), m_sName);
	ini.WriteBool(lpszSect, _T("RunOnce"), m_bRunOnce);

	int nCount = m_actions.GetSize();
	ini.WriteInt(lpszSect, _T("Actions"), nCount);

	for (int i = 0; i < nCount; i++)
	{
		CString sKey;
		sKey.Format(_T("Action%d"), i + 1);

		const ACTIONDATA& action = m_actions[i];
		// Format: type,keyCode,mouseBtn,modifiers,interval,postDelay,desc
		CString sLine;
		sLine.Format(_T("%d,%d,%d,%d,%d,%d,%s"), action.nType, action.nKeyCode, action.nButton, action.nMods, action.nInterval, action.nPostDelay, action.szDesc);
		ini.WriteString(lpszSect, sKey, sLine);		
	}
}

int CSchemeData::GetActionCount() const
{
	return m_actions.GetSize();
}

ACTIONDATA& CSchemeData::GetAction(int nIndex)
{
	return m_actions.ElementAt(nIndex);
}

BOOL CSchemeData::SetAction(int nIndex, const ACTIONDATA &action)
{
	if (nIndex < 0 || nIndex >= m_actions.GetSize())
		return FALSE;

	m_actions[nIndex] = action;
	return TRUE;
}

int CSchemeData::AddAction(const ACTIONDATA &action)
{
	return m_actions.Add(action);
}

BOOL CSchemeData::DeleteAction(int nIndex)
{
	if (nIndex < 0 || nIndex >= m_actions.GetSize())
		return FALSE;

	m_actions.RemoveAt(nIndex);
	return TRUE;
}

BOOL CSchemeData::SwapActions(int nIndex1, int nIndex2)
{
	if (nIndex1 == nIndex2 || nIndex1 < 0 || nIndex1 >= m_actions.GetSize() || nIndex2 < 0 || nIndex2 >= m_actions.GetSize())
		return FALSE;

	ACTIONDATA action = m_actions[nIndex1];
	m_actions[nIndex1] = m_actions[nIndex2];
	m_actions[nIndex2] = action;
	return TRUE;
}

void CSchemeData::SetName(LPCTSTR lpszName)
{
	m_sName = lpszName;
}

BOOL CSchemeData::IsRunOnce() const
{
	return m_bRunOnce;
}

void CSchemeData::SetRunOnce(BOOL bRunOnce)
{
	m_bRunOnce = bRunOnce;
}

void CSchemeData::ReleaseAction(ACTIONDATA &action)
{	
	if (action.nType == ACTION_MOUSE_DOWN)
		SimulateMouseUp(action.nButton, (WORD)action.nMods);		
	else if (action.nType == ACTION_KEY_DOWN)
		SimulateKeyUp((WORD)action.nKeyCode, (WORD)action.nMods);
	else
		NULL;

	action.dwLastProc = 0;
}

BOOL CSchemeData::Start()
{
	Stop();	
	return GetActionCount();
}

void CSchemeData::Stop()
{
	m_dwBlockUntil = 0;
	for (int i = 0; i < GetActionCount(); i++)
		ReleaseAction(GetAction(i));	
}

BOOL CSchemeData::OnTick()
{
	if (::GetTickCount() < m_dwBlockUntil)
		return TRUE; // Wait until block time ends

	if (m_bRunOnce && AllProced())
		return FALSE; // All actions are processed, stop the "run-once" scheme

	for (int i = 0; i < GetActionCount(); i++)
	{
		if (ProcessAction(GetAction(i)))
			break;
	}	
	
	return TRUE;
}

BOOL CSchemeData::AllProced() const
{
	for (int i = 0; i < m_actions.GetSize(); i++)
	{
		if (m_actions[i].dwLastProc == 0)
			return FALSE;
	}
	return TRUE;
}

BOOL CSchemeData::ProcessAction(ACTIONDATA& action)
{
	if (m_bRunOnce && action.dwLastProc)
		return FALSE;
	
	DWORD dwElapsed = ::GetTickCount() - action.dwLastProc;
	if (dwElapsed < (DWORD)action.nInterval)
		return FALSE;

	switch (action.nType)
	{
	case ACTION_KEY_STROKE:
		SimulateKeyStroke((WORD)action.nKeyCode, (WORD)action.nMods, INPUT_DELAY);
		break;

	case ACTION_KEY_DOWN:
		SimulateKeyDown((WORD)action.nKeyCode, (WORD)action.nMods, INPUT_DELAY);
		break;

	case ACTION_MOUSE_CLICK:
		SimulateMouseClick(action.nButton, (WORD)action.nMods, INPUT_DELAY);
		break;

	case ACTION_MOUSE_DOWN:
		SimulateMouseDown(action.nButton, (WORD)action.nMods, INPUT_DELAY);
		break;

	default:
		break;
	}

	DWORD dwNow = ::GetTickCount();

	// Check post waiting
	if (action.nPostDelay > 0)
		m_dwBlockUntil = dwNow + action.nPostDelay;

	action.dwLastProc = dwNow;
	return TRUE;
}