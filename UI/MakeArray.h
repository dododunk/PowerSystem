// MakeArray.h: interface for the CMakeArray class.
//
//////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// 
//                         创建一维、二维、三维和四维数组
//  --------------------------------------------------------------------
//
//  Head File Name:      Matrix.h
//                       
//  Written by:          胡高明
//  eidt by :            胡高明
//
//  Date of Beginning:   15:10 October 5 , 2001
//  Date of Revising:    15:30 Decomber 19,2001
//  Last Version:       
//
////////////////////////////////////////////////////////////////////////
#if !defined(AFX_MAKEARRAY_H__76B11BCA_2B2B_4176_9E7A_723F85268B84__INCLUDED_)
#define AFX_MAKEARRAY_H__76B11BCA_2B2B_4176_9E7A_723F85268B84__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

template <class T> class CMakeArray
{
public:
	CMakeArray(){};
public:
	T* MakeOneArray(int nDim1);
	void DelOneArray(T* pT);

	T** MakeTwoArray(int nDim1,int nDim2);
	void DelTwoArray(T** ppT, int nDim1);

	T*** MakeThreeArray(int nDim1, int nDim2, int nDim3);
	void DelThreeArray(T*** pppT,int nDim1, int nDim2);

	T**** MakeFourArray(int nDim1, int nDim2, int nDim3, int nDim4);
	void DelFourArray(T**** pppppT, int nDim1, int nDim2, int nDim3);
};

template <class T>
T* CMakeArray<T>::MakeOneArray(int nDim1)
{
	T* pT = new T[nDim1];
    return pT;
}

template <class T>
void CMakeArray<T>::DelOneArray(T* pT)
{
	delete[] pT;
}

template <class T>
T** CMakeArray<T>::MakeTwoArray(int nDim1,int nDim2)
{
	T** ppT = new T* [nDim1];

    for ( int i = 0; i < nDim1; i++ ) 
		ppT[i] = MakeOneArray(nDim2);
    
	return ppT;
}

template <class T>	
void CMakeArray<T>::DelTwoArray(T** ppT,int nDim1)
{
	for (int i = 0; i < nDim1; i++ )	
		DelOneArray(ppT[i]);

	delete[] ppT;
}

template <class T>
T*** CMakeArray<T>::MakeThreeArray(int nDim1, int nDim2, int nDim3)
{
    T*** pppT = new T **[nDim1];

    for ( int i = 0; i < nDim1; i++)
		pppT[i] = MakeTwoArray(nDim2, nDim3);

    return pppT;
}

template <class T>	
void CMakeArray<T>::DelThreeArray(T*** pppT, int nDim1, int nDim2)
{
    for ( int i = 0; i < nDim1; i++)	
		DelTwoArray(pppT[i], nDim2);
	delete[] pppT;
}

template <class T>
T**** CMakeArray<T>::MakeFourArray(int nDim1, int nDim2, int nDim3, int nDim4)
{
	T**** ppppT = new T ***[nDim1];

    for ( int i = 0; i < nDim1; i++ )
		ppppT[i] = MakeThreeArray(nDim2, nDim3, nDim4);

    return ppppT;
}

template <class T>	
void CMakeArray<T>::DelFourArray(T**** ppppT, int nDim1, int nDim2, int nDim3)
{
	for ( int i = 0; i < nDim1; i++ )	
	   DelThreeArray(ppppT[i], nDim2,nDim3);
	delete[] ppppT;
}

#endif  //!defined(OneDimArray_TwoDimArray_ThreeDimArray_FourDimArra

