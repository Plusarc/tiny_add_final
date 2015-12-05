#include<iostream>
#include<cstring>
#include<fstream>
#include<sstream>

#include<string>
#include <afxtempl.h>
#include<iostream>
using namespace std;



//在用词法分析的时候需要用token承载返回错误类型如下
/****************/
const string MODES[]={"KEY","SYM","ID","NUM","STR","#",
"ERR1","ERR2","ERR3","ERR4","ERR5","ERR6",
"ERR7","ERR8","ERR9","ERR10","ERR11"};
const int key=0;
const int sym=1;
const int id =2;
const int num=3;
const int str=4;
const int endd=5;//忘了end为何用
const int err1=6;
const int err2=7;
const int err3=8;
const int err4=9;
const int err5=10;
const int err6=11;
const int err7=12;
const int err8=13;
const int err9=14;
const int err10=15;
const int err11=16;
/*
（词法分析时）
ERR1	非法字符
ERR2	缺少’\’’的字符串
ERR3	注释不完整
ERR4	缺少=的:=符号
（语法分析时）
ERR5	开始符号和后跟符号错误
ERR6	标识符匹配错误（int后不是标识符）
ERR7	括号匹配错误（（、）不匹配）
ERR8	符号错误（例如：=不该出现在比较语句中）
（语意分析阶段）
ERR9	未申明的标识符
ERR10	条件表达式的类型不是bool
ERR11	运算对象类型不相同
ERR12	赋值符号左边和右边类型不匹配
ERR13	缺少申明字段



/*
/****************/

const string Message[]={		
	"非法字符",
	"缺少’\'’的字符串",
	"注释不完整",
	"缺少=的:=符号",
	"开始符号和后跟符号错误",
	"标识符匹配错误",
	"括号匹配错误（（、）不匹配）",
	"符号错误",
	"未申明的标识符",
	"重复申明的标识符",
	"意外的程序结束",
	"运算对象类型不相同",
	"空的申明字段",
	"空文件",
};
static int ERR1=0;
static int ERR2=1;
static int ERR3=2;
static int ERR4=3;
static int ERR5=4;
static int ERR6=5;
static int ERR7=6;
static int ERR8=7;
static int ERR9=8;
static int ERR10=9;
static int ERR11=10;
static int ERR12=11;
static int ERR13=12;
static int ERR14=13;

//保留字
/*****************************/
const string KEY[18] = {"true","false","or","and","not","int","bool","string",
"while","do","if","then","else","end","repeat","until"};
/*****************************/

//保留字符集
/**********************************/
const string SYM[] = {":=","<=",">=","<>",",","'","{","}",";",">",
"+","-","*","/","(",")","<","="};
/**********************************/

//以下虽然重复，为细节化定义
/******************************************/
const string TYPES[]={"int","bool","string"};
const string BOOLVAR[]={"true","false"};
const string CONTROL[]={"while","do","if","then","else","end","repeat","until"};
const string MATHOP[]={"+","-","*","/"};
const string CMPOP[]={"<=",">=","<>",">","<","="};
//此做标注，赋值只使用：=
const string CODES[]={"int","bool","string","true","false","or","and","not","while","do",
"if","then","else","end","repeat","until",":=","<=",">=","<>",
",","'","{","}",";",">","+","-","*","/",
"(",")","<","="};//,"identifier","number"};

const int INT1=0;
const int BOOL1=1;
const int STR=2;
const int TRUE1=3;
const int FALSE1=4;
const int OR=5;
const int AND=6;
const int NOT=7;
const int WHILE= 8;
const int DO=9;
const int IF=10;
const int THEN=11;
const int ELSE=12;
const int END=13;
const int REPEAT=14;
const int UNTIL=15;
const int IS=16;//:=
const int LE=17;//<=
const int GE=18;//>=
const int NE=19;//==
const int COMMA=20;
const int QUO=21;
const int LCS=22;
const int RCS=23;
const int SEM=24;
const int GRA=25;
const int ADD=26;
const int SUB=27;
const int MUL=28;
const int DIV=29;
const int LBRA=30;
const int RBRA=31;
const int LES=32;
const int EQ=33;
const int ID=34;
const int NUM=35;
const int STRING=36;
/******************************************/

//要用到的汇编代码：
/*********************/
const string ASM[]={"ADD","SUB","MUL","DIV","JMP","JE","JNE","JG","JEG","JL","JEL"};
const int add=0;//+
const int sub=1;//-
const int mul=2;//*
const int di=3;// /
const int jmp=4;
const int je=5;//if int==int| bool==bool| bool==true| string==string then
const int jne=6; //if int!=int| bool!=bool| bool==false| string!=string then
const int jg=7;// if int>int then
const int jeg=8; //if int >=int then
const int jl=9;//if int <int then
const int jel=10;//if int <=int then
/***********************/

/*
所用到数据结构定义
*/


//用来传递词法分析结果的参数

	//type的值和types里边的是一一对应的
//全局token，每次调用scan，token就是下一个单词，如果这个单词mode




struct row
{
	string id;
	int type;
};
//struct table
//以某种方式存储符号表
//待定是数组还是哈希表，总之不会自己写
//{
	
//};



/****************************
词法分析模块
****************************/
//从string里取出一个单词，返回一个包含word和ID的struct node。
//word里边会包含一些出错信息（在mode里边）
bool scan(istream &input);
bool parsing(istream&input);
//1.parsing一次处理一行，但是每次调用parsing只返回一个word。
//2.parsing处理好的一行被存储在一个token队列里边
//3.调用parsing时如果token队列不为空，则只从token队列里读取数据，否则则再处理一行 
//以上只是一种可能的实现，只是配合之前做了那么多的一个函数，不一定之后一定执行，但返回值是固定的。





/****************************
语法分析模块
**************************/
void analyze(istream& input, ostream& output);//输入和输出的确定
//
/****************************/

/****************************
符号表的维护操作
对于所有的申明语句自动登录符号表，包括id（也就是标号），属性
***************************/
//这里有几个问题：
//1.调用方法有没有必要知道row的存在，还是调用方法用一个指针下标来访问这个row对应的属性，实际上返回值都一样
//2.login是返回成功与否还是返回这个指针。
row* newtempt(int type);//自动生成一个标号，类型为type对应的类型
row* lookup(string id);//查找这个标号是不是已经存在于符号表里了。
row* login(string id, int type);//程序的开始，遇到一个也许是新的标号，进行登录操作。
void inactive_stbl();
//由于不知道数值表达式会怎么处理，所以这里暂时搁置
/*****************************/

/***********************************
输出控制。
每次emit操作知识把一窜待输出的代码放在队列底边，
每次回填以后只要输出队列首的第四地址没有出现空着的情况（需要回填），则自动输出，否则则等待下次回填操作。
*/
//记住，这里需要一个当前输出行的参数
void emit(const string &,const string &, const string &, const string &);
void emit(const string &,const string &, const string &, const int &);//专门用于goto语句的语句
void backpatch(int ,int);//把后一个地址回填到前一个地址链表的对应跳转位置
int merge(int,int);//把第二链表尾巴和第一链表头相连，返回链表头
void print();
void inactive_emit();
/***************************************/

void main();
bool isNormal();//mode判断,不该结束的地方
bool isErr();
//在main方法里边调用parsing得到的东西
//符号表包括属性有：登陆ID，值，是否定义，类型
//定义语句登陆符号表
//赋值语句查询符号表并且输出

//定义异常类
class MyException
{
private:    
        // 错误码
        int m_errorId;
		string msg;
public:


        // 构造函数,参数为错误代码
        MyException(int errorId)
        {
                m_errorId = errorId;
        }

        // 拷贝构造函数
        MyException( MyException& myExp)
        {
                this->m_errorId = myExp.m_errorId;
				this->msg=myExp.msg;
        }

       ~MyException()
        {
                // 输出析构函数被调用信息
        }

       // 获取错误码
        int getErrorId()
        {
                return m_errorId;
        }
		void addMSG(string str)
		{
			msg+=':';
			msg.append(str);
		}
		string getMessage()
		{
			string tempt=Message[m_errorId];
			return tempt.append(msg);
		}
};


struct stmt
{
	int codebegin;
	int chain;
};
struct bexp
{
	int codebegin;
	int tc;
	int fc;
};
struct expr
{
	string id;
	int type;
};







///////////////////////**************************************************









class token{
public:
	CString kind;
	CString value;
	CString line;
};


class gramexp{
public:
	CString line;
	CString op;
	CString s1;
	CString s2;
	CString s0;
};



//CArray<CString,CString&> error;
//CArray<CString,CString&> keyword;
//CArray<CString,CString&> symbol;


#define LETTERSS 1
#define SYMM 2
#define NUMM 3
#define STRR 4
#define COMMENTT 5		//注释
#define ERRORWORDD 6

#define CODE_LEN 20280      //代码长度
#define WORD_LEN 20        //每个量的最大长度
#define STR_LEN 80        //每个量的最大长度

#define KEYWORD_SIZE 20
#define ERROR_SIZE 15
#define TOKENT_SIZE 1000
#define ID_SIZE 1000            //标识符表长度
#define NUM_SIZE 1000
#define SYM_SIZE 20
#define STR_SIZE 1000



class Word
{
public:

	static const CString keyword[];	//关键字及符号数据
	static const CString symbol[];	//关键字及符号数据
	static const CString speciasymbol[];
	

CArray<token,token&> tokenArray;	//数据数组
CArray<CString,CString&> errorArray;	//数据数组
//CArray<gramexp,gramexp&> yuexpArray; 


public:
	int bracket;
int strsym;
int commentsym;


public:
	Word(){
		bracket=0;strsym=0; commentsym=0;}

TCHAR chooseCondition(int &condition,int &point,CString &code,bool &wordcondition,bool &worderror,CString &newword);
void save(int &conditon,bool &wordconditon,CString &str,bool &wordcondition,bool &worderror,int &line,CString &newword);
void wordAnalyse(CString sourceCode);


};















//


