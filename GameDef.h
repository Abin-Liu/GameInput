#ifndef __GAMEDEF_H__
#define __GAMEDEF_H__

struct GAMEDEF
{
	TCHAR szName[256];
	TCHAR szClass[256];
};

static const GAMEDEF GAME_LIST[] = {
	{ _T("前台窗口"), _T("") },
	{ _T("魔兽世界"), _T("GxWindowClass") },
	{ _T("Diablo III"), _T("D3 Main Window Class") },
};

static const int GAME_COUNT = sizeof(GAME_LIST) / sizeof(GAMEDEF);
#define VALID_GAME_INDEX(x) (x >= 0 && x < GAME_COUNT)

#endif // __GAMEDEF_H__