#if !defined(AFX_GAMEDLG_H__023AF200_8536_4562_A345_9DB518B88E3D__INCLUDED_)
#define AFX_GAMEDLG_H__023AF200_8536_4562_A345_9DB518B88E3D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GameDlg.h : header file
//

#include "Includes\ListCtrlEx.h"

/////////////////////////////////////////////////////////////////////////////
// CGameDlg dialog

class CGameDlg : public CDialog
{
// Construction
public:
	CGameDlg(CWnd* pParent = NULL);   // standard constructor
	BOOL m_bChanged;

// Dialog Data
	//{{AFX_DATA(CGameDlg)
	enum { IDD = IDD_GAMEDLG };
	CButton	m_wndEdit;
	CButton	m_wndRemove;
	CListCtrlEx	m_wndList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGameDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	LRESULT OnListNotify(WPARAM wParam, LPARAM lParam);
	void FillList();

	// Generated message map functions
	//{{AFX_MSG(CGameDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnAdd();
	afx_msg void OnRemove();
	afx_msg void OnEdit();
	afx_msg void OnCapture();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GAMEDLG_H__023AF200_8536_4562_A345_9DB518B88E3D__INCLUDED_)
