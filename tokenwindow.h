#pragma once
#include "afxcmn.h"


// tokenwindow �Ի���

class tokenwindow : public CDialogEx
{
	DECLARE_DYNAMIC(tokenwindow)

public:
	tokenwindow(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~tokenwindow();

// �Ի�������
	enum { IDD = IDD_token };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_cresult;
};
