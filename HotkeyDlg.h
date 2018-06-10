#if !defined(AFX_HOTKEYDLG_H__4005002B_5A5D_4D17_8A3E_8D011A17C0D9__INCLUDED_)
#define AFX_HOTKEYDLG_H__4005002B_5A5D_4D17_8A3E_8D011A17C0D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HotkeyDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHotkeyDlg dialog

class CHotkeyDlg : public CDialog
{
// Construction
public:
	CHotkeyDlg(CWnd* pParent = NULL);   // standard constructor
	DWORD m_dwHotkey;

// Dialog Data
	//{{AFX_DATA(CHotkeyDlg)
	enum { IDD = IDD_HOTKEYDLG };
	CComboBox	m_wndComboi;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHotkeyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	int AddHotkey(DWORD dwKeyCode, LPCTSTR lpszName);

	// Generated message map functions
	//{{AFX_MSG(CHotkeyDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HOTKEYDLG_H__4005002B_5A5D_4D17_8A3E_8D011A17C0D9__INCLUDED_)
