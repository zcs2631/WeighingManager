
// WeighingManager.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CWeighingManagerApp: 
// �йش����ʵ�֣������ WeighingManager.cpp
//

class CWeighingManagerApp : public CWinApp
{
public:
	CWeighingManagerApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
public:
	CSerialPort serialPort1;

};

extern CWeighingManagerApp theApp;