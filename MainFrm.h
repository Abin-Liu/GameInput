// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__9A8BE227_BD2D_4CCC_9643_D7EDDCF24049__INCLUDED_)
#define AFX_MAINFRM_H__9A8BE227_BD2D_4CCC_9643_D7EDDCF24049__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Includes\TrayFrameWnd.h"

class CMainFrame : public CTrayFrameWnd
{
	
public:
	CMainFrame();
protected: 
	DECLARE_DYNAMIC(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg void OnConfig();
	afx_msg void OnAppAbout();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnPopupReset();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	void DisplayBalloon();
	LRESULT OnHotKey(WPARAM wParam, LPARAM lParam);
	void Stop();
	void Start();

	BOOL m_bStarted;
	CString m_sGame;
	CString m_sScheme;
	int m_nActions;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__9A8BE227_BD2D_4CCC_9643_D7EDDCF24049__INCLUDED_)
