// GameInput.h : main header file for the GAMEINPUT application
//

#if !defined(AFX_GAMEINPUT_H__C3FF6C18_7017_4793_805B_35D09B560631__INCLUDED_)
#define AFX_GAMEINPUT_H__C3FF6C18_7017_4793_805B_35D09B560631__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "Includes\WinAppex.h"
#include "Includes\InputSimulate.h"
#include "GameManager.h"

/////////////////////////////////////////////////////////////////////////////
// CGameInputApp:
// See GameInput.cpp for the implementation of this class
//

class CGameInputApp : public CWinAppEx
{
public:
	CGameInputApp();
	CGameManager m_manager;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGameInputApp)
	public:
	virtual BOOL InitInstance();	
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

public:
	//{{AFX_MSG(CGameInputApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CGameManager& AfxGetManager();
int AfxFindComboByData(CComboBox* pCombo, DWORD dwData, BOOL bSelect = FALSE);
DWORD AfxGetComboSelectedData(CComboBox* pCombo);
int AfxAddComboLine(CComboBox* pCombo, LPCTSTR lpszText, DWORD dwData = 0);

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_GAMEINPUT_H__C3FF6C18_7017_4793_805B_35D09B560631__INCLUDED_)
