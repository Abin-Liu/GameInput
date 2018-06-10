//////////////////////////////////////////////////////////////////////////
// InputSimulate.h
// 
// A set of functions simply wrapped some of the win32 keyboard/mouse
// input API's the make such input simulation easier.
//
// Abin (abinn32@yahoo.com)
// 17/04/2006
//////////////////////////////////////////////////////////////////////////

#ifndef __INPUTSIMULATE_H__
#define __INPUTSIMULATE_H__

#include <windows.h>

#define SIM_MOUSE_LEFT			0x08 // The left mouse button is pressed
#define SIM_MOUSE_RIGHT			0x10 // The right mouse button is pressed
#define SIM_MOUSE_MIDDLE		0x20 // The middle mouse button is pressed

//////////////////////////////////////////////////////////////////////////
// Keybord Inputs
//////////////////////////////////////////////////////////////////////////
void SimulateKeyDown(WORD wVKCode, WORD wModifier = 0, DWORD dwDelay = 0);
void SimulateKeyUp(WORD wVKCode, WORD wModifier = 0, DWORD dwDelay = 0);
void SimulateKeyStroke(WORD wVKCode, WORD wModifier = 0, DWORD dwDelay = 0);
int CleanAllKeyStates(DWORD dwDelay = 0);
BOOL FindKeyRedundancy(WORD wVKCode, WORD wModifier);
BOOL IsKeyDown(WORD wKeyCode);

//////////////////////////////////////////////////////////////////////////
// Mouse & Keybord Combination Inputs
//////////////////////////////////////////////////////////////////////////
void SimulateMouseMove(int x, int y, DWORD dwDelay = 0);
void SimulateMouseMove(POINT point, DWORD dwDelay = 0);
void SimulateMouseJump(int x, int y, HWND hWnd = NULL, DWORD dwDelay = 0);
void SimulateMouseJump(POINT point, HWND hWnd = NULL, DWORD dwDelay = 0);
void SimulateMouseDown(DWORD dwButtons = SIM_MOUSE_LEFT, WORD wModifier = 0, DWORD dwDelay = 0);
void SimulateMouseUp(DWORD dwButtons = SIM_MOUSE_LEFT, WORD wModifier = 0, DWORD dwDelay = 0);
void SimulateMouseClick(DWORD dwButtons = SIM_MOUSE_LEFT, WORD wModifier = 0, DWORD dwDelay = 0);
void SimulateMouseDblClick(DWORD dwButtons = SIM_MOUSE_LEFT, WORD wModifier = 0, DWORD dwDelay = 0);
BOOL IsMouseDown(int nButton = SIM_MOUSE_LEFT);

#endif // __INPUTSIMULATE_H__