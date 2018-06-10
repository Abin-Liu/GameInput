// GameData.h: interface for the CGameData class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __GAMEDATA_H__
#define __GAMEDATA_H__

#include "SchemeData.h"

class CGameData  
{
public:
	
	CGameData(LPCTSTR lpszName = NULL, LPCTSTR lpszTitle = NULL, LPCTSTR lpszClass = NULL);
	virtual ~CGameData();
	
	BOOL Load(CIni &ini, LPCTSTR lpszSect);
	void Save(CIni& ini, LPCTSTR lpszSect) const;
	void Clear();

	CString GetName() const;
	CString GetTitle() const;
	CString GetClass() const;
	void Edit(LPCTSTR lpszName, LPCTSTR lpszTitle, LPCTSTR lpszClass);

	void SetActive(CSchemeData* pData);
	CSchemeData* GetActive();
	CSchemeData* AddScheme(LPCTSTR lpszName);
	void DeleteScheme(CSchemeData *pData);
	int GetSchemeCount() const;
	CSchemeData* GetScheme(int nIndex);
	int FindSchemeByName(LPCTSTR lpszName) const;

	BOOL IsWindow() const;
	BOOL IsForeground() const;
	void SetForeground() const;	
	BOOL UpdateGameWnd();

protected:
	
	CString m_sName;
	CString m_sTitle;
	CString m_sClass;
	CArrayEx<CSchemeData*, CSchemeData*> m_schemes;
	CSchemeData* m_pActive;
	HWND m_hGameWnd;
};


#endif // __GAMEDATA_H__
