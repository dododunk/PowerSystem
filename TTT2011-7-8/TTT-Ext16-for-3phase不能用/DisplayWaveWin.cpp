// DisplayWaveWin.cpp : implementation file
//

#include "stdafx.h"
#include "TTT.h"
#include "DisplayWaveWin.h"
#include "Dask.h"
#include "MainFrm.h"
#include "TTTDoc.h"
#include "TTTView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CDisplayWaveWin
extern float g_GainSampleWin;
extern float g_CurrentGainSampleWin;
extern BOOL             m_TestPhase;

CDisplayWaveWin::CDisplayWaveWin()
{

	m_bIsFirst = TRUE;   
}

CDisplayWaveWin::~CDisplayWaveWin()
{

}


BEGIN_MESSAGE_MAP(CDisplayWaveWin, CStatic)
	//{{AFX_MSG_MAP(CDisplayWaveWin)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDisplayWaveWin message handlers

void CDisplayWaveWin::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
    CTTTView* pview = (CTTTView *)((CMainFrame*)AfxGetMainWnd())->GetActiveView();

	//画背景
	if(m_bIsFirst)
	{
		m_bIsFirst = FALSE;
		GetClientRect(m_rectClient);
		m_nY0 = m_rectClient.Height() / 2;
		m_nCh0CurPoints = 0; 
		m_nCh1CurPoints = 0;
		m_nCh2CurPoints = 0;
		m_nCh3CurPoints = 0; 
		m_nCh4CurPoints = 0;
		m_nCh5CurPoints = 0; 
		
	}
	
	CBrush *m_pBrushBlack       = new CBrush(RGB(0, 0, 0));
	CPen *m_pPenDarkGreen       = new CPen(PS_DOT, 0, RGB(80, 80, 80));
	CPen *m_pPenDarkGreenX      = new CPen(PS_SOLID, 1, RGB(100, 100, 100));
	CPen *m_pPenDarkGreenDouble = new CPen(PS_SOLID, 2, RGB(100, 100, 100));

	CBrush *pBrush = dc.SelectObject(m_pBrushBlack);
	dc.Rectangle(m_rectClient);
	dc.SelectObject(pBrush);

	dc.SetBkMode(TRANSPARENT);
	dc.SelectObject(m_pPenDarkGreenX);
	nHeight = m_rectClient.Height();
	nWidth = m_rectClient.Width();

	dc.MoveTo(0, m_nY0);
	dc.LineTo(nWidth, m_nY0);
    
	CPen *pPen = dc.SelectObject(m_pPenDarkGreen);

	for(int i = 1; i <= 4; i ++)
	{
		dc.MoveTo(0, m_nY0 + i * nHeight / 10);
		dc.LineTo(CPoint(nWidth, m_nY0 + i * nHeight / 10));

		dc.MoveTo(0, m_nY0 - i * nHeight / 10);
		dc.LineTo(CPoint(nWidth, m_nY0 - i * nHeight / 10));
	}

	for(i = 1; i< 16; i ++)
	{
		if(i % 4 == 0)
		{
			pPen = dc.SelectObject(m_pPenDarkGreenDouble);
		}
		else
		{
			pPen = dc.SelectObject(m_pPenDarkGreen);
		}
        
		dc.MoveTo(i*nWidth/16, 0);
		dc.LineTo(CPoint(i*nWidth/16,  nHeight));
	}
	dc.SelectObject(pPen);
    
	CPen *m_pWaveCh0Pen  = new CPen(PS_SOLID, 1, RGB(255,255,0));
	CPen *m_pWaveCh1Pen  = new CPen(PS_SOLID, 1, RGB(0,255,0));
	CPen *m_pWaveCh2Pen  = new CPen(PS_SOLID, 1, RGB(255,0,0));
	CPen *m_pWaveCh3Pen  = new CPen(PS_SOLID, 3, RGB(255,255,0));
	CPen *m_pWaveCh4Pen  = new CPen(PS_SOLID, 3, RGB(0,255,0));
	CPen *m_pWaveCh5Pen  = new CPen(PS_SOLID, 3, RGB(255,0,0));
	CPen *m_pWaveCh8Pen  = new CPen(PS_SOLID, 2, RGB(255,255,0));
	CPen *m_pWaveCh9Pen  = new CPen(PS_SOLID, 2, RGB(0,255,0));
	CPen *m_pWaveCh10Pen = new CPen(PS_SOLID, 2, RGB(255,0,0));

	if(pview->m_ShowWave)
	{
		
		//第二通道
		dc.SelectObject(m_pWaveCh1Pen);  
		dc.MoveTo(0, m_pCh1YValues[0]);
		for(UINT j = 1; j <m_nCh1CurPoints; j ++)
		{ 
			if(m_pCh1YValues[j] < 1)
				m_pCh1YValues[j] = 0;
			if(m_pCh1YValues[j] > nHeight)
				m_pCh1YValues[j] = nHeight;
			dc.LineTo(j * (pview->g_Extend), m_pCh1YValues[j]);
		}
		
	}
	else
	{
		
		//第一通道
		if(pview->m_bCh0 )
		{
			
			dc.SelectObject(m_pWaveCh0Pen);  
			dc.MoveTo(0, m_pCh0YValues[0]);
			for(UINT j = 1; j < m_nCh0CurPoints; j ++)
			{	   if(m_pCh0YValues[j] < 1)
			m_pCh0YValues[j] = 0;
			if(m_pCh0YValues[j] > nHeight)
				m_pCh0YValues[j] = nHeight;
			dc.LineTo(j * (pview->g_Extend),m_pCh0YValues[j]);
			}
			
		}
		
		//第二通道
		if(pview->m_bCh1)
		{
			
			dc.SelectObject(m_pWaveCh1Pen);  
			dc.MoveTo(0, m_pCh1YValues[0]);
			for(UINT j = 1; j <m_nCh1CurPoints; j ++)
			{ 
				if(m_pCh1YValues[j] < 1)
					m_pCh1YValues[j] = 0;
				if(m_pCh1YValues[j] > nHeight)
                    m_pCh1YValues[j] = nHeight;
				dc.LineTo(j * (pview->g_Extend), m_pCh1YValues[j]);
			}
			
		}
		
		//第三通道
		if(pview->m_bCh2)
		{
			dc.SelectObject(m_pWaveCh2Pen);  
			dc.MoveTo(0, m_pCh2YValues[0]);
			for(UINT j = 1; j <m_nCh2CurPoints; j ++)
			{
				if(m_pCh2YValues[j]<1)
					m_pCh2YValues[j]=0;
				if(m_pCh2YValues[j]>nHeight)
                    m_pCh2YValues[j]=nHeight;
				dc.LineTo(j * (pview->g_Extend), m_pCh2YValues[j]);
			}
			
		}
		
		//第四通道
		if(pview->m_bCh3)
		{
			dc.SelectObject(m_pWaveCh3Pen);  
			dc.MoveTo(0, m_pCh3YValues[0]);
			for(UINT j = 1; j <m_nCh3CurPoints; j ++)
			{
				if(m_pCh3YValues[j]<1)
					m_pCh3YValues[j]=0;
				if(m_pCh3YValues[j]>nHeight)
                    m_pCh3YValues[j]=nHeight;
				dc.LineTo(j * (pview->g_Extend), m_pCh3YValues[j]);
			}
			
		}
		
		//第五通道
		if(pview->m_bCh4)
		{
			dc.SelectObject(m_pWaveCh4Pen);  
			dc.MoveTo(0, m_pCh4YValues[0]);
			for(UINT j = 1; j <m_nCh4CurPoints; j ++)
			{
				if(m_pCh4YValues[j]<1)
					m_pCh4YValues[j]=0;
				if(m_pCh4YValues[j]>nHeight)
                    m_pCh4YValues[j]=nHeight;
				dc.LineTo(j * (pview->g_Extend), m_pCh4YValues[j]);
			}
			
		}
		
		//第六通道
		if(pview->m_bCh5)
		{
			dc.SelectObject(m_pWaveCh5Pen);  
			dc.MoveTo(0, m_pCh5YValues[0]);
			for(UINT j = 1; j <m_nCh5CurPoints; j ++)
			{
				if(m_pCh5YValues[j]<1)
					m_pCh5YValues[j]=0;
				if(m_pCh5YValues[j]>nHeight)
                    m_pCh5YValues[j]=nHeight;
				dc.LineTo(j * (pview->g_Extend), m_pCh5YValues[j]);
			}
			
		}
		
		//第八通道
		if(pview->m_bCh8)
		{
			dc.SelectObject(m_pWaveCh8Pen);  
			dc.MoveTo(0, m_pCh8YValues[0]);
			for(UINT j = 1; j <m_nCh8CurPoints; j ++)
			{
				if(m_pCh8YValues[j]<1)
					m_pCh8YValues[j]=0;
				if(m_pCh8YValues[j]>nHeight)
                    m_pCh8YValues[j]=nHeight;
				dc.LineTo(j * (pview->g_Extend), m_pCh8YValues[j]);
			}
			
		}
		
		//第九通道
		if(pview->m_bCh9)
		{
			dc.SelectObject(m_pWaveCh9Pen);  
			dc.MoveTo(0, m_pCh9YValues[0]);
			for(UINT j = 1; j <m_nCh9CurPoints; j ++)
			{
				if(m_pCh9YValues[j]<1)
					m_pCh9YValues[j]=0;
				if(m_pCh9YValues[j]>nHeight)
                    m_pCh9YValues[j]=nHeight;
				dc.LineTo(j * (pview->g_Extend), m_pCh9YValues[j]);
			}
			
		}
		
		//第十通道
		if(pview->m_bCh10)
		{
			dc.SelectObject(m_pWaveCh10Pen);  
			dc.MoveTo(0, m_pCh10YValues[0]);
			for(UINT j = 1; j <m_nCh10CurPoints; j ++)
			{
				if(m_pCh10YValues[j] < 1)
					m_pCh10YValues[j] = 0;
				if(m_pCh10YValues[j] > nHeight)
                    m_pCh10YValues[j] = nHeight;
				dc.LineTo(j * (pview->g_Extend), m_pCh10YValues[j]);
			}
			
		}
	}

    delete m_pWaveCh0Pen;
	delete m_pWaveCh1Pen;
	delete m_pWaveCh2Pen;
	delete m_pWaveCh3Pen;
	delete m_pWaveCh4Pen;
	delete m_pWaveCh5Pen;
	delete m_pWaveCh8Pen;
	delete m_pWaveCh9Pen;
	delete m_pWaveCh10Pen;
	delete m_pBrushBlack;
	delete m_pPenDarkGreen;
	delete m_pPenDarkGreenX;
	delete m_pPenDarkGreenDouble;
}

void CDisplayWaveWin::NewDataIn(unsigned short *pValue,UINT nCount)
{   

	int m_maxDecimalVal,m_DivideVal;
	
	CTTTApp * pt = (CTTTApp*)AfxGetApp();

	if(pt->m_ifcardis9111dr)
	{	
		m_maxDecimalVal = 4096;//最大值        1、PCI-9111DR 4096     2、PCI-9111HR 65536 
		m_DivideVal     =   16;//采的数要除的值1、PCI-9111DR   16     2、PCI-9111HR     1 
	}
	else
	{
		m_maxDecimalVal = 65536;//最大值        1、PCI-9111DR 4096     2、PCI-9111HR 65536 
		m_DivideVal     =     1;//采的数要除的值1、PCI-9111DR   16     2、PCI-9111HR     1 
	} 


	//比例系数
	float coe = (float)nHeight/m_maxDecimalVal;
	m_nCh0CurPoints=m_nCh1CurPoints=m_nCh2CurPoints=m_nCh3CurPoints=m_nCh4CurPoints=m_nCh5CurPoints=m_nCh8CurPoints=m_nCh9CurPoints=m_nCh10CurPoints= 0;
	  
	unsigned short    m_MinValue8,m_MinValue9,m_MinValue10;
	m_MinValue8 = m_MinValue9 = m_MinValue10 = 5000;
	unsigned short    m_MaxValue8,m_MaxValue9,m_MaxValue10;
	m_MaxValue8 = m_MaxValue9 = m_MaxValue10 = 0;

	//除16
	for(UINT i = 0; i < nCount; i++)
	{
		*(pValue+i) =   *(pValue+i)/m_DivideVal;
	}

	//找出最大值
	if(m_TestPhase)
	{
		
		//算8,9,10通道的最大值、最小值
		for(int i = 0; i < nCount; i ++)
		{
			
			if((i%16) == 8)
			{
				
				//找最小值 
				if((*(pValue+i)) < m_MinValue8)
				{
					m_MinValue8  = (*(pValue+i));
				}
				
				//找最大值 
				if((*(pValue+i)) > m_MaxValue8)
				{
					m_MaxValue8  = (*(pValue+i));
				}
				
				
			}
			else if((i%16) == 9)
			{
				
				//找最小值 
				if((*(pValue+i)) < m_MinValue9)
				{
					m_MinValue9  = (*(pValue+i));
				}	
				
				//找最大值 
				if((*(pValue+i)) > m_MaxValue9)
				{
					m_MaxValue9  = (*(pValue+i));
				}

			}
			else if((i%16) == 10)
			{	
				
				//找最小值 
				if((*(pValue+i)) < m_MinValue10)
				{
					m_MinValue10  = (*(pValue+i));
				}
				
				//找最大值 	
				if((*(pValue+i)) > m_MaxValue10)
				{
					m_MaxValue10  = (*(pValue+i));
				}

			}
			
		}
		
	}
	
	//写入文本文件
	/*	
	FILE  *text;
	CString Str;
	if((text = fopen("c:\\data.txt","a")) != NULL)
	{
		Str.Format("m_MinValue8=%d,m_MinValue9=%d,m_MinValue10=%d,m_MaxValue8=%d, m_MaxValue9=%d,m_MaxValue10=%d",m_MinValue8,m_MinValue9,m_MinValue10,m_MaxValue8,m_MaxValue9,m_MaxValue10);
		fputs(Str + "\r\n",text);
		fclose(text);
	}
	*/


//	m_MinValue8 = m_MinValue9 = m_MinValue10 =  0;
//	m_MaxValue8 = m_MaxValue9 = m_MaxValue10 = 1000;

	/*
	m_MinValue8   = m_MaxValue8/2;
	m_MinValue9   = m_MaxValue9/2;
	m_MinValue10  = m_MaxValue10/2;
	*/

	//算数据值
	for( i = 0; i < nCount; i++)
	{

		switch(i%16)
		{
		case 0:	
			{    			
				if((*(pValue + i)) < m_maxDecimalVal/2)
				{
					m_pCh0YValues[m_nCh0CurPoints] = m_nY0 - (*(pValue + i))*g_CurrentGainSampleWin*coe;
				}
				else
				{
					m_pCh0YValues[m_nCh0CurPoints] = m_nY0 + (m_maxDecimalVal-(*(pValue + i)))*g_CurrentGainSampleWin*coe;
				}

				m_nCh0CurPoints++;

				break;
			}
		case 1:
			{
				if((*(pValue + i)) < m_maxDecimalVal/2)
				{
					m_pCh1YValues[m_nCh1CurPoints] = m_nY0-(*(pValue + i))*g_CurrentGainSampleWin*coe;
				}
				else
				{
					m_pCh1YValues[m_nCh1CurPoints] = m_nY0+(m_maxDecimalVal-(*(pValue + i)))*g_CurrentGainSampleWin*coe;
				}
				
				m_nCh1CurPoints++;
				
				break;
			}
		case 2:
			{
				if((*(pValue + i)) < m_maxDecimalVal/2)
				{
					m_pCh2YValues[m_nCh2CurPoints] = m_nY0 - (*(pValue + i))*g_CurrentGainSampleWin*coe;
				}
				else
				{
					m_pCh2YValues[m_nCh2CurPoints] = m_nY0 + (m_maxDecimalVal - (*(pValue + i)))*g_CurrentGainSampleWin*coe;
				}

				m_nCh2CurPoints++;
				break;
			}
		case 3:	
			{
	
				if((*(pValue + i)) < m_maxDecimalVal/2)
				{
					m_pCh3YValues[m_nCh3CurPoints] = m_nY0 - (*(pValue + i))*g_GainSampleWin*coe;
				}
				else
				{
					m_pCh3YValues[m_nCh3CurPoints] = m_nY0 + (m_maxDecimalVal-(*(pValue + i)))*g_GainSampleWin*coe;
				}

			    m_nCh3CurPoints++;
				break;
			}
		case 4:	
			{
			
				if((*(pValue+i)) < m_maxDecimalVal/2)
				{
					m_pCh4YValues[m_nCh4CurPoints] = m_nY0 - (*(pValue+i))*g_GainSampleWin*coe;
				}
				else
				{
					m_pCh4YValues[m_nCh4CurPoints] = m_nY0 + (m_maxDecimalVal-(*(pValue+i)))*g_GainSampleWin*coe;
				}

		    	m_nCh4CurPoints++;
				break;
			}
		case 5:	
			{
				if((*(pValue + i))  < m_maxDecimalVal/2)
				{
					m_pCh5YValues[m_nCh5CurPoints] = m_nY0 - (*(pValue + i))*g_GainSampleWin*coe;
				}
				else
				{
					m_pCh5YValues[m_nCh5CurPoints] = m_nY0 + (m_maxDecimalVal- (*(pValue + i)))*g_GainSampleWin*coe;
				}

				m_nCh5CurPoints++;
				break;
			}
		case 8:
			{
				/*	
				FILE  *text;
				CString Str;
				if((text = fopen("c:\\data.txt","a")) != NULL)
				{
					Str.Format("%d",*(pValue + i));
					fputs(Str + "\r\n",text);
					fclose(text);
				}
				*/
				
				if(m_TestPhase)
				{

					if((m_MaxValue8 - m_MinValue8) > 0)
					{
						
						//如果是5V
						m_pCh8YValues[m_nCh8CurPoints]  = m_nY0 - ((*(pValue + i))  - (m_MaxValue8 + m_MinValue8)/2.00)*g_GainSampleWin*((float)nHeight/1000);
							
					}
					else
					{
						
						m_pCh8YValues[m_nCh8CurPoints]  = m_nY0 ;
					
					}

				}
				else
				{
				
					//正常10V
					if((*(pValue + i))  < m_maxDecimalVal/2)
					{
						m_pCh8YValues[m_nCh8CurPoints] = m_nY0 - (*(pValue + i))*g_GainSampleWin*coe;
					}
					else
					{
						m_pCh8YValues[m_nCh8CurPoints] = m_nY0 + (m_maxDecimalVal - (*(pValue + i)))*g_GainSampleWin*coe;
					}	
					
				}

		    	m_nCh8CurPoints++;
				break;
			}
		case 9:
			{	
				
				if(m_TestPhase)
				{
				
					//如果是5V
					if((m_MaxValue9 - m_MinValue9) > 0)
					{

						//如果是5V
						m_pCh9YValues[m_nCh9CurPoints] = m_nY0 - ((*(pValue + i))  - (m_MaxValue9 + m_MinValue9)/2.00)*g_GainSampleWin*((float)nHeight/1000);
					}
					else
					{
						
						m_pCh9YValues[m_nCh9CurPoints] = m_nY0 ;

					}

				}
				else
				{
					//正常10V
					if(*(pValue + i) < m_maxDecimalVal/2)
					{
					
						m_pCh9YValues[m_nCh9CurPoints] = m_nY0 - (*(pValue + i))*g_GainSampleWin*coe;

					}
					else
					{

						m_pCh9YValues[m_nCh9CurPoints] = m_nY0 + (m_maxDecimalVal-(*(pValue + i)))*g_GainSampleWin*coe;

					}

				}

				m_nCh9CurPoints++;
				break;
			}
		case 10:
			{	
				
				if(m_TestPhase)
				{

					//如果是5V
					if((m_MaxValue10 - m_MinValue10) > 0)
					{

						//如果是5V
						m_pCh10YValues[m_nCh10CurPoints] = m_nY0 - ((*(pValue + i))  - (m_MaxValue10 + m_MinValue10)/2.00)*g_GainSampleWin*((float)nHeight/1000);
					}
					else
					{
						m_pCh10YValues[m_nCh10CurPoints]  = m_nY0 ;
		
					}

				}
				else
				{

					//正常10V
					if(*(pValue + i) < m_maxDecimalVal/2)
					{
						m_pCh10YValues[m_nCh10CurPoints] = m_nY0 -(*(pValue + i))*g_GainSampleWin*coe;
					}
					else
					{
						m_pCh10YValues[m_nCh10CurPoints] = m_nY0 +(m_maxDecimalVal-(*(pValue + i)))*g_GainSampleWin*coe;
					}
					
				}

				m_nCh10CurPoints++;				
				break;
			}
			
		}
	}

	Invalidate();
}

void CDisplayWaveWin::NewDataInAnalyze(int *pValue, int nCount)
{
	CString   str;
    int     Value;

	int m_maxDecimalVal;
	
	CTTTApp * pt = (CTTTApp*)AfxGetApp();

	if(pt->m_ifcardis9111dr)
	{	
		m_maxDecimalVal = 4096;//最大值        1、PCI-9111DR 4096     2、PCI-9111HR 65536 
	}
	else
	{
		m_maxDecimalVal = 65536;//最大值        1、PCI-9111DR 4096     2、PCI-9111HR 65536 
	} 

	float coe=(float)nHeight/m_maxDecimalVal;
	
	for(UINT i = 0; i < nCount; i ++)
	{   
		Value = *(pValue + i);
        if(Value < m_maxDecimalVal/2)
	       m_pCh1YValues[i] = m_nY0 - Value * g_GainSampleWin * coe;
		else
		   m_pCh1YValues[i] = m_nY0 + (m_maxDecimalVal - Value) * g_GainSampleWin * coe;         	
	}

	m_nCh1CurPoints = nCount;

	Invalidate();
}

void CDisplayWaveWin::ClearAllData()
{
	memset(m_pCh0YValues,0,80000);
	memset(m_pCh1YValues,0,80000);
	memset(m_pCh2YValues,0,80000);
	memset(m_pCh3YValues,0,80000);
	memset(m_pCh4YValues,0,80000);
	memset(m_pCh5YValues,0,80000);
	memset(m_pCh8YValues,0,80000);
	memset(m_pCh9YValues,0,80000);
	memset(m_pCh10YValues,0,80000);
}
