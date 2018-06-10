#if !defined(AFX_SCHEMELISTDLG_H__5A92E6A9_61CC_4EC6_9D1A_1963860CCF5D__INCLUDED_)
#define AFX_SCHEMELISTDLG_H__5A92E6A9_61CC_4EC6_9D1A_1963860CCF5D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SchemeListDlg.h : header file
//

#include "Includes\ListCtrlEx.h"

/////////////////////////////////////////////////////////////////////////////
// CSchemeListDlg dialog

class CSchemeListDlg : public CDialog
{
// Construction
public:
	CSchemeListDlg(CGameData* pGame, CWnd* pParent = NULL);   // standard constructor
	DWORD m_dwGameID;
	CString m_sGameName;
	BOOL m_bChanged;
	CGameData* m_pGame;

// Dialog Data
	//{{AFX_DATA(CSchemeListDlg)
	enum { IDD = IDD_SCHEMELISTDLG };
	CButton	m_wndRemove;
	CListCtrlEx	m_wndList;
	CButton	m_wndEdit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSchemeListDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSchemeListDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnEdit();
	afx_msg void OnRemove();
	afx_msg void OnAdd();
	//}}AFX_MSG
	LRESULT OnListNotify(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCHEMELISTDLG_H__5A92E6A9_61CC_4EC6_9D1A_1963860CCF5D__INCLUDED_)
