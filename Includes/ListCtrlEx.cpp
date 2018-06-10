// ListCtrlEx.cpp : implementation file
//

#include "stdafx.h"
#include "ListCtrlEx.h"
#include <afxtempl.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static const DWORD STYLES_FORBIDDEN = LVS_EDITLABELS | LVS_ICON | LVS_SMALLICON | LVS_LIST | LVS_NOSCROLL | LVS_NOCOLUMNHEADER;
static const DWORD STYLES_MUST = WS_VISIBLE | WS_CHILD | LVS_REPORT | LVS_SHOWSELALWAYS;

/////////////////////////////////////////////////////////////////////////////
// CSortHeaderCtrl

class CSortHeaderCtrl : public CHeaderCtrl
{
public:
	
	CSortHeaderCtrl(): m_nSortColumn(-1), m_bDescending(FALSE) {}
	virtual ~CSortHeaderCtrl() {}

	void SetSortArrow(int iColumn, BOOL bDescending);
	int GetSortColumn(LPBOOL lpDescending = NULL) const;
	int GetDataType(int nColumn) const;
	int GetAlign(int nColumn) const;
	CString GetText(int nColumn) const;

protected:

	void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	void OnBegintrack(NMHDR *pNMHDR, LRESULT *pResult);
	LRESULT OnLayout(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

	int m_nSortColumn;
	BOOL m_bDescending;	
};

BEGIN_MESSAGE_MAP(CSortHeaderCtrl, CHeaderCtrl)	
	ON_NOTIFY_REFLECT(HDN_BEGINTRACKA, OnBegintrack)
	ON_NOTIFY_REFLECT(HDN_BEGINTRACKW, OnBegintrack)
	ON_MESSAGE(HDM_LAYOUT, OnLayout)
END_MESSAGE_MAP()

int CSortHeaderCtrl::GetDataType(int nColumn) const
{
	HDITEM hdi = { 0 };
	hdi.mask = HDI_LPARAM;
	GetItem(nColumn, &hdi);
	return int(hdi.lParam);
}

int CSortHeaderCtrl::GetAlign(int nColumn) const
{
	HDITEM hdi = { 0 };
	hdi.mask = HDI_FORMAT;
	GetItem(nColumn, &hdi);
	int fmt = hdi.fmt;
	if (fmt & HDF_CENTER)
		return LVCFMT_CENTER;

	if (fmt & HDF_RIGHT)
		return LVCFMT_RIGHT;

	return LVCFMT_LEFT;
}

CString CSortHeaderCtrl::GetText(int nColumn) const
{
	HDITEM hdi = { 0 };
	TCHAR szText[256] = _T("");
	hdi.pszText = szText;
	hdi.cchTextMax = 255;
	hdi.mask = HDI_TEXT;
	GetItem(nColumn, &hdi);
	return szText;
}

void CSortHeaderCtrl::OnBegintrack(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER lpnh = (LPNMHEADER)pNMHDR;
	*pResult = GetDataType(lpnh->iItem) == LVEX_FMT_HIDDEN;
}

int CSortHeaderCtrl::GetSortColumn(LPBOOL lpDescending) const
{
	if (lpDescending)
		*lpDescending = m_bDescending;
	return m_nSortColumn;
}

void CSortHeaderCtrl::SetSortArrow(int iSortColumn, BOOL bDescending)
{
	m_nSortColumn = iSortColumn;
	m_bDescending = bDescending;

	// change the item to owner drawn.
	HD_ITEM hditem;
	hditem.mask = HDI_FORMAT;
	GetItem(iSortColumn, &hditem);
	hditem.fmt |= HDF_OWNERDRAW;
	SetItem(iSortColumn, &hditem);
	Invalidate();
}

LRESULT CSortHeaderCtrl::OnLayout(WPARAM wParam, LPARAM lParam)
{
	LRESULT lResult = CHeaderCtrl::DefWindowProc(HDM_LAYOUT, 0, lParam);
	HD_LAYOUT &hdl = *(HD_LAYOUT*) lParam;
	RECT *prc = hdl.prc;
	WINDOWPOS *pwpos = hdl.pwpos;
	pwpos->cy = LVEX_ITEMHEIGHT;
	prc->top = LVEX_ITEMHEIGHT;
	return lResult;
}

void CSortHeaderCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// attath to the device context.
	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);

	// save the device context.
	const int iSavedDC = dc.SaveDC();

	// get the column rect.
	CRect rc(lpDrawItemStruct->rcItem);

	// set the clipping region to limit drawing within the column.
	CRgn rgn;
	rgn.CreateRectRgnIndirect(&rc);
	dc.SelectObject(&rgn);
	rgn.DeleteObject();

	// draw the background,
	CBrush brush(GetSysColor(COLOR_3DFACE));
	dc.FillRect(rc, &brush);

	// get the column text and format.
	TCHAR szText[ 256 ];
	HD_ITEM hditem;

	hditem.mask = HDI_TEXT | HDI_FORMAT;
	hditem.pszText = szText;
	hditem.cchTextMax = 255;

	GetItem(lpDrawItemStruct->itemID, &hditem);

	// determine the format for drawing the column label.
	UINT uFormat = DT_SINGLELINE | DT_NOPREFIX | DT_NOCLIP | DT_VCENTER | DT_END_ELLIPSIS ;

	if(hditem.fmt & HDF_CENTER)
		uFormat |= DT_CENTER;
	else if(hditem.fmt & HDF_RIGHT)
		uFormat |= DT_RIGHT;
	else
		uFormat |= DT_LEFT;

	// adjust the rect if the mouse button is pressed on it.
	if(lpDrawItemStruct->itemState == ODS_SELECTED)
	{
		rc.left++;
		rc.top += 2;
		rc.right++;
	}

	CRect rcIcon(lpDrawItemStruct->rcItem);
	const int iOffset = (rcIcon.bottom - rcIcon.top) / 4;

	// adjust the rect further if the sort arrow is to be displayed.
	if(lpDrawItemStruct->itemID == (UINT)m_nSortColumn)
		rc.right -= 3 * iOffset;

	rc.left += iOffset;
	rc.right -= iOffset;

	// draw the column label.
	if(rc.left < rc.right)
		dc.DrawText(szText, -1, rc, uFormat);

	// draw the sort arrow.
	if(lpDrawItemStruct->itemID == (UINT)m_nSortColumn)
	{
		// set up the pens to use for drawing the arrow.
		CPen penLight(PS_SOLID, 1, GetSysColor(COLOR_3DHILIGHT));
		CPen penShadow(PS_SOLID, 1, GetSysColor(COLOR_3DSHADOW));
		CPen* pOldPen = dc.SelectObject(&penLight);

		if(m_bDescending)
		{
			// draw the arrow pointing downwards.
			dc.MoveTo(rcIcon.right - iOffset - 1, iOffset);
			dc.LineTo(rcIcon.right - 2 * iOffset - 1, rcIcon.bottom - iOffset);
			dc.SelectObject(&penShadow);
			dc.MoveTo(rcIcon.right - 2 * iOffset - 2, rcIcon.bottom - iOffset);
			dc.LineTo(rcIcon.right - 3 * iOffset - 1, iOffset);
			dc.LineTo(rcIcon.right - iOffset - 1, iOffset);
		}
		else
		{			
			// draw the arrow pointing upwards.
			dc.MoveTo(rcIcon.right - 2 * iOffset, iOffset);
			dc.LineTo(rcIcon.right - iOffset, rcIcon.bottom - iOffset - 1);
			dc.LineTo(rcIcon.right - 3 * iOffset - 2, rcIcon.bottom - iOffset - 1);
			dc.SelectObject(&penShadow);
			dc.MoveTo(rcIcon.right - 3 * iOffset - 1, rcIcon.bottom - iOffset - 1);
			dc.LineTo(rcIcon.right - 2 * iOffset, iOffset - 1);		
		}

		// restore the pen.
		dc.SelectObject(pOldPen);
	}

	// restore the previous device context.
	dc.RestoreDC(iSavedDC);

	// detach the device context before returning.
	dc.Detach();
}

// Temporary data used for column sorting
struct LVEX_SORTROWDATA
{
	DWORD dwData;		// The real data returned by CListCtrl::GetItemData
	DWORD dwVal;		// Integer data
	double fVal;		// Double data
	COleDateTime dVal;	// Date-time data
	CString sText;		// Text data
};

/////////////////////////////////////////////////////////////////////////////
// CListCtrlEx

CListCtrlEx::CListCtrlEx()
{
	m_pHeaderCtrl = new CSortHeaderCtrl;
	m_il.Create(1, LVEX_ITEMHEIGHT, ILC_COLOR24, 1, 1);
	m_nSelection = -1;
	m_dwSelectedData = 0;
	m_bCustomDraw = FALSE;
	m_bIsSorting = FALSE;
	m_dwHoverLink = LVEX_GRID_INVALID;
	m_hHandCursor = ::LoadCursor(NULL, IDC_HAND);
	m_hNormalCursor = ::LoadCursor(NULL, IDC_ARROW);	
	m_cLinkColor = RGB(0, 0, 255);
	m_cHoverColor = RGB(255, 0, 0);
	ClearHyperlinkUrlColumns();
}

CListCtrlEx::~CListCtrlEx()
{
	delete m_pHeaderCtrl;
	m_il.DeleteImageList();
}

BEGIN_MESSAGE_MAP(CListCtrlEx, CListCtrl)
	//{{AFX_MSG_MAP(CListCtrlEx)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONDOWN()
	ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnCustomDraw)
	ON_NOTIFY_REFLECT(LVN_ITEMCHANGED, OnItemchanged)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnclick)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListCtrlEx message handlers

void CListCtrlEx::OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LPNMLVCUSTOMDRAW lplvcd = (LPNMLVCUSTOMDRAW)pNMHDR;

	if (lplvcd->nmcd.dwDrawStage == CDDS_PREPAINT)
	{
	    *pResult = CDRF_NOTIFYITEMDRAW;
	}
    else if (lplvcd->nmcd.dwDrawStage == CDDS_ITEMPREPAINT)
	{
	    *pResult = CDRF_NOTIFYSUBITEMDRAW;
	}
    else if (lplvcd->nmcd.dwDrawStage == (CDDS_ITEMPREPAINT | CDDS_SUBITEM))
    {
		const int ROW = lplvcd->nmcd.dwItemSpec;
		const int COL = lplvcd->iSubItem;

		if (ROW >= 0 && COL >= 0)
		{
			if (GetFieldHyperlink(ROW, COL).GetLength())			
			{
				if (LOWORD(m_dwHoverLink) == ROW && HIWORD(m_dwHoverLink) == COL)
					lplvcd->clrText = m_cHoverColor;
				else
					lplvcd->clrText = m_cLinkColor;
			}
			else
			{
				lplvcd->clrText = 0;
				if (m_bCustomDraw)
					SendNotify(LVEX_WM_CUSTOMDRAW, ROW, COL, &lplvcd->clrText, &lplvcd->clrTextBk);
			}			
		}
		
		*pResult = CDRF_DODEFAULT;
	}
}

void CListCtrlEx::EnableCustomDraw(BOOL bEnable)
{
	if (!m_bCustomDraw != !bEnable)
	{
		m_bCustomDraw = bEnable;
		if (::IsWindow(m_hWnd) && IsWindowVisible())
			RedrawWindow();
	}
}

BOOL CListCtrlEx::IsCustomDrawEnabled() const
{
	return m_bCustomDraw;
}

int CListCtrlEx::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CListCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	InitListStyles();
	return 0;
}

DWORD CListCtrlEx::TestHoverLink(const CPoint& point)
{
	LVHITTESTINFO hti;
	hti.pt = point;
	SubItemHitTest(&hti);

	if (hti.iItem < 0 || hti.iSubItem < 0 || (hti.flags & LVHT_ONITEMLABEL) == 0)
		return LVEX_GRID_INVALID;

	if (GetFieldHyperlink(hti.iItem, hti.iSubItem).IsEmpty())
		return LVEX_GRID_INVALID;

	CString sText = GetItemText(hti.iItem, hti.iSubItem);
	if (sText.IsEmpty())
		return LVEX_GRID_INVALID;

	CRect rect;
	GetSubItemRect(hti.iItem, hti.iSubItem, LVIR_LABEL, rect);
			
	CDC* pDC = GetDC();
	pDC->SelectObject(GetFont());
	int nTextWidth = pDC->GetTextExtent(sText).cx;
	ReleaseDC(pDC);

	int nOverWidth = rect.Width() - nTextWidth - 6;
	if (nOverWidth > 2)
	{
		switch (GetColumnAlignFmt(hti.iSubItem))
		{
		case LVCFMT_CENTER:
			rect.DeflateRect(nOverWidth / 2, 0, nOverWidth / 2, 0);
			break;

		case LVCFMT_RIGHT:
			rect.DeflateRect(nOverWidth, 0, 0, 0);
			break;

		default:
			rect.DeflateRect(0, 0, nOverWidth, 0);
			break;
		}

		if (!rect.PtInRect(point))
			return LVEX_GRID_INVALID;
	}	

	return MAKELONG((WORD)hti.iItem, (WORD)hti.iSubItem);
}

void CListCtrlEx::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	DWORD dwHover = TestHoverLink(point);
	if (m_dwHoverLink != dwHover)
	{
		DWORD dwOld = m_dwHoverLink;
		m_dwHoverLink = dwHover;

		CRect rect;
		if (dwOld != LVEX_GRID_INVALID)
		{
			GetSubItemRect(LOWORD(dwOld), HIWORD(dwOld), LVIR_BOUNDS, rect);
			RedrawWindow(rect);
		}

		if (m_dwHoverLink != LVEX_GRID_INVALID)
		{
			GetSubItemRect(LOWORD(m_dwHoverLink), HIWORD(m_dwHoverLink), LVIR_BOUNDS, rect);
			RedrawWindow(rect);
			SetTimer(0, 100, NULL);
		}
		else
		{
			KillTimer(0);
		}
	}

	CListCtrl::OnMouseMove(nFlags, point);
}

void CListCtrlEx::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default	
	BOOL bHyperlink = FALSE;
	if (m_dwHoverLink != LVEX_GRID_INVALID)
	{
		CString sHyperlink = GetFieldHyperlink(LOWORD(m_dwHoverLink), HIWORD(m_dwHoverLink));
		if (!sHyperlink.IsEmpty())
		{
			::ShellExecute(NULL, _T("open"), sHyperlink, NULL, NULL, SW_SHOW);
			return;
		}
	}

	CListCtrl::OnLButtonDown(nFlags, point);
}

void CListCtrlEx::OnDestroy()
{
	KillTimer(0);
}

void CListCtrlEx::OnTimer(UINT nIDEvent)
{
	CRect rect;
	GetClientRect(&rect);
	ClientToScreen(&rect);
	
	POINT pt;
	::GetCursorPos(&pt);
	if (rect.PtInRect(pt))
		return;

	KillTimer(0);
	GetSubItemRect(LOWORD(m_dwHoverLink), HIWORD(m_dwHoverLink), LVIR_BOUNDS, rect);
	m_dwHoverLink = LVEX_GRID_INVALID;
	RedrawWindow(rect);	
}

BOOL CListCtrlEx::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
    if (m_dwHoverLink != LVEX_GRID_INVALID)
		::SetCursor(m_hHandCursor);		
	else
		::SetCursor(m_hNormalCursor);
    return TRUE;
}

void CListCtrlEx::OnClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	SendNotify(LVEX_WM_CLICK, pNMListView->iItem, pNMListView->iSubItem);		
	*pResult = 0;
}

void CListCtrlEx::CheckItemChange()
{
	if (m_bIsSorting)
		return;

	int nSel = -1;
	POSITION pos = GetFirstSelectedItemPosition();
	if (pos)
		nSel = GetNextSelectedItem(pos);

	if (nSel != m_nSelection)
	{
		m_nSelection = nSel;
		m_dwSelectedData = 0;
		if (nSel >= 0)
			m_dwSelectedData = GetItemData(nSel);
		SendNotify(LVEX_WM_SELCHANGE, m_nSelection);
	}
}

int CListCtrlEx::GetSelection() const
{
	return m_nSelection;
}

DWORD CListCtrlEx::GetSelectedData() const
{
	return m_dwSelectedData;
}

CString CListCtrlEx::GetItemText(int nIndex, int nColumn) const
{	
	if (nIndex < 0)
		nIndex = m_nSelection;
	
	return CListCtrl::GetItemText(nIndex, nColumn);
}

int CListCtrlEx::GetItemText(int nIndex, int nColumn, LPTSTR lpszText, int nLen) const
{
	if (nIndex < 0)
		nIndex = m_nSelection;

	return CListCtrl::GetItemText(nIndex, nColumn, lpszText, nLen);
}

CString CListCtrlEx::GetFieldText(int nIndex, int nColumn) const
{	
	return GetItemText(nIndex, nColumn);
}

int CListCtrlEx::GetFieldText(int nIndex, int nColumn, LPTSTR lpszText, int nLen) const
{
	return GetItemText(nIndex, nColumn, lpszText, nLen);
}

BOOL CListCtrlEx::IsFieldEmpty(int nIndex, int nColumn) const
{
	CString str = GetItemText(nIndex, nColumn);
	return str.IsEmpty();
}

int CListCtrlEx::GetFieldInt(int nIndex, int nColumn) const
{
	return (int)GetFieldLong(nIndex, nColumn);
}

UINT CListCtrlEx::GetFieldUInt(int nIndex, int nColumn, int nBase) const
{
	return (UINT)GetFieldULong(nIndex, nColumn, nBase);
}

long CListCtrlEx::GetFieldLong(int nIndex, int nColumn) const
{
	return _ttoi(GetFieldText(nIndex, nColumn));
}

DWORD CListCtrlEx::GetFieldULong(int nIndex, int nColumn, int nBase) const
{
	return _tcstoul(GetFieldText(nIndex, nColumn), NULL, nBase);
}

double CListCtrlEx::GetFieldDouble(int nIndex, int nColumn) const
{
	return _tcstod(GetFieldText(nIndex, nColumn), NULL);
}

COleDateTime CListCtrlEx::GetFieldDateTime(int nIndex, int nColumn, DWORD dwFlags, LCID lcid) const
{
	COleDateTime date;
	date.ParseDateTime(GetFieldText(nIndex, nColumn), dwFlags, lcid);
	return date;
}

COleCurrency CListCtrlEx::GetFieldMoney(int nIndex, int nColumn) const
{
	COleCurrency fMoney(0, 0);
	fMoney.ParseCurrency(GetFieldText(nIndex, nColumn));
	return fMoney;
}

CString CListCtrlEx::GetFieldHyperlink(int nIndex, int nColumn) const
{
	int nUrlCol = GetHyperlinkUrlColumn(nColumn);
	if (nUrlCol == -1)
		return _T("");

	return GetFieldText(nIndex, nUrlCol);
}

int CListCtrlEx::GetFieldSeconds(int nIndex, int nColumn) const
{
	CString sText = GetFieldText(nIndex, nColumn);
	int nLen = sText.GetLength();
	if (nLen < 7)
		return 0;

	BOOL bNegative = FALSE;
	if (sText.GetAt(0) == _T('-'))
	{
		bNegative = TRUE;
		sText = sText.Mid(1);
	}

	int nSeconds = 0;
	// 0:00:00 the lease, cannot be shorter than 7 chars
	CString sHour, sMin, sSec;
	sSec = sText.Right(2);
	sMin = sText.Mid(nLen - 5, 2);
	sHour = sText.Left(nLen - 6);					
	nSeconds = _ttoi(sHour) * 3600 + _ttoi(sMin) * 60 + _ttoi(sSec);

	if (bNegative)
		nSeconds = -nSeconds;

	return nSeconds;			
}

BOOL CListCtrlEx::SetItemText(int nIndex, int nColumn, LPCTSTR lpszValue)
{
	if (nIndex < 0)
		nIndex = m_nSelection;

	return CListCtrl::SetItemText(nIndex, nColumn, lpszValue);
}

BOOL CListCtrlEx::SetFieldText(int nIndex, int nColumn, LPCTSTR lpszValue)
{
	return SetItemText(nIndex, nColumn, lpszValue);
}

BOOL CListCtrlEx::SetFieldLong(int nIndex, int nColumn, long nValue, BOOL bEmptyIfZero)
{
	if (bEmptyIfZero && nValue == 0)
		return SetFieldText(nIndex, nColumn, NULL);

	CString str;
	str.Format(_T("%d"), nValue);
	return SetFieldText(nIndex, nColumn, str);
}

BOOL CListCtrlEx::SetFieldULong(int nIndex, int nColumn, DWORD dwValue, LPCTSTR lpszFormat, BOOL bEmptyIfZero)
{
	if (bEmptyIfZero && dwValue == 0)
		return SetFieldText(nIndex, nColumn, NULL);

	CString str;	
	str.Format(lpszFormat ? lpszFormat : _T("%d"), dwValue);
	return SetFieldText(nIndex, nColumn, str);
}

BOOL CListCtrlEx::SetFieldDouble(int nIndex, int nColumn, double fValue, int nPrecision, BOOL bTrim, BOOL bEmptyIfZero)
{
	if (bEmptyIfZero && fValue == 0.0)
		return SetFieldText(nIndex, nColumn, NULL);

	CString str;	
	if (nPrecision < 0)
	{
		str.Format(_T("%f"), fValue);
		if (bTrim)
		{
			str.TrimRight(_T('0'));
			str.TrimRight(_T('.'));
		}
	}
	else
	{
		CString sFmt;
		sFmt.Format(_T("%%.%df"), nPrecision);
		str.Format(sFmt, fValue);
	}

	return SetFieldText(nIndex, nColumn, str);
}

BOOL CListCtrlEx::SetFieldDateTime(int nIndex, int nColumn, COleDateTime dValue, DWORD dwFormat)
{
	CString sDateTime;
	if (dwFormat)
		sDateTime = dValue.Format(dwFormat);
	else
		sDateTime = dValue.Format(_T("%Y-%m-%d %H:%M:%S"));
	return SetFieldText(nIndex, nColumn, sDateTime);
}

BOOL CListCtrlEx::SetFieldHyperlink(int nIndex, int nColumn, LPCTSTR lpszHyperlink)
{
	int nUrlCol = GetHyperlinkUrlColumn(nColumn);
	if (nUrlCol == -1)
		return FALSE;

	return SetFieldText(nIndex, nUrlCol, lpszHyperlink);
}

BOOL CListCtrlEx::SetFieldMoney(int nIndex, int nColumn, COleCurrency fMoney, BOOL bEmptyIfZero)
{
	CString sResult;
	sResult.Format(_T("%.2f"), _tcstod(fMoney.Format(), NULL));	

	if (bEmptyIfZero && sResult == _T("0.00"))
		sResult.Empty();

	return SetFieldText(nIndex, nColumn, sResult);
}

BOOL CListCtrlEx::SetFieldSeconds(int nIndex, int nColumn, int nSeconds, BOOL bCanBeNegative, BOOL bEmptyIfZero)
{
	if (bEmptyIfZero && nSeconds == 0)
		return SetFieldText(nIndex, nColumn, NULL);

	BOOL bNegative = FALSE;
	if (nSeconds < 0)
	{
		if (bCanBeNegative)
		{
			bNegative = TRUE;
			nSeconds = -nSeconds;
		}
		else
		{
			nSeconds = 0;
		}
	}

	CString sResult;
	sResult.Format(_T("%d:%02d:%02d"), nSeconds / 3600, (nSeconds % 3600) / 60, nSeconds % 60);

	if (bNegative)
		sResult = CString(_T('-')) + sResult;

	return SetFieldText(nIndex, nColumn, sResult);
}

int CListCtrlEx::AddItem(LPCTSTR lpszText, DWORD dwData)
{
	const int IDX = InsertItem(INT_MAX, lpszText);
	if (dwData)
		SetItemData(IDX, dwData);
	return IDX;
}

void CListCtrlEx::OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	/*
	if (pNMListView->iItem >= 0)
	{
		BOOL bWasSelected = (pNMListView->uOldState & LVIS_SELECTED) != 0;
		BOOL bNowSelected = (pNMListView->uNewState & LVIS_SELECTED) != 0;
		if (bWasSelected != bNowSelected)
			CheckItemChange(pNMListView->iItem, bWasSelected, bNowSelected);		
	}
	*/
	
	CheckItemChange();
	*pResult = 0;
}

void CListCtrlEx::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	//if (pNMListView->iItem >= 0 && pNMListView->iSubItem >= 0)
	SendNotify(LVEX_WM_DBLCLICK, pNMListView->iItem, pNMListView->iSubItem);
	*pResult = 0;
}

void CListCtrlEx::OnRclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	//if (pNMListView->iItem >= 0 && pNMListView->iSubItem >= 0)
	SendNotify(LVEX_WM_RCLICK, pNMListView->iItem, pNMListView->iSubItem);
	*pResult = 0;
}

int CListCtrlEx::InsertColumn(int nColumn, LPCTSTR lpszText, int nWidth, int nDataType, int nAlign)
{
	if (nAlign < 0)
	{
		switch (nDataType)
		{
		case LVEX_FMT_INT:
		case LVEX_FMT_UINT:
		case LVEX_FMT_HEX:
		case LVEX_FMT_DOUBLE:
		case LVEX_FMT_SECONDS:
			nAlign = LVCFMT_RIGHT;
			break;

		default:
			nAlign = LVCFMT_LEFT;
			break;
		}	
	}

	if (nDataType == LVEX_FMT_HIDDEN)
		nWidth = 0;	

	nColumn = CListCtrl::InsertColumn(nColumn < 0 ? INT_MAX : nColumn, lpszText, nAlign, nWidth, -1);
	if (nColumn >= 0)
	{
		HDITEM hdi = { 0 };
		hdi.lParam = (LPARAM)nDataType;
		hdi.mask = HDI_LPARAM;
		m_pHeaderCtrl->SetItem(nColumn, &hdi);
	}

	return nColumn;
}

int CListCtrlEx::AddColumn(LPCTSTR lpszText, int nWidth, int nDataType, int nAlign)
{
	return InsertColumn(INT_MAX, lpszText, nWidth, nDataType, nAlign);
}

void CListCtrlEx::InitListStyles()
{
	ModifyStyle(STYLES_FORBIDDEN, STYLES_MUST);
	
	CHeaderCtrl* pHead = CListCtrl::GetHeaderCtrl();
	if (pHead)
		m_pHeaderCtrl->SubclassWindow(pHead->GetSafeHwnd());
	
	SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_SUBITEMIMAGES);
	CListCtrl::SetImageList(&m_il, LVSIL_SMALL);
}

BOOL CListCtrlEx::Create(CWnd* pParentWnd, DWORD dwStyles, UINT nID)
{
	dwStyles &= ~STYLES_FORBIDDEN;
	dwStyles |= STYLES_MUST;
	return CListCtrl::Create(dwStyles, CRect(0, 0, 1, 1), pParentWnd, nID);
}

void CListCtrlEx::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class	
	CListCtrl::PreSubclassWindow();	
	InitListStyles();
}

int CListCtrlEx::GetColumnCount() const
{
	return m_pHeaderCtrl->GetItemCount();
}

void CListCtrlEx::SaveColumnWidth(LPCTSTR lpszSection) const
{
	CString str;
	HDITEM hdi = { 0 };
	hdi.mask = HDI_WIDTH | HDI_LPARAM;
	
	int nCount = GetColumnCount();
	for (int i = 0; i < nCount; i++)
	{
		if (m_pHeaderCtrl->GetItem(i, &hdi) && hdi.lParam != LVEX_FMT_HIDDEN)
		{
			str.Format(_T("%03d"), i);
			AfxGetApp()->WriteProfileInt(lpszSection, str, hdi.cxy);
		}
	}
	AfxGetApp()->WriteProfileInt(lpszSection, _T("Count"), nCount);
}

void CListCtrlEx::LoadColumnWidth(LPCTSTR lpszSection)
{
	CHeaderCtrl* phc = CListCtrl::GetHeaderCtrl();
	CString str;
	HDITEM hdi = { 0 };
	hdi.mask = HDI_WIDTH | HDI_LPARAM;
	
	int nCount = GetColumnCount();
	if (nCount < 1 || nCount != (int)AfxGetApp()->GetProfileInt(lpszSection, _T("Count"), 0))
		return;
	
	for (int i = 0; i < nCount; i++)
	{
		if (phc->GetItem(i, &hdi) && hdi.lParam != LVEX_FMT_HIDDEN)
		{
			str.Format(_T("%03d"), i);
			int cx = AfxGetApp()->GetProfileInt(lpszSection, str, -1);
			if (cx > 4)
			{
				hdi.cxy = cx;
				phc->SetItem(i, &hdi);
			}
		}
	}
}

void CListCtrlEx::DeleteSavedColumnWidth(LPCTSTR lpszSection)
{
	AfxGetApp()->WriteProfileInt(lpszSection, _T("Count"), 0);
}

BOOL CListCtrlEx::DeleteItem(int nIndex)
{
	if (nIndex < 0)
		nIndex = m_nSelection;

	if (nIndex < 0)
		return FALSE;

	return CListCtrl::DeleteItem(nIndex);
}

int CListCtrlEx::DeleteAllSelectedItems()
{
	if (GetSelectedCount() < 1)
		return 0;
	
	CArray<int, int> arr;
	POSITION pos = GetFirstSelectedItemPosition();
	while (pos)
	{
		int nIndex = GetNextSelectedItem(pos);
		arr.Add(nIndex);
	}

	int nCount = arr.GetSize();
	for (int i = nCount - 1; i >= 0; i--)
		DeleteItem(arr[i]);
	
	return nCount;
}

BOOL CListCtrlEx::SelectItem(int nIndex)
{
	DWORD dwFlags = LVIS_SELECTED;
	if (GetFocus() == this)
		dwFlags |= LVIS_FOCUSED;
	return CListCtrl::SetItemState(nIndex, dwFlags, dwFlags);
}

void CListCtrlEx::UnselectItem(int nItem)
{
	CListCtrl::SetItemState(nItem, 0, LVIS_FOCUSED | LVIS_SELECTED);
}

int CListCtrlEx::GetSortColumn(LPBOOL lpDescending) const
{
	return ((CSortHeaderCtrl*)m_pHeaderCtrl)->GetSortColumn(lpDescending);
}

BOOL CListCtrlEx::SortItems(int nColumn, BOOL bDescending, int nDataType)
{
	if (m_bIsSorting)
		return FALSE;

	if (nColumn < 0 || nColumn >= GetColumnCount())
	{
		HideSortArrow();
		return FALSE;
	}

	SendNotify(LVEX_WM_SORTSTART, bDescending, nColumn);
	bDescending = !!bDescending;
	BOOL bOldDescending;
	int nOldSortColumn = GetSortColumn(&bOldDescending);
	BOOL bOK = TRUE;

	if (GetItemCount() > 1 && (nOldSortColumn != nColumn || !bOldDescending != !bDescending))
		bOK = InternalSort(nColumn, bDescending, nDataType);

	if (bOK)
		((CSortHeaderCtrl*)m_pHeaderCtrl)->SetSortArrow(nColumn, bDescending);

	SendNotify(LVEX_WM_SORTEND, bDescending, nColumn);
	CheckItemChange();
	return bOK;
}

BOOL CListCtrlEx::InternalSort(int nColumn, BOOL bDescending, int nDataType)
{	
	m_bIsSorting = TRUE;
	LockWindowUpdate();

	int nCount = GetItemCount();
	int i;
	for (i = 0; i < nCount; i++)
	{
		LVEX_SORTROWDATA* pData = new LVEX_SORTROWDATA;
		pData->dwData = GetItemData(i);
		SetItemData(i, (DWORD)pData);

		CString sText = GetItemText(i, nColumn);
		switch (nDataType)
		{
		case LVEX_FMT_INT:
			pData->dwVal = (LONG)_tcstol(sText, NULL, 10);
			break;

		case LVEX_FMT_UINT:
			pData->dwVal = _tcstoul(sText, NULL, 10);
			break;

		case LVEX_FMT_HEX:
			pData->dwVal = _tcstoul(sText, NULL, 16);
			break;

		case LVEX_FMT_DOUBLE:
			pData->fVal = _tcstod(sText, NULL);
			break;

		case LVEX_FMT_DATETIME:
			pData->dVal.ParseDateTime(sText);
			break;

		case LVEX_FMT_SECONDS:
			pData->dwVal = GetFieldSeconds(i, nColumn);			
			break;

		default:
			pData->sText = sText;
			break;
		}
	}

	BOOL bOK = CListCtrl::SortItems(CompareFunc, MAKELPARAM((WORD)nDataType, (WORD)bDescending));

	for (i = 0; i < nCount; i++)
	{
		LVEX_SORTROWDATA* pData = (LVEX_SORTROWDATA*)GetItemData(i);
		ASSERT(pData);
		SetItemData(i, pData->dwData);
		delete pData;
	}
	
	UnlockWindowUpdate();
	m_bIsSorting = FALSE;
	return bOK;
}

int CListCtrlEx::CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	LVEX_SORTROWDATA* pData1 = (LVEX_SORTROWDATA*)lParam1;
	LVEX_SORTROWDATA* pData2 = (LVEX_SORTROWDATA*)lParam2;
	ASSERT(pData1);
	ASSERT(pData2);

	int nResult = 0;
	switch (LOWORD(lParamSort))
	{
	case LVEX_FMT_INT:
	case LVEX_FMT_SECONDS:
		if ((LONG)pData1->dwVal < (LONG)pData2->dwVal)
			nResult = -1;
		else if ((LONG)pData1->dwVal > (LONG)pData2->dwVal)
			nResult = 1;
		break;

	case LVEX_FMT_UINT:
	case LVEX_FMT_HEX:
		if (pData1->dwVal < pData2->dwVal)
			nResult = -1;
		else if (pData1->dwVal > pData2->dwVal)
			nResult = 1;
		break;

	case LVEX_FMT_DOUBLE:
		if (pData1->fVal < pData2->fVal)
			nResult = -1;
		else if (pData1->fVal > pData2->fVal)
			nResult = 1;
		break;

	case LVEX_FMT_DATETIME:
		if (pData1->dVal < pData2->dVal)
			nResult = -1;
		else if (pData1->dVal > pData2->dVal)
			nResult = 1;
		break;

	default:
		nResult = pData1->sText.Compare(pData2->sText);
		break;
	}	

	return HIWORD(lParamSort) ? -nResult : nResult;
}

void CListCtrlEx::OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int nColumn = pNMListView->iSubItem;
	BOOL bOldDescending;
	int nOldSortColumn = GetSortColumn(&bOldDescending);
	SortItems(nColumn, nColumn == nOldSortColumn ? !bOldDescending : FALSE, GetColumnDataType(nColumn));
	*pResult = 0;
}

CHeaderCtrl* CListCtrlEx::GetHeaderCtrl()
{
	return m_pHeaderCtrl;
}

const CHeaderCtrl* CListCtrlEx::GetHeaderCtrl() const
{
	return m_pHeaderCtrl;
}

int CListCtrlEx::GetColumnDataType(int nColumn) const
{	
	return ((CSortHeaderCtrl*)m_pHeaderCtrl)->GetDataType(nColumn);
}

CString CListCtrlEx::GetColumnText(int nColumn) const
{
	return ((CSortHeaderCtrl*)m_pHeaderCtrl)->GetText(nColumn);
}

int CListCtrlEx::GetColumnAlignFmt(int nColumn) const
{
	return ((CSortHeaderCtrl*)m_pHeaderCtrl)->GetAlign(nColumn);
}

BOOL CListCtrlEx::DeleteAllItems()
{
	HideSortArrow();
	return CListCtrl::DeleteAllItems();
}

void CListCtrlEx::SendNotify(UINT nNotifyType, int nItem, int nSubItem, LPCOLORREF pClrText, LPCOLORREF pClrTextBk)
{
	LVEXNOTIFY lvn;
	lvn.nNotifyType = nNotifyType;
	lvn.nItem = nItem;
	lvn.nSubItem = nSubItem;
	lvn.pClrText = pClrText;
	lvn.pClrTextBk = pClrTextBk;
	GetParent()->SendMessage(WM_LVEX_NOTIFY, (WPARAM)&lvn, (LPARAM)this);
}

void CListCtrlEx::SetHyperlinkColors(COLORREF cLinkColor, COLORREF cHoverColor)
{
	m_cLinkColor = cLinkColor;
	m_cHoverColor = cHoverColor;
	if (::IsWindow(m_hWnd))
		RedrawWindow();
}

void CListCtrlEx::ClearHyperlinkUrlColumns()
{
	::memset(m_aUrlMap, 0xff, sizeof(m_aUrlMap));
}

void CListCtrlEx::RegisterHyperlinkUrlColumn(int nTextColumn, int nUrlColumn)
{
	ASSERT(nTextColumn >= 0 && nTextColumn < 256);
	if (nUrlColumn < -1)
		nUrlColumn = -1;
	m_aUrlMap[nTextColumn] = (BYTE)nUrlColumn;
}

int CListCtrlEx::GetHyperlinkUrlColumn(int nTextColumn) const
{
	ASSERT(nTextColumn >= 0 && nTextColumn < 256);
	BYTE i = m_aUrlMap[nTextColumn];
	if (i == 0xff)
		return -1;

	return (int)i;
}

void CListCtrlEx::HideSortArrow()
{
	((CSortHeaderCtrl*)m_pHeaderCtrl)->SetSortArrow(-1, FALSE);
}

BOOL CListCtrlEx::SwapItems(int nItem1, int nItem2)
{
	int nCount = GetItemCount();
	if (nItem1 == nItem2 || nItem1 < 0 || nItem1 >= nCount || nItem2 < 0 || nItem2 >= nCount)
		return FALSE;

	// Make a copy of row2
	DWORD dwItemID = CListCtrl::GetItemData(nItem2);
	CStringArray aTexts;
	int nCols = GetColumnCount();

	int i = 0;
	for (i = 0; i < nCols; i++)
		aTexts.Add(CListCtrl::GetItemText(nItem2, i));
	
	//  Copy texts from row1 to row2
	for (i = 0; i < nCols; i++)
		CListCtrl::SetItemText(nItem2, i, CListCtrl::GetItemText(nItem1, i));

	// Copy item data from row1 to row2
	CListCtrl::SetItemData(nItem2, CListCtrl::GetItemData(nItem1));

	// Restore texts to row1
	for (i = 0; i < nCols; i++)
		CListCtrl::SetItemText(nItem1, i, aTexts[i]);

	// Restore item data to row1
	CListCtrl::SetItemData(nItem1, dwItemID);

	if (GetSelection() == nItem1)
	{
		UnselectItem(nItem1);
		SelectItem(nItem2);
	}
	else if (GetSelection() == nItem2)
	{
		UnselectItem(nItem2);
		SelectItem(nItem1);
	}

	return TRUE;
}

// Image related
CImageList* CListCtrlEx::SetHeaderImageList(UINT nBitmapID, int nWidth, COLORREF crMask)
{
	if (m_ilHdr.m_hImageList)
		m_ilHdr.DeleteImageList();

	m_ilHdr.Create(nBitmapID, nWidth > 0 ? nWidth : 16, 4, crMask);
	return GetHeaderCtrl()->SetImageList(&m_ilHdr);
}

BOOL CListCtrlEx::SetHeaderImage(int nColumn, int nImageIndex, BOOL bLeftSide)
{
	HDITEM hi;
	::memset(&hi, 0, sizeof(HDITEM));
	hi.mask = HDI_FORMAT;
	if (!GetHeaderCtrl()->GetItem(nColumn, &hi))
		return FALSE;
	
	hi.mask |= HDI_IMAGE;		
	hi.fmt |= HDF_IMAGE;

	if (!bLeftSide)
		hi.fmt |= HDF_BITMAP_ON_RIGHT; // draw the image on right side of text

	hi.iImage = nImageIndex;
	return GetHeaderCtrl()->SetItem(nColumn, &hi);
}

CImageList* CListCtrlEx::SetImageList(UINT nBitmapID, int nWidth, COLORREF crMask)
{
	if (m_il.m_hImageList)
		m_il.DeleteImageList();

	m_il.Create(nBitmapID, nWidth > 0 ? nWidth : 16, 4, crMask);
	return CListCtrl::SetImageList(&m_il, LVSIL_SMALL);
}

BOOL CListCtrlEx::SetFieldImage(int nIndex, int nColumn, int nImageIndex)
{
	return CListCtrl::SetItem(nIndex, nColumn, LVIF_IMAGE, NULL, nImageIndex, 0, 0, 0);
}

int CListCtrlEx::FindItemByData(DWORD dwData) const
{
	for (int i = 0; i < GetItemCount(); i++)
	{
		if (GetItemData(i) == dwData)
			return i;
	}
	return -1;
}
