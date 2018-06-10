// Scheme.h: interface for the CScheme class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCHEME_H__6F3FB370_0871_4218_8FF3_45C76D185293__INCLUDED_)
#define AFX_SCHEME_H__6F3FB370_0871_4218_8FF3_45C76D185293__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>

static const LPCSTR SCHEME_ACTION_TYPES[] = { "键盘按键", "鼠标左键", "鼠标右键", "鼠标中键", "鼠标滚轮向上", "鼠标滚轮向下" };
static const int NUM_SCHEME_ACTIONS = sizeof(SCHEME_ACTION_TYPES) / sizeof(LPCSTR);

#define SCHEME_NAME_LEN		64
#define SCHEME_MAX			128
#define GAME_TEXT_LEN		127

typedef struct _tag_SchemeData
{
	char szDesc[SCHEME_NAME_LEN + 1];
	int nAction;
	DWORD dwCode;
	DWORD dwInterval;
	DWORD dwPreWait;
	DWORD dwPostWait;
	DWORD dwLastProc;
} SCHEMEDATA, *LPSCHEMEDATA;

class CScheme
{
public:
	friend class CSchemeManager;

	CScheme();
	CScheme(LPCSTR lpszName);
	CScheme(const CScheme& rhs);
	~CScheme();

	LPCSTR GetName() const;
	int GetCount() const;
	SCHEMEDATA& GetData(int nIndex);
	int AddData(const SCHEMEDATA& data);
	BOOL DeleteData(int nIndex);
	BOOL MoveData(int nIndex, BOOL bMoveUp);
	const CScheme& operator=(const CScheme& rhs);

	static DWORD ExecuteAction(SCHEMEDATA& data);
	static DWORD PreExecuteAction(const SCHEMEDATA& data);

private:

	BOOL Load(int nIndex);
	BOOL Save(int nIndex);
	
	char m_szName[SCHEME_NAME_LEN + 1];
	CArray<SCHEMEDATA, const SCHEMEDATA&> m_aData;
};

typedef CArray<CScheme, const CScheme&> CSchemeArray;

typedef struct _TagGameData
{
	TCHAR szName[GAME_TEXT_LEN + 1];
	TCHAR szTitle[GAME_TEXT_LEN + 1];
	TCHAR szClass[GAME_TEXT_LEN + 1];
} GAMEDATA, *LPGAMEDATA;

typedef CArray<GAMEDATA, const GAMEDATA&> CGameDataArray;

class CSchemeManager
{
public:		
	DWORD GetHotkey() const;
	void SetHotey(DWORD dwHotkey);
	BOOL GetGameData(int nIndex, LPGAMEDATA pData) const;
	int GetGameCount() const;
	int FindGame(LPCTSTR lpszName) const;
	BOOL EditGame(LPCTSTR lpszName, LPCTSTR lpszNewName, LPCTSTR lpszTitle, LPCTSTR lpszClass);
	void ResetGames();
	BOOL DeleteGame(LPCTSTR lpszName);
	const GAMEDATA& GetSelectedGame() const;
	void SelectGame(LPCTSTR lpszName);
	BOOL AddGame(LPCTSTR lpszName, LPCTSTR lpszTitle, LPCTSTR lpszClass);
	CGameDataArray& GetGames();
	CSchemeArray& GetSchemes();

	CSchemeManager();
	~CSchemeManager();

	BOOL Load();
	void Save();
	int GetActive() const;
	CScheme* GetActiveData();
	BOOL SetActive(int nIndex);

private:

	CSchemeArray m_aSchemes;
	CGameDataArray m_aGameData;
	GAMEDATA m_selGame;
	int m_nActive;
	DWORD m_dwHotkey;
};

#endif // !defined(AFX_SCHEME_H__6F3FB370_0871_4218_8FF3_45C76D185293__INCLUDED_)
