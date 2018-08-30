// DisplayAnalyzeWin.cpp : implementation file
//

#include "stdafx.h"
#include "TTT.h"
#include "DisplayAnalyzeWin.h"
#include "MainFrm.h"
#include "TTTDoc.h"
#include "TTTView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CDisplayAnalyzeWin

CDisplayAnalyzeWin::CDisplayAnalyzeWin()
{
	m_bIsFirst = TRUE;
}

CDisplayAnalyzeWin::~CDisplayAnalyzeWin()
{
}


BEGIN_MESSAGE_MAP(CDisplayAnalyzeWin, CStatic)
	//{{AFX_MSG_MAP(CDisplayAnalyzeWin)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDisplayAnalyzeWin message handlers

void CDisplayAnalyzeWin::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CTTTView* pview = (CTTTView *)((CMainFrame*)AfxGetMainWnd())->GetActiveView();

	if(m_bIsFirst)
	{
		m_bIsFirst = FALSE;
		GetClientRect(m_rectClient);
		m_nY0           = m_rectClient.Height() / 2;
		m_nCycleNum     = 1;
    	m_nCh1CurPoints = 0;
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
    nHeight = m_rectClient.Height(), nWidth = m_rectClient.Width();
	dc.MoveTo(0, m_nY0);
	dc.LineTo(nWidth, m_nY0);
	
    CPen *pPen = dc.SelectObject(m_pPenDarkGreen);
	
	//画8根线
	for(int i = 1; i <= 4; i ++)
	{
		dc.MoveTo(0, m_nY0 + i * nHeight/10);
		dc.LineTo(CPoint(nWidth, m_nY0 + i * nHeight/10));
		
		dc.MoveTo(0, m_nY0 - i * nHeight/10);
		dc.LineTo(CPoint(nWidth, m_nY0 - i * nHeight/10));
	}
	
	//16根坚线
	for(i = 1; i < 16; i ++)
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
		dc.LineTo(CPoint(i*nWidth/16,nHeight));
	}
	dc.SelectObject(pPen);
    
	delete m_pBrushBlack;
	delete m_pPenDarkGreen;
    delete m_pPenDarkGreenX;
    delete m_pPenDarkGreenDouble;
	
	CPen *m_pWaveCh0Pen = new CPen(PS_SOLID, 1, RGB(255,255,0));
	CPen *m_pWaveCh1Pen = new CPen(PS_SOLID, 1, RGB(0,255,0));
	CPen *m_pWaveCh2Pen = new CPen(PS_SOLID, 1, RGB(255,0,0));
	CPen *m_pWaveCh3Pen = new CPen(PS_SOLID, 1, RGB(255,255,255));
	CPen *m_pWaveCh4Pen = new CPen(PS_SOLID, 1, RGB(0,255,255));
    CPen *m_pWaveCh5Pen = new CPen(PS_SOLID, 1, RGB(255,0,255));

	//画叠加线
	if(pview->m_bDiff2)
	{
		
		dc.SelectObject(m_pWaveCh2Pen);  
		dc.MoveTo(0, m_Splice[0]);
		
		for(UINT j = 0; j < m_nCh1CurPoints; j ++)
		{

			if(m_Splice[j] < 0)
			{
				m_Splice[j] = 0;
			}

			if(m_Splice[j] > nHeight)
			{
				m_Splice[j] = nHeight;
			}

			dc.LineTo(int(j * (pview->g_Extend)), m_Splice[j]);
		
		}

	}	
	
	//画所有向上向下叠加线
	if(pview->m_AllAdd)
	{
		
		dc.SelectObject(m_pWaveCh4Pen);
		
		if(m_SpliceUp[0] < 0)
		{
			m_SpliceUp[0] = 0;
		}
		
		dc.MoveTo(0, nHeight/2);
		
		for(UINT j = 0; j < m_nCh1CurPoints; j ++)
		{

			if(m_SpliceUp[j] < 0)
			{
				m_SpliceUp[j] = 0;
			}

			/*
			if(j < (m_nCh1CurPoints - pview->PointsNum/2))
			{
				m_SpliceUp[j] = nHeight/2;
			}
			
			if(m_SpliceUp[j] == 0)
			{
                 m_SpliceUp[j] = nHeight/2;
			}
			*/

			if(m_SpliceUp[j] > nHeight)
			{
				m_SpliceUp[j] = nHeight;
			}

			if(j <= m_nCh1CurPoints*3/8 || j >= m_nCh1CurPoints/2)
			{
				m_SpliceUp[j] = nHeight/2;
			}

			dc.LineTo(int(j * (pview->g_Extend)), m_SpliceUp[j]);
		
		}
		
		
		dc.SelectObject(m_pWaveCh5Pen); 
		
		
		if(m_SpliceDown[0] < 0)
		{
			m_SpliceDown[0] = 0;
		}
		
		dc.MoveTo(0, nHeight/2);
		
		for( j = 0; j < m_nCh1CurPoints; j ++)
		{

			if(m_SpliceDown[j] < 0)
			{
				m_SpliceDown[j] = 0;
			}

	        /*
			if(m_SpliceDown[j] == 0)
			{
                 m_SpliceDown[j] = nHeight/2;
			}
			
			if(j < (m_nCh1CurPoints - pview->PointsNum/2))
			{
				m_SpliceDown[j] = nHeight/2;
			}
			*/

			if(m_SpliceDown[j] > nHeight)
			{
				m_SpliceDown[j] = nHeight;
			}

	        if(j <= m_nCh1CurPoints*3/8 || j >= m_nCh1CurPoints/2)
			{
				m_SpliceDown[j] = nHeight/2;
			}

			dc.LineTo(int(j * (pview->g_Extend)), m_SpliceDown[j]);
		
		}
		

	}
	
	
	//匹配波
	if(pview->m_bDiff3)
	{

     	dc.SelectObject(m_pWaveCh3Pen);  
		dc.MoveTo(0, m_PiPaiWave[0]);
		
		for(UINT j = 0; j < m_nCh1CurPoints; j ++)//m_nCh1CurPoints/2
		{
			if(m_PiPaiWave[j] < 0)
				m_PiPaiWave[j] = 0;
			if(m_PiPaiWave[j] > nHeight)
				m_PiPaiWave[j] = nHeight;
			dc.LineTo(int(j * (pview->g_Extend)), m_PiPaiWave[j]);
		}
		
		//拟合线
		dc.SelectObject(m_pWaveCh0Pen);  

		if(m_niheWave[0] < 0)
		{
			m_niheWave[0] = 0;
		}
		else if(m_niheWave[0] > nHeight)
		{
			m_niheWave[0] = nHeight;
		}

		dc.MoveTo(int(3*(pview->PointsNum)/2*(pview->g_Extend)),m_niheWave[0]);
		
		for( j = 3*(pview->PointsNum)/2; j < 2*(pview->PointsNum); j ++)
		{
			if(m_niheWave[j-3*(pview->PointsNum)/2] < 0)
				m_niheWave[j - 3*(pview->PointsNum)/2] = 0;
			if(m_niheWave[j - 3*(pview->PointsNum)/2] > nHeight)
				m_niheWave[j-  3*(pview->PointsNum)/2] = nHeight;
			dc.LineTo(int(j * (pview->g_Extend)), m_niheWave[j-3*(pview->PointsNum)/2]);
		}
		
	}
	
	//数据图
    dc.SelectObject(m_pWaveCh1Pen);  
    dc.MoveTo(0, m_pCh1YValues[0]);

    for(UINT j = 0; j < m_nCh1CurPoints; j ++)
    {
	   if(m_pCh1YValues[j] < 0)
		   m_pCh1YValues[j] = 0;
       if(m_pCh1YValues[j] > nHeight)
		   m_pCh1YValues[j] = nHeight;
	   dc.LineTo(int(j * (pview->g_Extend)), m_pCh1YValues[j]);
	   
    }
   
    dc.SelectStockObject(BLACK_PEN);
    
    delete m_pWaveCh0Pen;
    delete m_pWaveCh1Pen;
    delete m_pWaveCh2Pen;
	delete m_pWaveCh3Pen;
	delete m_pWaveCh4Pen;
	delete m_pWaveCh5Pen;
 
}

void CDisplayAnalyzeWin::NewDataIn(int *pValue, UINT nCount)
{   
		
	CString         str;
	int               p;
	int               j;	
	float          temp;
	int m_maxDecimalVal;
	long m_sums   =   0;

	memset(m_niheWave,0,80000);//拟合曲线
	memset(m_temp,0,80000);

	CTTTApp * pt = (CTTTApp*)AfxGetApp();

	if(pt->m_ifcardis9111dr)
	{	
		m_maxDecimalVal = 4096;//最大值        1、PCI-9111DR 4096     2、PCI-9111HR 65536 
	}
	else
	{
		m_maxDecimalVal = 65536;//最大值        1、PCI-9111DR 4096     2、PCI-9111HR 65536 
	} 

    CTTTView* pview = (CTTTView *)((CMainFrame*)AfxGetMainWnd())->GetActiveView();

	int  FirstWaveValue[5000],CurWaveValue[5000],Value[80000];
	int SecondWaveValue[5000],CurWave2Value[5000];

	float coe = (float)nHeight/m_maxDecimalVal;
	
	//从起始点开始算		
	for(UINT i = 0;i < nCount; i ++)
	{
		Value[i] = *(pValue + i);
	}
	
	    
	for(i = 0;i < nCount/(pview->PointsNum);i ++)
	{
		
		for(  j = 0; j < (pview->PointsNum); j ++)
		{
			m_pCh1YValues[i*(pview->PointsNum)+j] = m_nY0;
		}
		
	}


	//流差
	if(pview->m_bDiffI)
	{

        for(i = 0;i < nCount/(pview->PointsNum); i ++)
		{
			
			p = i%4;
			
			//512个点运算一次
			for( j = 0;j < (pview->PointsNum);j ++) 
			{
				
     			switch(p)
				{
				case 0:
					{	
						//第1个赋为中间线值
						if(Value[i*(pview->PointsNum)+j] < m_maxDecimalVal/2)
						{
							FirstWaveValue[j] = Value[i*(pview->PointsNum)+j];
						}
						else
						{
							FirstWaveValue[j] = -(m_maxDecimalVal-Value[i*(pview->PointsNum)+j]);         	
						}
						break;
					}
				case 1:
					{	
						//第2个赋为中间线值
						if(Value[i*(pview->PointsNum)+j] < m_maxDecimalVal/2)
						{
							SecondWaveValue[j] = Value[i*(pview->PointsNum)+j];
						}
						else
						{
							SecondWaveValue[j] = -(m_maxDecimalVal-Value[i*(pview->PointsNum)+j]);         	
						}
						break;
					}
				case 2:
					{
						//数据3－1
						if(Value[i*(pview->PointsNum)+j] < m_maxDecimalVal/2)
						{
							CurWaveValue[j] = Value[i*(pview->PointsNum)+j];
						}
						else
						{
							CurWaveValue[j] = -(m_maxDecimalVal-Value[i*(pview->PointsNum)+j]); 
						}
					
						m_pCh1YValues[i*(pview->PointsNum)+j] = (CurWaveValue[j] - FirstWaveValue[j])*(pview->g_Gain);
					    break;
					}
				case 3:
					{
						//数据4－2
						if(Value[i * (pview->PointsNum) + j] < m_maxDecimalVal/2)
						{
							CurWave2Value[j] = Value[i * (pview->PointsNum) + j];
						}
						else
						{
							CurWave2Value[j] = -(m_maxDecimalVal - Value[i*(pview->PointsNum)+j]); 
						}
						
						m_pCh1YValues[i*(pview->PointsNum)+j]  = (CurWave2Value[j]-SecondWaveValue[j])* (pview->g_Gain);
	                	break;
					}

				}
				
			}
			
			
			//拟合线
			if((p + 1)%4 == 0)
			{

				
				for( j = 0;j < (pview->PointsNum)/2;j ++) 
				{					
					//叠加数据
					m_temp[j] = int(double(m_pCh1YValues[i*(pview->PointsNum)+j]  + m_pCh1YValues[i*(pview->PointsNum)+j + (pview->PointsNum)/2] + m_pCh1YValues[i*(pview->PointsNum)+j + (pview->PointsNum)] + m_pCh1YValues[i*(pview->PointsNum)+j+ (3*(pview->PointsNum))/2])/(pview->g_Gain));
				}
						
				
				for(int  kkkkk = 0;kkkkk < (pview->PointsNum)/2;kkkkk ++)
				{
					
					m_niheWave[kkkkk] = 0;

					for( j = 0;j < (pview->PointsNum)/2;j ++)
					{

						if(j + kkkkk < (pview->PointsNum)/2)
						{
							m_niheWave[kkkkk] = m_niheWave[kkkkk] + m_temp[j]*pview->m_ppwave[j + kkkkk];
						}
						else
						{			
							m_niheWave[kkkkk] = m_niheWave[ kkkkk] + m_temp[j]*pview->m_ppwave[j + kkkkk -(pview->PointsNum)/2];
						}
					
					} 
                    
					m_niheWave[kkkkk] = int(m_nY0- m_niheWave[kkkkk] * coe/((pview->PointsNum)/2));

				}
				
				
			}
		

			
			//去直流
			if(pview->m_qzhikiu && p > 1)
			{	
				
				m_sums  = 0;
				
				for(int k = 0;k < (pview->PointsNum)/2; k++)
				{
					m_sums += m_pCh1YValues[i*(pview->PointsNum) + k];
				}
				
				for(j = 0;j < (pview->PointsNum)/2; j++)
				{
					m_pCh1YValues[i*(pview->PointsNum)+j] = m_pCh1YValues[i*(pview->PointsNum)+j] - int(m_sums/((pview->PointsNum)/2));
				}
				
				m_sums  = 0;

				for(k = (pview->PointsNum)/2;k < (pview->PointsNum); k++)
				{
					m_sums += m_pCh1YValues[i*(pview->PointsNum) + k];
				}
			
				for(j = (pview->PointsNum)/2;j < (pview->PointsNum); j++)
				{
					m_pCh1YValues[i*(pview->PointsNum)+j] = m_pCh1YValues[i*(pview->PointsNum)+j] - int(m_sums/((pview->PointsNum)/2));
				}

			}
					
			//前八
			if(pview->m_bAver4)
			{
			
				for(j = 0;j < (pview->PointsNum) - 8; j++)
				{
					m_sums = 0;

     				for(BYTE k = 1;k < 8; k++)
					{
						m_sums += m_pCh1YValues[i*(pview->PointsNum)+j+k];
					}
								
					m_pCh1YValues[i*(pview->PointsNum)+j] = m_sums/8;
				
				}

			}
			
				
			//化成图形数组,512个点运算一次
			for( j = 0;j < (pview->PointsNum);j ++) 
			{
				
				m_Splice[i *(pview->PointsNum)   + j]       = m_nY0;
				m_PiPaiWave[i *(pview->PointsNum)+ j]       = m_nY0;

				switch(p)
				{
				case 0:
					{	
						//第1个赋为中间线值
						m_pCh1YValues[i*(pview->PointsNum)+j] = m_nY0;
						break;
					}
				case 1:
					{	
						//第2个赋为中间线值
						m_pCh1YValues[i*(pview->PointsNum)+j] = m_nY0;
					    break;
					}
				case 2:
					{
						//数据3－1
						m_pCh1YValues[i*(pview->PointsNum)+j] = int(m_nY0- m_pCh1YValues[i*(pview->PointsNum)+j]*coe);
					    break;
					}
				case 3:
					{
						//数据4－2
						m_pCh1YValues[i*(pview->PointsNum)+j]  = int(m_nY0- m_pCh1YValues[i*(pview->PointsNum)+j]*coe);
	                    
						if( j > (pview->PointsNum)/2)
						{
							//叠加数组显示水平线
							if(pview->m_AllAdd)
							{	
								m_SpliceUp[(i - 2)*(pview->PointsNum) + j]        = int(m_nY0- pview->m_ppAllWave[j - pview->PointsNum/2] * coe * pview->m_alltimes );
								m_SpliceDown[(i - 2)*(pview->PointsNum) + j]      = int(m_nY0- pview->m_ppAllWave[j] * coe * pview->m_alltimes);
							}
						
							//叠加波
							m_Splice[(i - 2)*(pview->PointsNum)    + j]           = m_pCh1YValues[i*(pview->PointsNum)+j]  + m_pCh1YValues[i*(pview->PointsNum)+j - (pview->PointsNum)/2] + m_pCh1YValues[i*(pview->PointsNum)+j - (pview->PointsNum)] + m_pCh1YValues[i*(pview->PointsNum)+j-(3*(pview->PointsNum))/2] - 3*m_nY0;
							//匹配波
							m_PiPaiWave[(i - 2)*(pview->PointsNum) + j]           = int(m_nY0- pview->m_ppwave[j - (pview->PointsNum)/2] * coe);
							//拟合曲线
							m_niheWave[(i - 2)*(pview->PointsNum)  + j]           = int(m_nY0- m_niheWave[j - (pview->PointsNum)/2] * coe);
						
						}

						break;

					}

				}
				
			}

			//带通
			if(pview->m_bBandPass)
			{
				temp = float(pview->BandPassAngle/90.0);
				
				int a=(int)(temp*((pview->PointsNum)/2));
				
				for(j = 0 ; j < ((pview->PointsNum)/2) - a; j ++)
				{
					m_pCh1YValues[i*(pview->PointsNum)+j] = m_nY0;
				}
				
				for(j = (pview->PointsNum)/2; j < (pview->PointsNum)/2 + ((pview->PointsNum)/2 - a); j ++)
				{
					m_pCh1YValues[i*(pview->PointsNum)+j] = m_nY0;
				}

			}
			
		}

	}
	
    m_nCh1CurPoints = nCount;
	Invalidate();
}


