#ifndef __GAMEMANAGER_H__
#define __GAMEMANAGER_H__

#include "GameData.h"

class CGameManager
{
public:	

	CGameManager();
	virtual ~CGameManager();

	BOOL Start();
	void Stop();
	BOOL OnTick();
	void SetMainWnd(HWND hWnd);

	void Load();
	void Save() const;
	void Clear();
	void Reset();

	void SetActive(CGameData* pData);
	CGameData* GetActive();
	CSchemeData* GetActiveScheme();
	CGameData* AddGame(LPCTSTR lpszName, LPCTSTR lpszTitle, LPCTSTR lpszClass);
	void DeleteGame(CGameData *pData);
	
	int GetGameCount() const;
	CGameData* GetGame(int nIndex);

	void SetHotkey(DWORD dwHotkey);
	DWORD GetHotkey() const;
	BOOL RegisterHotkey();
	void UnregisterHotkey();
	void SetAutoForeground(BOOL bForeground);
	BOOL GetAutoForeground() const;

private:
	
	HWND m_hMainWnd;
	DWORD m_dwHotkey;
	CArrayEx<CGameData*, CGameData*> m_games;
	CGameData* m_pActive;
	BOOL m_bForeground;
	int m_nDelayTick;
};


#endif // __GAMEMANAGER_H__