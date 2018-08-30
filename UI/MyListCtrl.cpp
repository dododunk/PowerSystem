// MyListCtrl.cpp : implementation file
//

#include "stdafx.h"
//#include "manager.h"
#include "MyListCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////
// CDataListCtrl

// 构建函数
CDataListCtrl::CDataListCtrl()
{
}

// 构析函数
CDataListCtrl::~CDataListCtrl()
{
}

BEGIN_MESSAGE_MAP(CDataListCtrl, CListCtrl)
   //{{AFX_MSG_MAP(CDataListCtrl)
	//}}AFX_MSG_MAP

#ifdef CMyListCtrl_SORTMODE
   ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnclick)
#endif

END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////
// CDataListCtrl helper functions

// 所选行是否存在
BOOL CDataListCtrl::IsItem(int nItem) const
{
   return GetItemCount() > nItem;
}

//向列表框中添加列
BOOL CDataListCtrl::AddColumn(LPCTSTR strItem,int nItem,int nSubItem,int nMask,int nFmt)
{
	LV_COLUMN lvc;
	lvc.mask = nMask;
	lvc.fmt = nFmt;
	lvc.pszText = (LPTSTR) strItem;
	lvc.cx = GetStringWidth(lvc.pszText) + 65;
	if(nMask & LVCF_SUBITEM){
		if(nSubItem != -1)
			lvc.iSubItem = nSubItem;
		else
			lvc.iSubItem = nItem;
	}
	return InsertColumn(nItem,&lvc);
}

//向列表框中添加行
BOOL CDataListCtrl::AddItem(int nItem,int nSubItem,LPCTSTR strItem,int nImageIndex)
{
	LV_ITEM lvItem;
	lvItem.mask = LVIF_TEXT;
	lvItem.iItem = nItem;
	lvItem.iSubItem = nSubItem;
	lvItem.pszText = (LPTSTR) strItem;
//	lvItem.Height=20;
	if(nImageIndex != -1){
		lvItem.mask |= LVIF_IMAGE;
		lvItem.iImage |= LVIF_IMAGE;
	}
	if(nSubItem == 0)
		return InsertItem(&lvItem);
	return SetItem(&lvItem);
}

// 所选列是否存在
BOOL CDataListCtrl::IsColumn(int nCol) const
{
   LV_COLUMN lvc;
   memset(&lvc, 0, sizeof(lvc));
   lvc.mask = LVCF_WIDTH;
   return GetColumn(nCol, &lvc);
}

// 返回所选行
int CDataListCtrl::GetSelectedItem(int nStartItem /* = -1 */ ) const
{
   return GetNextItem(nStartItem, LVNI_SELECTED);
}

// 选择指定的行
BOOL CDataListCtrl::SelectItem(int nItem) 
{
   return SetItemState(nItem, LVIS_SELECTED, LVIS_SELECTED);
}

// 选择列表框中的所有行
BOOL CDataListCtrl::SelectAll()
{
   BOOL bReturn(TRUE);

   for (int nItem = 0; IsItem(nItem); nItem++) 
      if (! SetItemState(nItem, LVIS_SELECTED, LVIS_SELECTED)) {
         bReturn = FALSE;
         break;
      }

   return bReturn;
}


// 重载该函数以将所选行的整行高亮显示.
void CDataListCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
   // 取得显示设备描述表指针
   CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
 
   // 设置标志
   UINT uiFlags(ILD_TRANSPARENT);

   // 检查该行是否被选择
   if (lpDrawItemStruct->itemState & ODS_SELECTED) 
   {
	  //如果被被选择则将文字和背景的颜色设为高亮显示时的颜色
      pDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
      pDC->SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));
      uiFlags |= ILD_BLEND50;
   }
   else 
   {
	  //否则将将文字和背景的颜色设为正常颜色
      pDC->SetTextColor(::GetSysColor(COLOR_WINDOWTEXT));
      pDC->SetBkColor(::GetSysColor(COLOR_WINDOW));
   }

   // 得到活动图形列表指针
   CImageList* plistImages = GetImageList(LVSIL_SMALL);

   // 得到将高亮显示的行
   LV_ITEM lvi;
   memset(&lvi, 0, sizeof(&lvi));
   lvi.mask = LVIF_IMAGE | LVIF_STATE;
   lvi.iItem = lpDrawItemStruct->itemID;
   GetItem(&lvi);

   // 绘制所选行的图形列表
   if (plistImages) {
      CPoint ptAt(lpDrawItemStruct->rcItem.left,
         lpDrawItemStruct->rcItem.top);
	  if ( ! plistImages->Draw(pDC, 0/*lvi.iImage*/, ptAt, uiFlags) ) {
		  int x = 0;
		  x++;
	  }
   }

   // 创建用于绘制表格线的画笔
   CPen pen(PS_SOLID, 0, ::GetSysColor(COLOR_WINDOWTEXT));
   CPen* penOld = pDC->SelectObject(&pen);

   char szText[256];     // 设置文本长度,如果文本长度较大,可以增加该数组的长度
   LV_COLUMN lvc;
   memset(&lvc, 0, sizeof(lvc));
   lvc.mask = LVCF_WIDTH;

   for (int nColumn = 0; GetColumn(nColumn, &lvc); nColumn++) 
   {
      CRect rTextClip;

      // 如果是画第一列
      if (0 == nColumn) 
	  {
		 //画第一列时如果有图形列表则将绘制文本的矩形右移以空出绘制图形的空间
         rTextClip.left   = lpDrawItemStruct->rcItem.left +
            (plistImages ? 16 : 0);
         rTextClip.top    = lpDrawItemStruct->rcItem.top;
         rTextClip.right  = lpDrawItemStruct->rcItem.left + lvc.cx;
         rTextClip.bottom = lpDrawItemStruct->rcItem.bottom;
      }
      else 
	  {
         // 如果不是第一列则将文本矩形右移至上一次文本矩形的右侧
         rTextClip.left  = rTextClip.right;
         rTextClip.right = rTextClip.left + lvc.cx;
      }

      // 获得文本
      lvi.iItem = lpDrawItemStruct->itemID;
      lvi.mask = LVIF_TEXT;
      lvi.iSubItem = nColumn;
      lvi.pszText = szText;
      lvi.cchTextMax = sizeof(szText);
      GetItem(&lvi);

      // 得到文本长度
      int nTextCount(lstrlen(lvi.pszText));

	  //绘制文本
      CSize sizText(pDC->GetOutputTextExtent(lvi.pszText,
         nTextCount));

      //使文本矩形略小一些以使列间出现分隔,以免如果文本较长而造成列间文本连接起来
      rTextClip.right -= 4;

	  //如果文本宽度大于绘制矩形的宽度
      if (sizText.cx >= rTextClip.Width()) 
	  {

         // 获得...的长度
         CSize sizEllipse = pDC->GetOutputTextExtent("...", 3);

         // 制做较短的文本
         while (sizText.cx+sizEllipse.cx > (rTextClip.Width())  &&
           nTextCount > 1) 
		 {
            lvi.pszText[--nTextCount] = 0;
            sizText = pDC->GetOutputTextExtent(lvi.pszText,
               nTextCount);
         }

         // 向文本后添加 "...".
         lvi.pszText[nTextCount] = '.';
         lvi.pszText[nTextCount + 1] = '.';
         lvi.pszText[nTextCount + 2] = '.';
         lvi.pszText[nTextCount + 3] = 0;
      }

      // 恢复整个矩形
      rTextClip.right += 4;

      // 绘制文本
     pDC->ExtTextOut(rTextClip.left + 2, rTextClip.top-1,
       ETO_CLIPPED | ETO_OPAQUE, &rTextClip, lvi.pszText,
       lstrlen(lvi.pszText), NULL);


      //绘制表格线
//      pDC->MoveTo(rTextClip.left+1, rTextClip.bottom-1);
//      pDC->LineTo(rTextClip.right-1, rTextClip.bottom-1);
//      pDC->MoveTo(rTextClip.right-1, rTextClip.bottom-1);
//      pDC->LineTo(rTextClip.right-1, rTextClip.top-1);
   }

   // 重设颜色
   if (lpDrawItemStruct->itemState & ODS_SELECTED) 
   {
      pDC->SetTextColor(::GetSysColor(COLOR_WINDOWTEXT));
      pDC->SetBkColor(::GetSysColor(COLOR_WINDOW));
   }

   // 如果该行被选则绘制选择矩形
   if (lpDrawItemStruct->itemState & ODS_FOCUS) 
   {
      CRect rTextClip(lpDrawItemStruct->rcItem);
      rTextClip.left += (plistImages ? 16 : 0);
      pDC->DrawFocusRect(&rTextClip);
   }

   // 恢复原有画笔
   pDC->SelectObject(penOld);
}


