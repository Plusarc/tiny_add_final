
// tiny_add_finalDlg.cpp : 实现文件
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



// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// Ctiny_add_finalDlg 对话框



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


// Ctiny_add_finalDlg 消息处理程序

BOOL Ctiny_add_finalDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	/////////////////***************************************??????????????????
	CRect tabRect;   // 标签控件客户区的位置和大小   
  
    m_tab.InsertItem(0, _T("词法分析"));         // 插入第一个标签  
    m_tab.InsertItem(1, _T("语法分析"));  // 插入第二个标签   
    tokenwindow1.Create(IDD_token, &m_tab);    // 创建第一个标签页   
    gramwindow1.Create(IDD_gram, &m_tab); // 创建第二个标签页   
  
    m_tab.GetClientRect(&tabRect);    // 获取标签控件客户区Rect   
    // 调整tabRect，使其覆盖范围适合放置标签页   
    tabRect.left += 1;                  
    tabRect.right -= 1;   
    tabRect.top += 25;   
    tabRect.bottom -= 1;   
    // 根据调整好的tabRect放置m_jzmDlg子对话框，并设置为显示   
    tokenwindow1.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);   
    // 根据调整好的tabRect放置m_androidDlg子对话框，并设置为隐藏   
    gramwindow1.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);   

		CRect rect2;   
  
    // 获取编程语言列表视图控件的位置和大小   
m_error.GetClientRect(&rect2);   
  
    // 为列表视图控件添加全行选中和栅格风格   
m_error.SetExtendedStyle(m_error.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES); 
m_error.InsertColumn(0, _T("错误："), LVCFMT_CENTER, rect2.Width(), 0);   

////////////////***********************************????????????????????
//	
	CRect rect;   
//  
//    // 获取编程语言列表视图控件的位置和大小   
	tokenwindow1.m_cresult.GetClientRect(&rect);   
//  
    // 为列表视图控件添加全行选中和栅格风格   
tokenwindow1.m_cresult.SetExtendedStyle(tokenwindow1.m_cresult.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);   
tokenwindow1.m_cresult.InsertColumn(0, _T("line"), LVCFMT_CENTER, rect.Width()/6, 0);  
tokenwindow1.m_cresult.InsertColumn(1, _T("type"), LVCFMT_CENTER, rect.Width()/3, 1);   
tokenwindow1.m_cresult.InsertColumn(2, _T("content"), LVCFMT_CENTER, rect.Width()/2, 2);  

CRect rect3;   
//  
//    // 获取编程语言列表视图控件的位置和大小   
	gramwindow1.m_yresult.GetClientRect(&rect3);   
//  
    // 为列表视图控件添加全行选中和栅格风格   
gramwindow1.m_yresult.SetExtendedStyle(tokenwindow1.m_cresult.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);   
gramwindow1.m_yresult.InsertColumn(0, _T("NO"), LVCFMT_CENTER, rect.Width()/8, 0);   
gramwindow1.m_yresult.InsertColumn(1, _T("op"), LVCFMT_CENTER, rect.Width()/6, 1);  
gramwindow1.m_yresult.InsertColumn(2, _T("s1"), LVCFMT_CENTER, rect.Width()/6, 2);  
gramwindow1.m_yresult.InsertColumn(3, _T("s2"), LVCFMT_CENTER, rect.Width()/6, 3);  
gramwindow1.m_yresult.InsertColumn(4, _T("s0"), LVCFMT_CENTER, rect.Width()/6, 4);


 
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Ctiny_add_finalDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
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

	//显示数据
	
    CRect tabRect;    // 标签控件Rect   
  
    // 获取标签控件Rect，并对其调整，以适合放置标签页   
    m_tab.GetClientRect(&tabRect);   
    tabRect.left += 1;   
    tabRect.right -= 1;              //设置词法窗口未显示，另一个隐藏
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
   
  
    // 在列表视图控件中插入列表项，并设置列表子项文本   
   

}


void Ctiny_add_finalDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;   
    CRect tabRect;    // 标签控件客户区的Rect   
  
    // 获取标签控件客户区Rect，并对其调整，以适合放置标签页   
    m_tab.GetClientRect(&tabRect);   
    tabRect.left += 1;   
    tabRect.right -= 1;   
    tabRect.top += 25;   
    tabRect.bottom -= 1;   
  
    switch (m_tab.GetCurSel())   
    {   
    // 如果标签控件当前选择标签为“词法分析”，则显示tokenwindow1对话框，隐藏gramwindow1对话框   
    case 0:   
        tokenwindow1.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);   
        gramwindow1.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);   
        break;   
    // 如果标签控件当前选择标签为“语法分析”，则。。。。。。
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
    // 设置过滤器   
    TCHAR szFilter[] = _T("文本文件(*.txt)|*.txt|所有文件(*.*)|*.*||");   
    // 构造打开文件对话框   
    CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, szFilter, this);   
    CString strFilePath;   
  
    // 显示打开文件对话框   
    if (IDOK == fileDlg.DoModal())   
    {   
        // 如果点击了文件对话框上的“打开”按钮，则将选择的文件路径显示到编辑框里   
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

	 CRect tabRect;    // 标签控件的Rect  
	 m_tab.GetClientRect(&tabRect);   
    tabRect.left += 1;   
    tabRect.right -= 1;              //设置词法窗口未显示，另一个隐藏
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
		
		e1+=_T("行号：");
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
		//file.Write("/xff/xfe", 2); //Unicode编码的txt文件以0xff、0xfe两个字节作为开头标记。   
   

		

		//CString str = _T("D://校内项目//QQ.bmp");

            //注意：以下n和len的值大小不同,n是按字符计算的，len是按字节计算的
              int n = text.GetLength();     // n = 14, len = 18

             //获取宽字节字符的大小，大小是按字节计算的
             int len = WideCharToMultiByte(CP_ACP,0,text,text.GetLength(),NULL,0,NULL,NULL);

             //为多字节字符数组申请空间，数组大小为按字节计算的宽字节字节大小
            char * pFileName = new char[len+1];   //以字节为单位

            //宽字节编码转换成多字节编码
            WideCharToMultiByte(CP_ACP,0,text,text.GetLength(),pFileName,len,NULL,NULL);

            WideCharToMultiByte(CP_ACP,0,text,text.GetLength() + 1 ,pFileName,len + 1 ,NULL,NULL);
			pFileName[len] = '\0';   //多字节字符以'\0'结束
			file.Write(pFileName,len);
		file.Close();


	
}
