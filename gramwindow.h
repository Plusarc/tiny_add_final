#pragma once
#include "afxcmn.h"


// gramwindow �Ի���

class gramwindow : public CDialogEx
{
	DECLARE_DYNAMIC(gramwindow)

public:
	gramwindow(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~gramwindow();

// �Ի�������
	enum { IDD = IDD_gram };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_yresult;
};
