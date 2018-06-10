#ifndef __SCHEMEDATA_H__
#define __SCHEMEDATA_H__

#include "Includes\ArrayEx.h"
#include "Includes\Ini.h"

enum { ACTION_KEY_STROKE = 0, ACTION_KEY_DOWN, ACTION_MOUSE_CLICK, ACTION_MOUSE_DOWN };

struct ACTIONDATA
{
	int nType; // 4 action types, see enums above
	int nKeyCode; // virtual key code
	int nButton; // mouse button SIM_MOUSE_LEFT, SIM_MOUSE_RIGHT, SIM_MOUSE_MIDDLE
	int nMods; // modifier keys, combination of MOD_ALT, MOD_CONTROL, MOD_SHIFT
	int nInterval; // interval for repetitive actions, in ms
	int nPostDelay;	// delay triggered y this action, in ms
	TCHAR szDesc[33]; // action desc
	DWORD dwLastProc; // internal usage
};

class CSchemeData
{
public:

	CSchemeData();
	virtual ~CSchemeData();

	BOOL Load(CIni &ini, LPCTSTR lpszSect);
	void Save(CIni &ini, LPCTSTR lpszSect) const;
	void Clear();

	BOOL Start();
	void Stop();
	BOOL OnTick();
	
	void SetRunOnce(BOOL bRunOnce);
	BOOL IsRunOnce() const;
	void SetName(LPCTSTR lpszName);
	CString GetName() const;

	int AddAction(const ACTIONDATA& action);
	BOOL DeleteAction(int nIndex);
	BOOL SwapActions(int nIndex1, int nIndex2);
	BOOL SetAction(int nIndex, const ACTIONDATA& action);
	int GetActionCount() const;
	ACTIONDATA& GetAction(int nIndex);

protected:

	BOOL AllProced() const;
	void ReleaseAction(ACTIONDATA& action);
	BOOL ProcessAction(ACTIONDATA& action);
	BOOL LoadAction(CString sLine);
	static BOOL Extract(const CString& sLine, int& nStart, int& nValue);

	CString m_sName;
	BOOL m_bRunOnce;
	DWORD m_dwBlockUntil;
	CArrayEx<ACTIONDATA, const ACTIONDATA&> m_actions;
	
};

#endif // __SCHEMEDATA_H__