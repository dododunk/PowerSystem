// P9111.cpp: implementation of the CP9111 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TTT.h"
#include "DASK.H"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CP9111::CP9111()
{
	m_nCardNum = 0;
//	m_bExit = false;
//	m_bPaused = false;
//	m_pThread = NULL;
	if (( m_nCardNum= Register_Card (PCI_9111DG, 0)) < 0) 
	{
		CString error;
		error.Format("×¢²á²É¼¯¿¨´íÎó£¬´íÎóºÅ%d", m_nCardNum);
        AfxMessageBox(LPCTSTR(error));
		return;
    }
/*    I16 err = AI_9111_Config(m_nCardNum, TRIG_INT_PACER,0,1024);
    if (err != 0) 
	{
		CString error;
		error.Format("²É¼¯¿¨ÅäÖÃ´íÎó  %s",  err);
        AfxMessageBox(LPCTSTR(error));
    }*/
//	m_SampleStruct.nCardNumber = m_nCardNum;
	
}

CP9111::~CP9111()
{
    if(m_nCardNum >= 0)
	{
		
		Release_Card(m_nCardNum);
	}
}
