#if !defined(AFX_CONFIGDLG_H__19CD5770_A393_4594_B946_D1514830B470__INCLUDED_)
#define AFX_CONFIGDLG_H__19CD5770_A393_4594_B946_D1514830B470__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigDlg.h : header file
//
#include "Includes\ListCtrlEx.h"
#include "Includes\EditEx.h"

/////////////////////////////////////////////////////////////////////////////
// CConfigDlg dialog

class CConfigDlg : public CDialog
{
// Construction
public:

	CConfigDlg(HWND hParentWnd);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConfigDlg)
	enum { IDD = IDD_CONFIGDLG };
	CButton	m_wndSelHotkey;
	CButton	m_wndForeground;
	CButton	m_wndManageSchemes;
	CComboBox	m_wndGames;
	CStatic	m_wndLblGameText;
	CListCtrlEx	m_wndActionList;
	CButton	m_wndDelAction;
	CButton	m_wndDownAction;
	CButton	m_wndEditAction;
	CComboBox	m_wndSchemes;
	CButton	m_wndUpAction;
	CButton	m_wndAddAction;
	BOOL	m_bForeground;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConfigDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeSchemes();
	afx_msg void OnAddAction();
	afx_msg void OnEditAction();
	afx_msg void OnDelAction();
	afx_msg void OnUpAction();
	afx_msg void OnDownAction();
	afx_msg void OnSelgame();
	afx_msg void OnSelchangeGames();
	afx_msg void OnManagescheme();
	afx_msg void OnForeground();
	afx_msg void OnSelhotkey();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:

	void UpdateActionRow(int nIndex, const ACTIONDATA& action, BOOL bRunOnce);
	void LoadSchemeList();
	void LoadGameList();
	void LoadActionList();
	LRESULT OnListMsg(WPARAM wParam, LPARAM lParam);
	
	HICON m_hIcon;
	HWND m_hParentWnd;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGDLG_H__19CD5770_A393_4594_B946_D1514830B470__INCLUDED_)
