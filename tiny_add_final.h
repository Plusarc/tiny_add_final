
// tiny_add_final.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Ctiny_add_finalApp:
// �йش����ʵ�֣������ tiny_add_final.cpp
//

class Ctiny_add_finalApp : public CWinApp
{
public:
	Ctiny_add_finalApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Ctiny_add_finalApp theApp;