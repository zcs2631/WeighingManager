// serialportApi.h : serialportApi DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CserialportApiApp
// �йش���ʵ�ֵ���Ϣ������� serialportApi.cpp
//

class CserialportApiApp : public CWinApp
{
public:
	CserialportApiApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
