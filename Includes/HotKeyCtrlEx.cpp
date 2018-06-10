//////////////////////////////////////////////////////////////////////////////////////
// HotKeyCtrlEx.h
//
// CHotKeyCtrlEx, an improvement to the MFC CHotKeyCtrl control. Allows:
// 
// 1, Configurable "eraser".
// 2, Recognizes VK_SPACE, VKBACK as valid hotkeys.
// 3, Accepts VK_CONTROL, VK_SHIFT, VK_MENU as valid hotkeys rather than modifiers only.
// 4, You can now retrieve string representation of hotkey combinations. 
//
// Written by Abin (abinn32@yahoo.com)
// Apr 19, 2006
//////////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HotKeyCtrlEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define HK_DEFAULT_ERASER_CODE	VK_BACK;
#define HK_DEFAULT_ERASER_MOD	0
#define HK_DEFAULT_KEY_NAME		_T("None");

DWORD CHotKeyCtrlEx::GetKeyName(BYTE iVKCode, LPTSTR lpszBuffer, DWORD dwMaxChars)
{
	if (lpszBuffer == NULL)
		return 0;

	lpszBuffer[0] = _T('\0');
	if (dwMaxChars == 0)
		return 0;

	switch (iVKCode)
	{
	case 0x08:

		_tcsncpy(lpszBuffer, _T("Backspace"), dwMaxChars);
		break;
		
	case 0x09:
	
		_tcsncpy(lpszBuffer, _T("Tab"), dwMaxChars);
		break;

	case 0x0c:
	
		_tcsncpy(lpszBuffer, _T("Num 5"), dwMaxChars);
		break;
		
	case 0x0d:
	
		_tcsncpy(lpszBuffer, _T("Return"), dwMaxChars);
		break;

	case 0x10:
	
		_tcsncpy(lpszBuffer, _T("Shift"), dwMaxChars);
		break;

	case 0x11:
	
		_tcsncpy(lpszBuffer, _T("Ctrl"), dwMaxChars);
		break;

	case 0x12:
	
		_tcsncpy(lpszBuffer, _T("Alt"), dwMaxChars);
		break;

	case 0x13:
	
		_tcsncpy(lpszBuffer, _T("Pause"), dwMaxChars);
		break;

	case 0x14:
	
		_tcsncpy(lpszBuffer, _T("Caps Lock"), dwMaxChars);
		break;

	case 0x1b:
	
		_tcsncpy(lpszBuffer, _T("Esc"), dwMaxChars);
		break;

	case 0x20:
	
		_tcsncpy(lpszBuffer, _T("Space"), dwMaxChars);
		break;

	case 0x21:
	
		_tcsncpy(lpszBuffer, _T("Page Up"), dwMaxChars);
		break;
		
	case 0x22:
	
		_tcsncpy(lpszBuffer, _T("Page Down"), dwMaxChars);
		break;

	case 0x23:
	
		_tcsncpy(lpszBuffer, _T("End"), dwMaxChars);
		break;
	case 0x24:
	
		_tcsncpy(lpszBuffer, _T("Home"), dwMaxChars);
		break;

	case 0x25:
	
		_tcsncpy(lpszBuffer, _T("Left"), dwMaxChars);
		break;

	case 0x26:
	
		_tcsncpy(lpszBuffer, _T("Up"), dwMaxChars);
		break;

	case 0x27:
	
		_tcsncpy(lpszBuffer, _T("Right"), dwMaxChars);
		break;

	case 0x28:
	
		_tcsncpy(lpszBuffer, _T("Down"), dwMaxChars);
		break;

	case 0x2d:
	
		_tcsncpy(lpszBuffer, _T("Insert"), dwMaxChars);
		break;
		
	case 0x2e:
	
		_tcsncpy(lpszBuffer, _T("Delete"), dwMaxChars);
		break;
		
	case 0x30:
	case 0x31:
	case 0x32:
	case 0x33:
	case 0x34:
	case 0x35:
	case 0x36:
	case 0x37:
	case 0x38:
	case 0x39:
	
		_stprintf(lpszBuffer, _T("%d"), iVKCode - 0x30);
		break;

	case 0x41: // a
	case 0x42: // b
	case 0x43: // c
	case 0x44: // d
	case 0x45: // e
	case 0x46: // f
	case 0x47: // g
	case 0x48: // h
	case 0x49: // i
	case 0x4a: // j
	case 0x4b: // k
	case 0x4c: // l
	case 0x4d: // m
	case 0x4e: // n
	case 0x4f: // o
	case 0x50: // p
	case 0x51: // q
	case 0x52: // r
	case 0x53: // s
	case 0x54: // t
	case 0x55: // u
	case 0x56: // v
	case 0x57: // w
	case 0x58: // x
	case 0x59: // y
	case 0x5a: // z
	
		_stprintf(lpszBuffer, _T("%C"), iVKCode - 0x41 + _T('A'));
		break;

	case 0x60:
	case 0x61:
	case 0x62:
	case 0x63:
	case 0x64:
	case 0x65:
	case 0x66:
	case 0x67:
	case 0x68:
	case 0x69:
	
		_stprintf(lpszBuffer, _T("Num %d"), iVKCode - 0x60);
		break;

	case 0x6a:
	
		_tcsncpy(lpszBuffer, _T("Num *"), dwMaxChars);
		break;

	case 0x6b:
	
		_tcsncpy(lpszBuffer, _T("Num +"), dwMaxChars);
		break;
	case 0x6d:
	
		_tcsncpy(lpszBuffer, _T("Num -"), dwMaxChars);
		break;

	case 0x6e:
	
		_tcsncpy(lpszBuffer, _T("Num ."), dwMaxChars);
		break;

	case 0x6f:
	
		_tcsncpy(lpszBuffer, _T("Num /"), dwMaxChars);
		break;

	case VK_F1:
	case VK_F2:
	case VK_F3:
	case VK_F4:
	case VK_F5:
	case VK_F6:
	case VK_F7:
	case VK_F8:
	case VK_F9:
	case VK_F10:
	case VK_F11:
	case VK_F12:
	
		_stprintf(lpszBuffer, _T("F%d"), iVKCode - VK_F1 + 1);
		break;

	case 0x90:
	
		_tcsncpy(lpszBuffer, _T("Num Lock"), dwMaxChars);
		break;
	case 0x91:
	
		_tcsncpy(lpszBuffer, _T("Scroll Lock"), dwMaxChars);
		break;

	case 0xba:
	
		_tcsncpy(lpszBuffer, _T(";"), dwMaxChars);
		break;

	case 0xbb:
	
		_tcsncpy(lpszBuffer, _T("="), dwMaxChars);
		break;

	case 0xbc:
	
		_tcsncpy(lpszBuffer, _T(","), dwMaxChars);
		break;

	case 0xbd:
	
		_tcsncpy(lpszBuffer, _T("-"), dwMaxChars);
		break;
	case 0xbe:
	
		_tcsncpy(lpszBuffer, _T("."), dwMaxChars);
		break;

	case 0xbf:
	
		_tcsncpy(lpszBuffer, _T("/"), dwMaxChars);
		break;
	case 0xc0:
	
		_tcsncpy(lpszBuffer, _T("`"), dwMaxChars);
		break;

	case 0xdb:
	
		_tcsncpy(lpszBuffer, _T("["), dwMaxChars);
		break;
	case 0xdc:
	
		_tcsncpy(lpszBuffer, _T("\\"), dwMaxChars);
		break;

	case 0xdd:
	
		_tcsncpy(lpszBuffer, _T("]"), dwMaxChars);
		break;
	case 0xde:
	
		_tcsncpy(lpszBuffer, _T("'"), dwMaxChars);
		break;

	default:
		return 0;
		break;	
	}

	return _tcslen(lpszBuffer);
}

/////////////////////////////////////////////////////////////////////////////
// CHotKeyCtrlEx

CHotKeyCtrlEx::CHotKeyCtrlEx()
{
	m_wVKCode = 0;
	m_wModifiers = 0;
	m_wEraserVKCode = HK_DEFAULT_ERASER_CODE;
	m_wEraserModifiers = HK_DEFAULT_ERASER_MOD;
	m_wInvalidComb = 0;
	m_wRuleModifiers = 0;
}

CHotKeyCtrlEx::~CHotKeyCtrlEx()
{
}

BEGIN_MESSAGE_MAP(CHotKeyCtrlEx, CEdit)
	//{{AFX_MSG_MAP(CHotKeyCtrlEx)
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHotKeyCtrlEx message handlers
LRESULT CHotKeyCtrlEx::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	switch (message)
	{
	// These messages must be disabled to make the control more alike the CHotKeyCtrl
	case WM_COPY: // copy
	case WM_CUT: // cut
	case WM_PASTE: // Paste
	case WM_CONTEXTMENU: // Pop up menu
	case WM_CLEAR: // Clear edit texts
	case EM_UNDO: // undo
	case EM_REDO: // redo
	case WM_MOUSEMOVE: // Mouse drags
	case WM_CHAR: // Character inputs
		return 1;
		break;

	case EM_SETSEL: // Text selection
		if ((long)wParam < (long)lParam)
			return 1;
		break;

	default:
		break;
	}

	return CEdit::WindowProc(message, wParam, lParam);
}

void CHotKeyCtrlEx::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	// Prevent user from changing the caret position
	CEdit::OnLButtonDown(nFlags, point);
	SetSel(INT_MAX, INT_MAX);
}

void CHotKeyCtrlEx::SetHotKey(WORD wVirtualKeyCode, WORD wModifiers)
{
	m_wVKCode = wVirtualKeyCode;
	m_wModifiers = wModifiers;
	NormalizeModifiers(m_wVKCode, m_wModifiers);
	if (::IsWindow(m_hWnd))
		UpdateHotKeyText();
}

void CHotKeyCtrlEx::SetHotKey(DWORD dwHotKey)
{
	m_wVKCode = LOWORD(dwHotKey);
	m_wModifiers = HIWORD(dwHotKey);
	NormalizeModifiers(m_wVKCode, m_wModifiers);
	if (::IsWindow(m_hWnd))
		UpdateHotKeyText();
}

void CHotKeyCtrlEx::GetHotKey(WORD &wVirtualKeyCode, WORD &wModifiers) const
{
	wVirtualKeyCode = m_wVKCode;
	wModifiers = m_wModifiers;
}

DWORD CHotKeyCtrlEx::GetHotKey() const
{
	return MAKELONG(m_wVKCode, m_wModifiers);
}

void CHotKeyCtrlEx::SetEraser(DWORD dwEraser)
{
	m_wEraserVKCode = LOWORD(dwEraser);
	m_wEraserModifiers = HIWORD(dwEraser);
	NormalizeModifiers(m_wEraserVKCode, m_wEraserModifiers);
}

void CHotKeyCtrlEx::SetEraser(WORD wVirtualKeyCode, WORD wModifiers)
{
	m_wEraserVKCode = wVirtualKeyCode;
	m_wEraserModifiers = wModifiers;
	NormalizeModifiers(m_wEraserVKCode, m_wEraserModifiers);
}

DWORD CHotKeyCtrlEx::GetEraser() const
{
	return MAKELONG(m_wEraserVKCode, m_wEraserModifiers);
}

void CHotKeyCtrlEx::GetEraser(WORD &wVirtualKeyCode, WORD &wModifiers) const
{
	wVirtualKeyCode = m_wEraserVKCode;
	wModifiers = m_wEraserModifiers;
}

CString CHotKeyCtrlEx::GetHotKeyString(WORD wVirtualKeyCode, WORD wModifiers)
{
	CString str;
	if (wVirtualKeyCode == VK_CONTROL || (wModifiers & HOTKEYF_CONTROL))
		str += _T("Ctrl");

	if (wVirtualKeyCode == VK_SHIFT || (wModifiers & HOTKEYF_SHIFT))
	{
		if (str.GetLength())
			str += _T(" + ");
		str += _T("Shift");
	}

	if (wVirtualKeyCode == VK_MENU || (wModifiers & HOTKEYF_ALT))
	{
		if (str.GetLength())
			str += _T(" + ");
		str += _T("Alt");
	}	
	
	if (wVirtualKeyCode != VK_CONTROL && wVirtualKeyCode != VK_SHIFT && wVirtualKeyCode != VK_MENU)
	{
		TCHAR szKey[64] = _T("");
		if (GetKeyName((BYTE)wVirtualKeyCode, szKey, 63))
		{
			if (str.GetLength())
				str += _T(" + ");

			str += szKey;
		}		
	}	

	return str;
}

CString CHotKeyCtrlEx::GetHotKeyString(DWORD dwHotkey)
{
	return GetHotKeyString(LOWORD(dwHotkey), HIWORD(dwHotkey));
}

CString CHotKeyCtrlEx::GetHotKeyString() const
{
	return GetHotKeyString(m_wVKCode, m_wModifiers);
}

void CHotKeyCtrlEx::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
	if (nRepCnt > 1 || (nFlags & 0x4000))
		return;

	WORD wVKCode = (WORD)nChar;
	WORD WModifiers = GetModifiersFromKeyboard();
	NormalizeModifiers(wVKCode, WModifiers);

	if (wVKCode == m_wEraserVKCode && m_wModifiers == m_wEraserModifiers)
	{
		m_wVKCode = 0;
		m_wModifiers = 0;
	}
	else
	{
		m_wVKCode = wVKCode;
		m_wModifiers = WModifiers;

		if ((m_wInvalidComb & HKCOMB_A) && m_wModifiers == HOTKEYF_ALT
			|| (m_wInvalidComb & HKCOMB_C) && m_wModifiers == HOTKEYF_CONTROL
			|| (m_wInvalidComb & HKCOMB_CA) && m_wModifiers == (HOTKEYF_CONTROL | HOTKEYF_ALT)
			|| (m_wInvalidComb & HKCOMB_NONE) && m_wModifiers == 0
			|| (m_wInvalidComb & HKCOMB_S) && m_wModifiers == HOTKEYF_SHIFT
			|| (m_wInvalidComb & HKCOMB_SA) && m_wModifiers == (HOTKEYF_SHIFT | HOTKEYF_ALT)
			|| (m_wInvalidComb & HKCOMB_SC) && m_wModifiers == (HOTKEYF_SHIFT | HOTKEYF_CONTROL)
			|| (m_wInvalidComb & HKCOMB_SCA) && m_wModifiers == (HOTKEYF_CONTROL | HOTKEYF_CONTROL | HOTKEYF_ALT))
		{
			m_wModifiers = m_wRuleModifiers;
			NormalizeModifiers(m_wVKCode, m_wModifiers);
		}
	}	

	UpdateHotKeyText();
}

WORD CHotKeyCtrlEx::GetModifiersFromKeyboard()
{
	WORD wModifiers = 0;
	if (::GetKeyState(VK_CONTROL) & 0x80)
		wModifiers |= HOTKEYF_CONTROL;

	if (::GetKeyState(VK_SHIFT) & 0x80)
		wModifiers |= HOTKEYF_SHIFT;

	if (::GetKeyState(VK_MENU) & 0x80)
		wModifiers |= HOTKEYF_ALT;

	return wModifiers;
}

void CHotKeyCtrlEx::UpdateHotKeyText()
{
	CString str = GetHotKeyString();
	if (str.IsEmpty())
		str = HK_DEFAULT_KEY_NAME;
	SetWindowText(str);
	SetSel(INT_MAX, INT_MAX);
}

int CHotKeyCtrlEx::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CEdit::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	UpdateHotKeyText();	
	return 0;
}

void CHotKeyCtrlEx::PreSubclassWindow()
{
	// TODO: Add your specialized code here and/or call the base class	
	CEdit::PreSubclassWindow();
	if (::IsWindow(m_hWnd))
		UpdateHotKeyText();
}

void CHotKeyCtrlEx::NormalizeModifiers(WORD wVirtualKeyCode, WORD &wModifiers)
{
	if (wVirtualKeyCode == VK_CONTROL)
		wModifiers &= ~HOTKEYF_CONTROL;

	if (wVirtualKeyCode == VK_SHIFT)
		wModifiers &= ~HOTKEYF_SHIFT;

	if (wVirtualKeyCode == VK_MENU)
		wModifiers &= ~HOTKEYF_ALT;
	HKCOMB_A;
}

void CHotKeyCtrlEx::SetRules(WORD wInvalidComb, WORD wModifiers)
{
	m_wInvalidComb = wInvalidComb;
	m_wRuleModifiers = wModifiers;
}
