#if !defined(AFX_EDITDLG_H__DCC718A6_D841_427C_B267_6EB0BED5B50F__INCLUDED_)
#define AFX_EDITDLG_H__DCC718A6_D841_427C_B267_6EB0BED5B50F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditDlg.h : header file
//
#include "Includes\EditEx.h"
#include "Includes\HotKeyCtrlEx.h"
/////////////////////////////////////////////////////////////////////////////
// CEditDlg dialog

class CEditDlg : public CDialog
{
// Construction
public:
	CEditDlg(const ACTIONDATA* pAction, BOOL bRunOnce, CWnd* pParent = NULL);   // standard constructor

	ACTIONDATA m_action;

// Dialog Data
	//{{AFX_DATA(CEditDlg)
	enum { IDD = IDD_EDITDLG };
	CStatic	m_wndIntLbl2;
	CStatic	m_wndIntLbl1;
	CComboBox	m_wndType;
	CComboBox	m_wndMouseBtns;
	CHotKeyCtrlEx	m_wndCode;
	CEditEx	m_wndDesc;
	CEditEx	m_wndInterval;
	CEditEx	m_wndPostWait;
	CString	m_sDesc;
	int		m_nMouseBtn;
	BOOL	m_bAlt;
	BOOL	m_bCtrl;
	BOOL	m_bShift;
	int		m_nType;
	int		m_nInterval;
	int		m_nPostDelay;
	//}}AFX_DATA

	BOOL m_bRunOnce;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEditDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelchangeType();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITDLG_H__DCC718A6_D841_427C_B267_6EB0BED5B50F__INCLUDED_)
