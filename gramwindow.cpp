// gramwindow.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "tiny_add_final.h"
#include "gramwindow.h"
#include "afxdialogex.h"


// gramwindow �Ի���

IMPLEMENT_DYNAMIC(gramwindow, CDialogEx)

gramwindow::gramwindow(CWnd* pParent /*=NULL*/)
	: CDialogEx(gramwindow::IDD, pParent)
{

}

gramwindow::~gramwindow()
{
}

void gramwindow::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_yresult);
}


BEGIN_MESSAGE_MAP(gramwindow, CDialogEx)
END_MESSAGE_MAP()


// gramwindow ��Ϣ�������
