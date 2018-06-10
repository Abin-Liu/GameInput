/////////////////////////////////////////////////////////////////////////////
// CListCtrlEx
//
// An extension ClistCtrl derived class.
//
// Abin (2012-9-15) 
/////////////////////////////////////////////////////////////////////////////

#ifndef __LISTCTRLEX_H__
#define __LISTCTRLEX_H__

#define LVEX_ITEMHEIGHT		(20) // Predefined height for list header and items
#define LVEX_GRID_INVALID	(-1) // Invalid grid coordinates
#define WM_LVEX_NOTIFY		(WM_APP + 11709) // Fixed CListCtrlEx notification message id
#define ON_LVEX_MESSAGE(x)	ON_MESSAGE(WM_LVEX_NOTIFY, x) // Fixed CListCtrlEx notification message id

enum 
{
	// Column data format, used for sort-comparison and text alignment
	LVEX_FMT_TEXT = 0,	// Regular text
	LVEX_FMT_INT,		// Signed integer/long
	LVEX_FMT_UINT,		// Unsigned integer/long
	LVEX_FMT_HEX,		// Hexadecimal unsigned long
	LVEX_FMT_DOUBLE,	// Double
	LVEX_FMT_DATETIME,	// Date-time
	LVEX_FMT_SECONDS,	// Time snippet in format of "h:mm:ss"
	LVEX_FMT_HIDDEN,	// Hidden column, column width is forced to 0 and cannot be changed by divider dragging

	// Custom messages to be sent to parent window when list events happen
	LVEX_WM_SELCHANGE,	// Item selection changed
	LVEX_WM_CLICK,		// User left-clicked inside the control
	LVEX_WM_DBLCLICK,	// User double-clicked inside the control
	LVEX_WM_RCLICK,		// User right-clicked inside the control
	LVEX_WM_SORTSTART,	// Sort started
	LVEX_WM_SORTEND,	// Sort ended
	LVEX_WM_CUSTOMDRAW,	// Custom draw
};

// Pointer of this stuct is sent to the parent window as WPARAM
typedef struct _tagLVEXNotify
{
	UINT nNotifyType;		// Notify type LVEX_WM_, see above declaration
	int nItem;				// Item index, when used for LVEX_WM_SORTSTART or LVEX_WM_SORTEND, this value is BOOL which indicates ascending/descending
	int nSubItem;			// Column index
	LPCOLORREF pClrText;	// Only valid when custom draw mode is enabled
	LPCOLORREF pClrTextBk;	// Only valid when custom draw mode is enabled
} LVEXNOTIFY, *LPLVEXNOTIFY;

class CListCtrlEx : public CListCtrl
{
public:
	
	CListCtrlEx();
	virtual ~CListCtrlEx();
	
public:		

	virtual BOOL Create(CWnd* pParentWnd, DWORD dwStyles = 0, UINT nID = 0xffff);

	// Column & sorting
	CHeaderCtrl* GetHeaderCtrl();
	const CHeaderCtrl* GetHeaderCtrl() const;

	int GetColumnCount() const;
	void SaveColumnWidth(LPCTSTR lpszSection) const;
	void LoadColumnWidth(LPCTSTR lpszSection);
	static void DeleteSavedColumnWidth(LPCTSTR lpszSection);
	int GetColumnDataType(int nColumn) const;
	int GetColumnAlignFmt(int nColumn) const;
	CString GetColumnText(int nColumn) const;
	int GetSortColumn(LPBOOL lpDescending = NULL) const;
	int InsertColumn(int nColumn, LPCTSTR lpszText, int nWidth, int nDataType = LVEX_FMT_TEXT, int nAlign = -1);
	int AddColumn(LPCTSTR lpszText, int nWidth, int nDataType = LVEX_FMT_TEXT, int nAlign = -1);
	BOOL SortItems(int nColumn, BOOL bDescending, int nDataType = LVEX_FMT_TEXT);
	void HideSortArrow();

	void SetHyperlinkColors(COLORREF cLinkColor, COLORREF cHoverColor);
	void RegisterHyperlinkUrlColumn(int nTextColumn, int nUrlColumn);
	int GetHyperlinkUrlColumn(int nTextColumn) const;
	void ClearHyperlinkUrlColumns();

	// Item operations
	int AddItem(LPCTSTR lpszText, DWORD dwData = 0);
	BOOL DeleteItem(int nIndex = -1);
	int DeleteAllSelectedItems();
	BOOL DeleteAllItems();
	int FindItemByData(DWORD dwData) const;

	int GetSelection() const;
	DWORD GetSelectedData() const;
	BOOL SelectItem(int nIndex);
	void UnselectItem(int nItem);

	BOOL SwapItems(int nItem1, int nItem2); // Swap two items

	// Custom draw	
	BOOL IsCustomDrawEnabled() const;
	void EnableCustomDraw(BOOL bEnable);

	// Column header images
	BOOL SetHeaderImage(int nColumn, int nImageIndex, BOOL bLeftSide = TRUE);
	CImageList* SetHeaderImageList(UINT nBitmapID, int nWidth = 16, COLORREF crMask = RGB(255, 0, 255));
	
	// Sub-item images
	BOOL SetFieldImage(int nIndex, int nColumn, int nImageIndex);
	CImageList* SetImageList(UINT nBitmapID, int nWidth = 16, COLORREF crMask = RGB(255, 0, 255));

	// Field data access
	BOOL IsFieldEmpty(int nIndex, int nColumn) const;

	CString GetItemText(int nIndex, int nColumn) const;
	int GetItemText(int nIndex, int nColumn, LPTSTR lpszText, int nLen) const;
	CString GetFieldText(int nIndex, int nColumn) const;
	int GetFieldText(int nIndex, int nColumn, LPTSTR lpszText, int nLen) const;
	int GetFieldInt(int nIndex, int nColumn) const;
	UINT GetFieldUInt(int nIndex, int nColumn, int nBase = 10) const;
	long GetFieldLong(int nIndex, int nColumn) const;
	DWORD GetFieldULong(int nIndex, int nColumn, int nBase = 10) const;
	double GetFieldDouble(int nIndex, int nColumn) const;
	COleDateTime GetFieldDateTime(int nIndex, int nColumn, DWORD dwFlags = 0, LCID lcid = LANG_USER_DEFAULT) const;
	COleCurrency GetFieldMoney(int nIndex, int nColumn) const;
	CString GetFieldHyperlink(int nIndex, int nColumn) const;
	int GetFieldSeconds(int nIndex, int nColumn) const;

	BOOL SetItemText(int nIndex, int nColumn, LPCTSTR lpszValue);
	BOOL SetFieldText(int nIndex, int nColumn, LPCTSTR lpszValue);
	BOOL SetFieldLong(int nIndex, int nColumn, long nValue, BOOL bEmptyIfZero = FALSE);
	BOOL SetFieldULong(int nIndex, int nColumn, DWORD dwValue, LPCTSTR lpszFormat = NULL, BOOL bEmptyIfZero = FALSE);
	BOOL SetFieldDouble(int nIndex, int nColumn, double fValue, int nPrecision, BOOL bTrim = FALSE, BOOL bEmptyIfZero = FALSE);
	BOOL SetFieldDateTime(int nIndex, int nColumn, COleDateTime dValue, DWORD dwFormat = 0);
	BOOL SetFieldHyperlink(int nIndex, int nColumn, LPCTSTR lpszHyperlink);
	BOOL SetFieldMoney(int nIndex, int nColumn, COleCurrency fMoney, BOOL bEmptyIfZero = FALSE);
	BOOL SetFieldSeconds(int nIndex, int nColumn, int nSeconds, BOOL bCanBeNegative = FALSE, BOOL bEmptyIfZero = FALSE);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListCtrlEx)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL	

	// Generated message map functions
protected:
	//{{AFX_MSG(CListCtrlEx)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:

	DWORD TestHoverLink(const CPoint& point);
	virtual void CheckItemChange();

private:

	void InitListStyles();
	BOOL InternalSort(int nColumn, BOOL bDescending, int nDataType);
	void SendNotify(UINT nNotifyType, int nItem, int nSubItem = -1, LPCOLORREF pClrText = NULL, LPCOLORREF pClrTextBk = NULL);
	static int CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

	CHeaderCtrl* m_pHeaderCtrl;
	int m_nSelection;
	DWORD m_dwSelectedData;
	BOOL m_bCustomDraw;
	BOOL m_bIsSorting;
	HCURSOR m_hHandCursor;
	HCURSOR m_hNormalCursor;
	DWORD m_dwHoverLink;
	COLORREF m_cLinkColor;
	COLORREF m_cHoverColor;
	BYTE m_aUrlMap[256];
	
	CImageList m_il;
	CImageList m_ilHdr; // Image list for the header control
};

#endif // __LISTCTRLEX_H__
