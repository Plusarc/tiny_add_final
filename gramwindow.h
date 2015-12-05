#pragma once
#include "afxcmn.h"


// gramwindow 对话框

class gramwindow : public CDialogEx
{
	DECLARE_DYNAMIC(gramwindow)

public:
	gramwindow(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~gramwindow();

// 对话框数据
	enum { IDD = IDD_gram };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_yresult;
};
