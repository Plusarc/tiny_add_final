
// tiny_add_finalDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "gramwindow.h"
#include "tokenwindow.h"



// Ctiny_add_finalDlg �Ի���
class Ctiny_add_finalDlg : public CDialogEx
{
// ����
public:
	Ctiny_add_finalDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TINY_ADD_FINAL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	//tab������������
	gramwindow gramwindow1;
	tokenwindow tokenwindow1;

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CEdit m_edit;
	CListCtrl m_error;
	CTabCtrl m_tab;
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton1();
	//static CString position;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
};

static CString position;

