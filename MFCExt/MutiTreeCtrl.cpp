// MutiTreeCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "MutiTreeCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CMutiTreeCtrl

CMultiTreeCtrl::CMultiTreeCtrl()
{
	m_uFlags=0;
}

CMultiTreeCtrl::~CMultiTreeCtrl()
{
}


BEGIN_MESSAGE_MAP(CMultiTreeCtrl, CTreeCtrl)
	//{{AFX_MSG_MAP(CMutiTreeCtrl)
	ON_WM_LBUTTONDOWN()
	ON_NOTIFY_REFLECT(NM_CLICK, OnStateIconClick)
	ON_NOTIFY_REFLECT(TVN_KEYDOWN, OnKeydown)
	ON_WM_KEYDOWN()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMutiTreeCtrl message handlers

void CMultiTreeCtrl::OnStateIconClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if(m_uFlags&TVHT_ONITEMSTATEICON) *pResult=1;
	else *pResult = 0;
}

void CMultiTreeCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	HTREEITEM hItem =HitTest(point, &m_uFlags);
	if ( (m_uFlags&TVHT_ONITEMSTATEICON ))
	{
		//nState: 0->无选择钮 1->没有选择 2->部分选择 3->全部选择
		UINT nState = GetItemState( hItem, TVIS_STATEIMAGEMASK ) >> 12;
		nState=(nState==3)?1:3;
		SetItemState( hItem, INDEXTOSTATEIMAGEMASK(nState), TVIS_STATEIMAGEMASK );
	}
	
	CTreeCtrl::OnLButtonDown(nFlags, point);
}

void CMultiTreeCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
 	//处理空格键
 	if(nChar == 0x20)
 	{
 		HTREEITEM hItem = GetSelectedItem();
 		UINT nState = GetItemState( hItem, TVIS_STATEIMAGEMASK ) >> 12;
 		if(nState != 0)
 		{
 			nState=(nState==3)?1:3;
 			SetItemState( hItem, INDEXTOSTATEIMAGEMASK(nState), TVIS_STATEIMAGEMASK );
 		}
 	}
	else CTreeCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CMultiTreeCtrl::OnKeydown(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TV_KEYDOWN* pTVKeyDown = (TV_KEYDOWN*)pNMHDR;
	
	*pResult = 0;
}

BOOL CMultiTreeCtrl::SetItemState(HTREEITEM hItem, UINT nState, UINT nStateMask, BOOL bSearch)
{
	BOOL bReturn=CTreeCtrl::SetItemState( hItem, nState, nStateMask );

	UINT iState = nState >> 12;
	if(iState!=0)
	{
		if(bSearch) TravelChild(hItem, iState);
		TravelSiblingAndParent(hItem,iState);
	}
	return bReturn;
}

void CMultiTreeCtrl::TravelChild(HTREEITEM hItem, int nState)
{
	HTREEITEM hChildItem,hBrotherItem;
	
	//查找子节点，没有就结束
	hChildItem = GetChildItem(hItem);
	if(hChildItem != NULL)
	{
		//设置子节点的状态与当前节点的状态一致
		CTreeCtrl::SetItemState( hChildItem, INDEXTOSTATEIMAGEMASK(nState), TVIS_STATEIMAGEMASK );
		//再递归处理子节点的子节点和兄弟节点
		TravelChild(hChildItem, nState);
		
		//处理子节点的兄弟节点和其子节点
		hBrotherItem = GetNextSiblingItem(hChildItem);
		while (hBrotherItem)
		{
			//设置子节点的兄弟节点状态与当前节点的状态一致
			int nState1 = GetItemState( hBrotherItem, TVIS_STATEIMAGEMASK ) >> 12;
			if(nState1 != 0)
			{
				CTreeCtrl::SetItemState( hBrotherItem, INDEXTOSTATEIMAGEMASK(nState), TVIS_STATEIMAGEMASK );
			}
			//再递归处理子节点的兄弟节点的子节点和兄弟节点
			TravelChild(hBrotherItem, nState);
			hBrotherItem = GetNextSiblingItem(hBrotherItem);
		} 

	}

}

void CMultiTreeCtrl::TravelSiblingAndParent(HTREEITEM hItem, int nState)
{
	HTREEITEM hNextSiblingItem,hPrevSiblingItem,hParentItem;
	
	//查找父节点，没有就结束
	hParentItem=GetParentItem(hItem);
	if(hParentItem!=NULL)
	{
		int nState1=nState;//设初始值，防止没有兄弟节点时出错
		
		//查找当前节点下面的兄弟节点的状态
		hNextSiblingItem=GetNextSiblingItem(hItem);
		while(hNextSiblingItem != NULL)
		{
			nState1 = GetItemState( hNextSiblingItem, TVIS_STATEIMAGEMASK ) >> 12;
			if(nState1!=nState && nState1 != 0) 
				break;
			else
				hNextSiblingItem=GetNextSiblingItem(hNextSiblingItem);
		}
		
		if(nState1 == nState)
		{
			//查找当前节点上面的兄弟节点的状态
			hPrevSiblingItem = GetPrevSiblingItem(hItem);
			while(hPrevSiblingItem != NULL)
			{
				nState1 = GetItemState( hPrevSiblingItem, TVIS_STATEIMAGEMASK ) >> 12;
				if(nState1 != nState && nState1!=0)
					break;
				else
					hPrevSiblingItem = GetPrevSiblingItem(hPrevSiblingItem);
			}
		}
		
		if(nState1 == nState || nState1 == 0)
		{
			nState1 = GetItemState( hParentItem, TVIS_STATEIMAGEMASK ) >> 12;
			if(nState1 != 0)
			{
				//如果状态一致，则父节点的状态与当前节点的状态一致
				CTreeCtrl::SetItemState( hParentItem, INDEXTOSTATEIMAGEMASK(nState), TVIS_STATEIMAGEMASK );
			}
			//再递归处理父节点的兄弟节点和其父节点
			TravelSiblingAndParent(hParentItem,nState);
		}
		else
		{
			//状态不一致，则当前节点的父节点、父节点的父节点……状态均为第三态
			hParentItem=GetParentItem(hItem);
			while(hParentItem!=NULL)
			{
				nState1 = GetItemState( hParentItem, TVIS_STATEIMAGEMASK ) >> 12;
				if(nState1!=0)
				{
					CTreeCtrl::SetItemState( hParentItem, INDEXTOSTATEIMAGEMASK(2), TVIS_STATEIMAGEMASK );
				}
				hParentItem = GetParentItem(hParentItem);
			}
		}

	}
	
}

BOOL CMultiTreeCtrl::OnNotify( WPARAM wParam, LPARAM lParam, LRESULT* pResult )
{
	BOOL bRes = CTreeCtrl::OnNotify(wParam, lParam, pResult);

	NMHDR* pNMHDR = (NMHDR*)lParam;
	ASSERT(pNMHDR != NULL);

	if (pNMHDR && pNMHDR->code == TTN_SHOW && GetToolTips() != NULL)
	{
		GetToolTips()->SetWindowPos(&wndTop, -1, -1, -1, -1, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE);
	}

	return bRes;
}



