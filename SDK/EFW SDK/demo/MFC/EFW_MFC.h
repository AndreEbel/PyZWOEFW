
// EFW_MFC.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CEFW_MFCApp:
// �йش����ʵ�֣������ EFW_MFC.cpp
//

class CEFW_MFCApp : public CWinApp
{
public:
	CEFW_MFCApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CEFW_MFCApp theApp;