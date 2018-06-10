#if !defined(AFX_NAMEDLG_H__F0ADF0D6_C4E1_413B_8EF6_F88C7E32B8A7__INCLUDED_)
#define AFX_NAMEDLG_H__F0ADF0D6_C4E1_413B_8EF6_F88C7E32B8A7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NameDlg.h : header file
//

#include "Includes\EditEx.h"

/////////////////////////////////////////////////////////////////////////////
// CNameDlg dialog

class CNameDlg : public CDialog
{
// Construction
public:
	CNameDlg(LPCTSTR lpszName, BOOL bRunOnce, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNameDlg)
	enum { IDD = IDD_NAMEDLG };
	CEditEx	m_wndName;
	CString	m_sName;
	int		m_nType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNameDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNameDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NAMEDLG_H__F0ADF0D6_C4E1_413B_8EF6_F88C7E32B8A7__INCLUDED_)
