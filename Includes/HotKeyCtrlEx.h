//////////////////////////////////////////////////////////////////////////////////////
// HotKeyCtrlEx.h
//
// CHotKeyCtrlEx, an improvement to the MFC CHotKeyCtrl control. Allows:
// 
// 1, Configurable "eraser", that is, a key combination for erasing existing hotkeys.
// 2, Recognizes VK_SPACE, VK_BACK as valid hotkeys.
// 3, Accepts VK_CONTROL, VK_SHIFT, VK_MENU as valid hotkeys rather than modifiers only.
// 4, You can now retrieve string representation of hotkey combinations. 
//
// Written by Abin (abinn32@yahoo.com)
// Apr 19, 2006
//////////////////////////////////////////////////////////////////////////////////////

#ifndef __HOTKEYCTRLEX_H__
#define __HOTKEYCTRLEX_H__

class CHotKeyCtrlEx : public CEdit
{
public:
	
	CHotKeyCtrlEx();	
	virtual ~CHotKeyCtrlEx();

	void SetHotKey(DWORD dwHotKey);
	void SetHotKey(WORD wVirtualKeyCode, WORD wModifiers);
	DWORD GetHotKey() const;
	void GetHotKey(WORD &wVirtualKeyCode, WORD &wModifiers) const;

	static CString GetHotKeyString(DWORD dwHotkey);
	static CString GetHotKeyString(WORD wVirtualKeyCode, WORD wModifiers);
	CString GetHotKeyString() const;

	void SetEraser(DWORD dwEraser);
	void SetEraser(WORD wVirtualKeyCode, WORD wModifiers);
	DWORD GetEraser() const;
	void GetEraser(WORD &wVirtualKeyCode, WORD &wModifiers) const;

	void SetRules(WORD wInvalidComb, WORD wModifiers);

protected:

	void UpdateHotKeyText();
	static void NormalizeModifiers(WORD wVirtualKeyCode, WORD &wModifiers);
	static WORD GetModifiersFromKeyboard();
	static DWORD GetKeyName(BYTE iVKCode, LPTSTR lpszBuffer, DWORD dwMaxChars);

	WORD m_wVKCode;
	WORD m_wModifiers;
	WORD m_wEraserVKCode;
	WORD m_wEraserModifiers;
	WORD m_wInvalidComb;
	WORD m_wRuleModifiers;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHotKeyCtrlEx)
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL
	// Generated message map functions

	//{{AFX_MSG(CHotKeyCtrlEx)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

#endif // __HOTKEYCTRLEX_H__
