
// tiny_add_finalDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "tiny_add_final.h"
#include "tiny_add_finalDlg.h"
#include "afxdialogex.h"
#include "compiling.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern int mode;
extern string token;
extern int par_line;
extern istream glo_input;
extern int code_index;

extern CArray<gramexp,gramexp&> gramArray;



// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Ctiny_add_finalDlg �Ի���



Ctiny_add_finalDlg::Ctiny_add_finalDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Ctiny_add_finalDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Ctiny_add_finalDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
	DDX_Control(pDX, IDC_LIST1, m_error);
	DDX_Control(pDX, IDC_TAB1, m_tab);
}

BEGIN_MESSAGE_MAP(Ctiny_add_finalDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &Ctiny_add_finalDlg::OnBnClickedOk)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &Ctiny_add_finalDlg::OnTcnSelchangeTab1)
	ON_BN_CLICKED(IDC_BUTTON1, &Ctiny_add_finalDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &Ctiny_add_finalDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &Ctiny_add_finalDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// Ctiny_add_finalDlg ��Ϣ�������

BOOL Ctiny_add_finalDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	/////////////////***************************************??????????????????
	CRect tabRect;   // ��ǩ�ؼ��ͻ�����λ�úʹ�С   
  
    m_tab.InsertItem(0, _T("�ʷ�����"));         // �����һ����ǩ  
    m_tab.InsertItem(1, _T("�﷨����"));  // ����ڶ�����ǩ   
    tokenwindow1.Create(IDD_token, &m_tab);    // ������һ����ǩҳ   
    gramwindow1.Create(IDD_gram, &m_tab); // �����ڶ�����ǩҳ   
  
    m_tab.GetClientRect(&tabRect);    // ��ȡ��ǩ�ؼ��ͻ���Rect   
    // ����tabRect��ʹ�串�Ƿ�Χ�ʺϷ��ñ�ǩҳ   
    tabRect.left += 1;                  
    tabRect.right -= 1;   
    tabRect.top += 25;   
    tabRect.bottom -= 1;   
    // ���ݵ����õ�tabRect����m_jzmDlg�ӶԻ��򣬲�����Ϊ��ʾ   
    tokenwindow1.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);   
    // ���ݵ����õ�tabRect����m_androidDlg�ӶԻ��򣬲�����Ϊ����   
    gramwindow1.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);   

		CRect rect2;   
  
    // ��ȡ��������б���ͼ�ؼ���λ�úʹ�С   
m_error.GetClientRect(&rect2);   
  
    // Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
m_error.SetExtendedStyle(m_error.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES); 
m_error.InsertColumn(0, _T("����"), LVCFMT_CENTER, rect2.Width(), 0);   

////////////////***********************************????????????????????
//	
	CRect rect;   
//  
//    // ��ȡ��������б���ͼ�ؼ���λ�úʹ�С   
	tokenwindow1.m_cresult.GetClientRect(&rect);   
//  
    // Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
tokenwindow1.m_cresult.SetExtendedStyle(tokenwindow1.m_cresult.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);   
tokenwindow1.m_cresult.InsertColumn(0, _T("line"), LVCFMT_CENTER, rect.Width()/6, 0);  
tokenwindow1.m_cresult.InsertColumn(1, _T("type"), LVCFMT_CENTER, rect.Width()/3, 1);   
tokenwindow1.m_cresult.InsertColumn(2, _T("content"), LVCFMT_CENTER, rect.Width()/2, 2);  

CRect rect3;   
//  
//    // ��ȡ��������б���ͼ�ؼ���λ�úʹ�С   
	gramwindow1.m_yresult.GetClientRect(&rect3);   
//  
    // Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
gramwindow1.m_yresult.SetExtendedStyle(tokenwindow1.m_cresult.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);   
gramwindow1.m_yresult.InsertColumn(0, _T("NO"), LVCFMT_CENTER, rect.Width()/8, 0);   
gramwindow1.m_yresult.InsertColumn(1, _T("op"), LVCFMT_CENTER, rect.Width()/6, 1);  
gramwindow1.m_yresult.InsertColumn(2, _T("s1"), LVCFMT_CENTER, rect.Width()/6, 2);  
gramwindow1.m_yresult.InsertColumn(3, _T("s2"), LVCFMT_CENTER, rect.Width()/6, 3);  
gramwindow1.m_yresult.InsertColumn(4, _T("s0"), LVCFMT_CENTER, rect.Width()/6, 4);


 
	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}



void Ctiny_add_finalDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void Ctiny_add_finalDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR Ctiny_add_finalDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

Word w1;

void Ctiny_add_finalDlg::OnBnClickedOk()
{
    CString code;
	m_edit.GetWindowText(code);
	code=code+_T(" ");

	w1.wordAnalyse(code);

	//��ʾ����
	
    CRect tabRect;    // ��ǩ�ؼ�Rect   
  
    // ��ȡ��ǩ�ؼ�Rect����������������ʺϷ��ñ�ǩҳ   
    m_tab.GetClientRect(&tabRect);   
    tabRect.left += 1;   
    tabRect.right -= 1;              //���ôʷ�����δ��ʾ����һ������
    tabRect.top += 25;   
    tabRect.bottom -= 1;   
	 tokenwindow1.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);   
        gramwindow1.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);   



	m_error.DeleteAllItems();
	tokenwindow1.m_cresult.DeleteAllItems();

	
	for (int index=0; index<=w1.tokenArray.GetSize()-1; ++index) 
	{
		tokenwindow1.m_cresult.InsertItem(index, w1.tokenArray[index].line); 
		tokenwindow1.m_cresult.SetItemText(index, 1,w1.tokenArray[index].kind); 
       tokenwindow1.m_cresult.SetItemText(index, 2,w1.tokenArray[index].value);   
	   
	}

	
	for (int index=0; index<=w1.errorArray.GetSize()-1; ++index) 
	{
		m_error.InsertItem(index, w1.errorArray[index]);
		
	}
	w1.tokenArray.RemoveAll();
	w1.errorArray.RemoveAll();
   
  
    // ���б���ͼ�ؼ��в����б���������б������ı�   
   

}


void Ctiny_add_finalDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;   
    CRect tabRect;    // ��ǩ�ؼ��ͻ�����Rect   
  
    // ��ȡ��ǩ�ؼ��ͻ���Rect����������������ʺϷ��ñ�ǩҳ   
    m_tab.GetClientRect(&tabRect);   
    tabRect.left += 1;   
    tabRect.right -= 1;   
    tabRect.top += 25;   
    tabRect.bottom -= 1;   
  
    switch (m_tab.GetCurSel())   
    {   
    // �����ǩ�ؼ���ǰѡ���ǩΪ���ʷ�������������ʾtokenwindow1�Ի�������gramwindow1�Ի���   
    case 0:   
        tokenwindow1.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);   
        gramwindow1.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);   
        break;   
    // �����ǩ�ؼ���ǰѡ���ǩΪ���﷨���������򡣡���������
    case 1:   
       tokenwindow1.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);   
        gramwindow1.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);   
        break;   
    default:   
        break;   
    }   
}


void Ctiny_add_finalDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here   
    // ���ù�����   
    TCHAR szFilter[] = _T("�ı��ļ�(*.txt)|*.txt|�����ļ�(*.*)|*.*||");   
    // ������ļ��Ի���   
    CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, szFilter, this);   
    CString strFilePath;   
  
    // ��ʾ���ļ��Ի���   
    if (IDOK == fileDlg.DoModal())   
    {   
        // ���������ļ��Ի����ϵġ��򿪡���ť����ѡ����ļ�·����ʾ���༭����   
        strFilePath = fileDlg.GetPathName();   
        //SetDlgItemText(IDC_EDIT1, strFilePath);  
		position=strFilePath;
	//	string tempposition;
	//	//tempposition=strFilePath.GetBuffer(0);

	//	char codetemp[CODE_LEN];
	//	//fstream code("e:\\code.txt",ios::in);
	//	fstream code(strFilePath,ios::in);
	//code.getline(codetemp,CODE_LEN,'\0');
	//string codebuffer(codetemp,0,strlen(codetemp));
	//codebuffer+=' ';

	
	
	CFile file(strFilePath, CFile::modeRead);
		char* pChar = new char[file.GetLength()];   
		file.Read(pChar,file.GetLength());
		CString text(pChar, file.GetLength());
		file.Close();
		
		m_edit.SetWindowText(text);

		gramwindow1.m_yresult.DeleteAllItems();
		tokenwindow1.m_cresult.DeleteAllItems();
		m_error.DeleteAllItems();
		//CString ctemp;
		//ctemp=codebuffer.c_str();
		//m_edit.SetWindowText(ctemp);
		//SetWindowText(IDC_EDIT1, ctemp);
		//SetDlgItemText(IDC_EDIT1, ctemp); 
		
//		code.close();
    }   
}


void Ctiny_add_finalDlg::OnBnClickedButton2()
{

	//gram gram1;
	ifstream input(position,ios::in);
	//cout<<position<<endl;
	if(!input)cout<<"false to open"<<endl;
	ofstream output("e:\\result.txt",ios::out);

	gramwindow1.m_yresult.DeleteAllItems();
	m_error.DeleteAllItems();

	 CRect tabRect;    // ��ǩ�ؼ���Rect  
	 m_tab.GetClientRect(&tabRect);   
    tabRect.left += 1;   
    tabRect.right -= 1;              //���ôʷ�����δ��ʾ����һ������
    tabRect.top += 25;   
    tabRect.bottom -= 1;  
	tokenwindow1.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);   
    gramwindow1.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);   

	bool choose=true;
	try
	{
		analyze(input,output);

	}
	catch(MyException ex)
	
	{   choose=false;
	//	//cout<<endl;
	//	//cout<<ex.getMessage()<<" "<<"in line:"<<par_line<<" "<<endl;
		CString e1;
		
		e1+=_T("�кţ�");
		CString tmeps;
		tmeps.Format(_T("%d"),par_line);
		//yus+=par_line;
		e1+=tmeps;
		e1+=_T("  ");
		e1+=ex.getMessage().c_str();
		m_error.DeleteAllItems();
		m_error.InsertItem(0,e1);
		///////////////////////*****************************************////////////////IMPORTANT
	}	

	if(choose){
		//gramwindow1.m_yresult.DeleteAllItems();
		gramwindow1.m_yresult.DeleteAllItems();
	for (int index=0; index<=gramArray.GetSize()-1; ++index) 
	{
		gramwindow1.m_yresult.InsertItem(index,gramArray[index].line); 
		gramwindow1.m_yresult.SetItemText(index,1,gramArray[index].op); 
		gramwindow1.m_yresult.SetItemText(index,2,gramArray[index].s1); 
		gramwindow1.m_yresult.SetItemText(index,3,gramArray[index].s2); 
		gramwindow1.m_yresult.SetItemText(index,4,gramArray[index].s0); 
        
	   
	}


	}
	gramArray.RemoveAll();
	//CString s=_T("ERROR");
	//m_edit.SetWindowTextW(s);
	input.close();
	output.close();
	inactive_stbl();
	inactive_emit();
	par_line=-1;
	//code_index=0;
}


void Ctiny_add_finalDlg::OnBnClickedButton3()
{
	CString text;
		m_edit.GetWindowText(text);

		CFile file(position, CFile::modeWrite|CFile::modeCreate);
		//file.Write("/xff/xfe", 2); //Unicode�����txt�ļ���0xff��0xfe�����ֽ���Ϊ��ͷ��ǡ�   
   

		

		//CString str = _T("D://У����Ŀ//QQ.bmp");

            //ע�⣺����n��len��ֵ��С��ͬ,n�ǰ��ַ�����ģ�len�ǰ��ֽڼ����
              int n = text.GetLength();     // n = 14, len = 18

             //��ȡ���ֽ��ַ��Ĵ�С����С�ǰ��ֽڼ����
             int len = WideCharToMultiByte(CP_ACP,0,text,text.GetLength(),NULL,0,NULL,NULL);

             //Ϊ���ֽ��ַ���������ռ䣬�����СΪ���ֽڼ���Ŀ��ֽ��ֽڴ�С
            char * pFileName = new char[len+1];   //���ֽ�Ϊ��λ

            //���ֽڱ���ת���ɶ��ֽڱ���
            WideCharToMultiByte(CP_ACP,0,text,text.GetLength(),pFileName,len,NULL,NULL);

            WideCharToMultiByte(CP_ACP,0,text,text.GetLength() + 1 ,pFileName,len + 1 ,NULL,NULL);
			pFileName[len] = '\0';   //���ֽ��ַ���'\0'����
			file.Write(pFileName,len);
		file.Close();


	
}
