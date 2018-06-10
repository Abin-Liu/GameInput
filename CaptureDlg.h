#if !defined(AFX_CAPTUREDLG_H__9CDBB90E_6FAF_403A_8A5D_2313BFC9ABD3__INCLUDED_)
#define AFX_CAPTUREDLG_H__9CDBB90E_6FAF_403A_8A5D_2313BFC9ABD3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CaptureDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCaptureDlg dialog

class CCaptureDlg : public CDialog
{
// Construction
public:
	CCaptureDlg(CWnd* pParent = NULL);   // standard constructor
	int m_nRemain;

// Dialog Data
	//{{AFX_DATA(CCaptureDlg)
	enum { IDD = IDD_CAPTUREDLG };
	CStatic	m_wndCountDown;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCaptureDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCaptureDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAPTUREDLG_H__9CDBB90E_6FAF_403A_8A5D_2313BFC9ABD3__INCLUDED_)
