#if !defined(AFX_GAMEDETAILDLG_H__B00E0CE4_3AF6_4E82_8F69_485552EBDCFA__INCLUDED_)
#define AFX_GAMEDETAILDLG_H__B00E0CE4_3AF6_4E82_8F69_485552EBDCFA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GameDetailDlg.h : header file
//

#include "Includes\EditEx.h"

/////////////////////////////////////////////////////////////////////////////
// CGameDetailDlg dialog

class CGameDetailDlg : public CDialog
{
// Construction
public:
	CGameDetailDlg(LPCTSTR lpszName, LPCTSTR lpszTitle, LPCTSTR lpszClass, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGameDetailDlg)
	enum { IDD = IDD_GAMEDETAILDLG };
	CEditEx	m_wndClass;
	CEditEx	m_wndText;
	CEditEx	m_wndName;
	CString	m_sName;
	CString	m_sText;
	CString	m_sClass;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGameDetailDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL ValidateTitleClass();

	// Generated message map functions
	//{{AFX_MSG(CGameDetailDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GAMEDETAILDLG_H__B00E0CE4_3AF6_4E82_8F69_485552EBDCFA__INCLUDED_)
