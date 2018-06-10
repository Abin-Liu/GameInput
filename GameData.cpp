#include "stdafx.h"
#include "GameInput.h"
#include "GameData.h"

CGameData::CGameData(LPCTSTR lpszName, LPCTSTR lpszTitle, LPCTSTR lpszClass)
{
	m_pActive = NULL;
	m_hGameWnd = NULL;
	Edit(lpszName, lpszTitle, lpszClass);
}

CGameData::~CGameData()
{
	Clear();
}

CString CGameData::GetName() const
{
	return m_sName;
}

CSchemeData* CGameData::GetActive()
{
	return m_pActive;
}

int CGameData::FindSchemeByName(LPCTSTR lpszName) const
{
	for (int i = 0; i < m_schemes.GetSize(); i++)
	{
		if (m_schemes[i]->GetName().CompareNoCase(lpszName) == 0)
			return i;
	}

	return -1;
}

void CGameData::Edit(LPCTSTR lpszName, LPCTSTR lpszTitle, LPCTSTR lpszClass)
{
	m_sName = lpszName;
	m_sTitle = lpszTitle;
	m_sClass = lpszClass;
}

CSchemeData* CGameData::AddScheme(LPCTSTR lpszName)
{
	int nSurfix = 0;
	CString sName(lpszName);

	while (FindSchemeByName(sName) != -1)
	{
		nSurfix++;
		sName.Format(_T("%s (%d)"), lpszName, nSurfix);
	}

	CSchemeData* p = new CSchemeData;
	p->SetName(lpszName);
	m_schemes.Add(p);
	SetActive(p);
	return p;	
}

void CGameData::DeleteScheme(CSchemeData *pData)
{
	if (pData == NULL)
		return;

	int nIndex = m_schemes.Find(pData);
	if (nIndex == -1)
		return;

	if (m_pActive == pData)
		m_pActive = NULL;

	m_schemes.RemoveAt(nIndex);
	delete pData;
}

void CGameData::SetActive(CSchemeData* pData)
{
	if (pData == m_pActive)
		return;

	if (pData == NULL)
	{
		m_pActive = pData;
	}
	else
	{
		int nIndex = m_schemes.Find(pData);
		if (nIndex != -1)
			m_pActive = pData;
	}
}

int CGameData::GetSchemeCount() const
{
	return m_schemes.GetSize();
}

CSchemeData* CGameData::GetScheme(int nIndex)
{
	if (nIndex >= 0 && nIndex < m_schemes.GetSize())
		return m_schemes[nIndex];
	return NULL;
}


////////////////////////////////////////////////////

BOOL CGameData::Load(CIni &ini, LPCTSTR lpszSect)
{
	Clear();

	m_sName = ini.GetString(lpszSect, _T("Name"));
	if (m_sName.IsEmpty())
		return FALSE;

	m_sTitle = ini.GetString(lpszSect, _T("Title"));
	m_sClass = ini.GetString(lpszSect, _T("Class"));
	if (m_sTitle.IsEmpty() && m_sClass.IsEmpty())
		return FALSE;

	int nActive = ini.GetInt(lpszSect, _T("active"), -1);
	int nCount = ini.GetInt(lpszSect, _T("Schemes"), 0);

	for (int i = 0; i <nCount; i++)
	{
		CString sSect;
		sSect.Format(_T("%s-Scheme%d"), lpszSect, i + 1);
		CSchemeData* p = new CSchemeData;
		if (p->Load(ini, sSect))
		{
			m_schemes.Add(p);
		}
		else
		{
			delete p;
			break;
		}		

		if (nActive == i)
			m_pActive = p;
	}

	return TRUE;
}

void CGameData::Clear()
{
	m_pActive = NULL;
	m_hGameWnd = NULL;

	for (int i = 0; i < m_schemes.GetSize(); i++)
	{
		m_schemes[i]->Clear();
		delete m_schemes[i];
	}
	m_schemes.RemoveAll();	
}

void CGameData::Save(CIni &ini, LPCTSTR lpszSect) const
{
	ini.WriteString(lpszSect, _T("Name"), m_sName);
	ini.WriteString(lpszSect, _T("Title"), m_sTitle);
	ini.WriteString(lpszSect, _T("Class"), m_sClass);

	int nCount = m_schemes.GetSize();
	ini.WriteInt(lpszSect, _T("Schemes"), nCount);

	for (int i = 0; i < nCount; i++)
	{
		CSchemeData* pData = m_schemes[i];
		if (m_pActive == pData)
			ini.WriteInt(lpszSect, _T("Active"), i);

		CString sSect;
		sSect.Format(_T("%s-Scheme%d"), lpszSect, i + 1);
		pData->Save(ini, sSect);
	}
}

CString CGameData::GetTitle() const
{
	return m_sTitle;
}

CString CGameData::GetClass() const
{
	return m_sClass;
}

BOOL CGameData::UpdateGameWnd()
{
	m_hGameWnd = NULL;

	LPCTSTR lpszTitle = NULL;
	LPCTSTR lpszClass = NULL;

	if (!m_sTitle.IsEmpty())
		lpszTitle = m_sTitle;

	if (!m_sClass.IsEmpty())
		lpszClass = m_sClass;

	if (lpszTitle || lpszClass)
		m_hGameWnd = ::FindWindow(lpszClass, lpszTitle);	

	return m_hGameWnd != NULL;
}

BOOL CGameData::IsForeground() const
{
	return m_hGameWnd && ::GetForegroundWindow() == m_hGameWnd;
}

void CGameData::SetForeground() const
{
	if (m_hGameWnd == NULL)
		return;
	
	if (::IsIconic(m_hGameWnd))
		::ShowWindow(m_hGameWnd, SW_RESTORE);

	::SetForegroundWindow(m_hGameWnd);
}

BOOL CGameData::IsWindow() const
{
	return ::IsWindow(m_hGameWnd);
}