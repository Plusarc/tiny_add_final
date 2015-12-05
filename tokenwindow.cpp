// tokenwindow.cpp : 实现文件

#include "stdafx.h"
#include "tiny_add_final.h"
#include "tokenwindow.h"
#include "afxdialogex.h"



// tokenwindow 对话框

IMPLEMENT_DYNAMIC(tokenwindow, CDialogEx)

tokenwindow::tokenwindow(CWnd* pParent /*=NULL*/)
	: CDialogEx(tokenwindow::IDD, pParent)
{

}

tokenwindow::~tokenwindow()
{
}

void tokenwindow::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_cresult);
}

BEGIN_MESSAGE_MAP(tokenwindow, CDialogEx)
END_MESSAGE_MAP()

// tokenwindow 消息处理程序
