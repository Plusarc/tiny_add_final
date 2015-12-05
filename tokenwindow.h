#pragma once
#include "afxcmn.h"


// tokenwindow 对话框

class tokenwindow : public CDialogEx
{
	DECLARE_DYNAMIC(tokenwindow)

public:
	tokenwindow(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~tokenwindow();

// 对话框数据
	enum { IDD = IDD_token };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_cresult;
};
