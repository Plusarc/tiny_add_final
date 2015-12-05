
// tiny_add_final.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// Ctiny_add_finalApp:
// 有关此类的实现，请参阅 tiny_add_final.cpp
//

class Ctiny_add_finalApp : public CWinApp
{
public:
	Ctiny_add_finalApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern Ctiny_add_finalApp theApp;