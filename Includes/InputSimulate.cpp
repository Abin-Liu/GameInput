//////////////////////////////////////////////////////////////////////////
// InputSimulate.cpp
// 
// A set of functions simply wrapped some of the win32 keyboard/mouse
// input API's the make such input simulation easier.
//
// Abin (abinn32@yahoo.com)
// 17/04/2006
//////////////////////////////////////////////////////////////////////////

#include "stdafx.h" // Include if needed
#include "InputSimulate.h"

void InputSleep(DWORD dwDelay)
{
	if (dwDelay)
		::Sleep(dwDelay);
}

BOOL IsKeyDown(WORD wKeyCode)
{
	return wKeyCode && (::GetAsyncKeyState(wKeyCode) & 0x8000) != 0;
}

BOOL IsMouseDown(int nButton)
{
	if (nButton == SIM_MOUSE_LEFT)
		return IsKeyDown(VK_LBUTTON);

	if (nButton == SIM_MOUSE_RIGHT)
		return IsKeyDown(VK_RBUTTON);

	if (nButton == SIM_MOUSE_MIDDLE)
		return IsKeyDown(VK_MBUTTON);

	return FALSE;
}

BOOL FindKeyRedundancy(WORD wVKCode, WORD wModifier)
{
	if (wVKCode == VK_SHIFT)
		return wModifier & MOD_SHIFT;

	if (wVKCode == VK_CONTROL)
		return wModifier & MOD_CONTROL;

	if (wVKCode == VK_MENU)
		return wModifier & MOD_ALT;

	return FALSE;
}

void SimulateKeyDown(WORD wVKCode, WORD wModifier, DWORD dwDelay)
{
	if ((wModifier & MOD_SHIFT) && !IsKeyDown(VK_SHIFT))
	{
		::keybd_event(VK_SHIFT, 0, KEYEVENTF_EXTENDEDKEY, ::GetMessageExtraInfo());
		InputSleep(dwDelay);
	}

	if ((wModifier & MOD_CONTROL) && !IsKeyDown(VK_CONTROL))
	{
		::keybd_event(VK_CONTROL, 0, KEYEVENTF_EXTENDEDKEY, ::GetMessageExtraInfo());
		InputSleep(dwDelay);
	}

	if ((wModifier & MOD_ALT) && !IsKeyDown(VK_MENU))
	{
		::keybd_event(VK_MENU, 0, KEYEVENTF_EXTENDEDKEY, ::GetMessageExtraInfo());
		InputSleep(dwDelay);
	}

	if (wVKCode && !FindKeyRedundancy(wVKCode, wModifier) && !IsKeyDown(wVKCode))
	{
		::keybd_event((BYTE)wVKCode, 0, KEYEVENTF_EXTENDEDKEY, ::GetMessageExtraInfo());
		InputSleep(dwDelay);
	}	
}

void SimulateKeyUp(WORD wVKCode, WORD wModifier, DWORD dwDelay)
{
	if (wVKCode && !FindKeyRedundancy(wVKCode, wModifier) && IsKeyDown(wVKCode))
	{
		::keybd_event((BYTE)wVKCode, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, ::GetMessageExtraInfo());
		InputSleep(dwDelay);
	}	

	if ((wModifier & MOD_ALT) && IsKeyDown(VK_MENU))
	{
		::keybd_event(VK_MENU, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, ::GetMessageExtraInfo());
		InputSleep(dwDelay);
	}

	if ((wModifier & MOD_CONTROL) && IsKeyDown(VK_CONTROL))
	{
		::keybd_event(VK_CONTROL, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, ::GetMessageExtraInfo());
		InputSleep(dwDelay);
	}

	if ((wModifier & MOD_SHIFT) && IsKeyDown(VK_SHIFT))
	{
		::keybd_event(VK_SHIFT, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, ::GetMessageExtraInfo());
		InputSleep(dwDelay);
	}
}

void SimulateKeyStroke(WORD wVKCode, WORD wModifier, DWORD dwDelay)
{
	if (wVKCode == 0 && wModifier == 0)
		return;
	
	SimulateKeyDown(wVKCode, wModifier, dwDelay);
	SimulateKeyUp(wVKCode, wModifier, dwDelay);
}

int CleanAllKeyStates(DWORD dwDelay)
{
	BYTE aStats[256] = { 0 };
	if (!::GetKeyboardState(aStats))
		return 0;

	int nCount = 0;
	for (WORD i = 0; i < 256; i++)
	{
		if (aStats[i] & 0x80)
		{
			::keybd_event((BYTE)i, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, ::GetMessageExtraInfo());
			nCount++;
			InputSleep(dwDelay);
		}
	}

	return nCount;
}

void SimulateMouseMove(int x, int y, DWORD dwDelay)
{
	::mouse_event(MOUSEEVENTF_MOVE, x, y, 0, ::GetMessageExtraInfo());
	InputSleep(dwDelay);
}

void SimulateMouseMove(POINT point, DWORD dwDelay)
{
	SimulateMouseMove(point.x, point.y, dwDelay);
}

void SimulateMouseJump(int x, int y, HWND hWnd, DWORD dwDelay)
{
	POINT point;
	point.x = x;
	point.y = y;
	SimulateMouseJump(point, hWnd, dwDelay);
}

void SimulateMouseJump(POINT point, HWND hWnd, DWORD dwDelay)
{
	if (hWnd && ::IsWindow(hWnd))
		::ClientToScreen(hWnd, &point);

	::SetCursorPos(point.x, point.y);
	InputSleep(dwDelay);
}

void SimulateMouseDown(DWORD dwButtons, WORD wModifier, DWORD dwDelay)
{
	SimulateKeyDown(0, wModifier, dwDelay);

	if ((dwButtons & SIM_MOUSE_LEFT) && !IsMouseDown(SIM_MOUSE_LEFT))
	{
		::mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, ::GetMessageExtraInfo());
		InputSleep(dwDelay);
	}

	if ((dwButtons & SIM_MOUSE_MIDDLE) && !IsMouseDown(SIM_MOUSE_MIDDLE))
	{
		::mouse_event(MOUSEEVENTF_MIDDLEDOWN, 0, 0, 0, ::GetMessageExtraInfo());
		InputSleep(dwDelay);
	}

	if ((dwButtons & SIM_MOUSE_RIGHT) && !IsMouseDown(SIM_MOUSE_RIGHT))
	{
		::mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, ::GetMessageExtraInfo());
		InputSleep(dwDelay);
	}
}

void SimulateMouseUp(DWORD dwButtons, WORD wModifier, DWORD dwDelay)
{
	if ((dwButtons & SIM_MOUSE_RIGHT) && IsMouseDown(SIM_MOUSE_RIGHT))
	{
		::mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, ::GetMessageExtraInfo());
		InputSleep(dwDelay);
	}

	if ((dwButtons & SIM_MOUSE_MIDDLE) && IsMouseDown(SIM_MOUSE_MIDDLE))
	{
		::mouse_event(MOUSEEVENTF_MIDDLEUP, 0, 0, 0, ::GetMessageExtraInfo());
		InputSleep(dwDelay);
	}

	if ((dwButtons & SIM_MOUSE_LEFT) && IsMouseDown(SIM_MOUSE_LEFT))
	{
		::mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, ::GetMessageExtraInfo());
		InputSleep(dwDelay);
	}

	SimulateKeyUp(0, wModifier, dwDelay);
}

void SimulateMouseClick(DWORD dwButtons, WORD wModifier, DWORD dwDelay)
{
	SimulateMouseDown(dwButtons, wModifier, dwDelay);
	SimulateMouseUp(dwButtons, wModifier, dwDelay);
}

void SimulateMouseDblClick(DWORD dwButtons, WORD wModifier, DWORD dwDelay)
{
	SimulateKeyDown(0, wModifier, dwDelay);
	SimulateMouseClick(dwButtons, 0, dwDelay);
	SimulateMouseClick(dwButtons, 0, dwDelay);
	SimulateKeyUp(0, wModifier, dwDelay);
}
