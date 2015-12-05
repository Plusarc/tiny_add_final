#include<iostream>
#include<cstring>
#include<fstream>
#include<sstream>

#include<string>
#include <afxtempl.h>
#include<iostream>
using namespace std;



//���ôʷ�������ʱ����Ҫ��token���ط��ش�����������
/****************/
const string MODES[]={"KEY","SYM","ID","NUM","STR","#",
"ERR1","ERR2","ERR3","ERR4","ERR5","ERR6",
"ERR7","ERR8","ERR9","ERR10","ERR11"};
const int key=0;
const int sym=1;
const int id =2;
const int num=3;
const int str=4;
const int endd=5;//����endΪ����
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
���ʷ�����ʱ��
ERR1	�Ƿ��ַ�
ERR2	ȱ�١�\�������ַ���
ERR3	ע�Ͳ�����
ERR4	ȱ��=��:=����
���﷨����ʱ��
ERR5	��ʼ���źͺ�����Ŵ���
ERR6	��ʶ��ƥ�����int���Ǳ�ʶ����
ERR7	����ƥ����󣨣�������ƥ�䣩
ERR8	���Ŵ������磺=���ó����ڱȽ�����У�
����������׶Σ�
ERR9	δ�����ı�ʶ��
ERR10	�������ʽ�����Ͳ���bool
ERR11	����������Ͳ���ͬ
ERR12	��ֵ������ߺ��ұ����Ͳ�ƥ��
ERR13	ȱ�������ֶ�



/*
/****************/

const string Message[]={		
	"�Ƿ��ַ�",
	"ȱ�١�\'�����ַ���",
	"ע�Ͳ�����",
	"ȱ��=��:=����",
	"��ʼ���źͺ�����Ŵ���",
	"��ʶ��ƥ�����",
	"����ƥ����󣨣�������ƥ�䣩",
	"���Ŵ���",
	"δ�����ı�ʶ��",
	"�ظ������ı�ʶ��",
	"����ĳ������",
	"����������Ͳ���ͬ",
	"�յ������ֶ�",
	"���ļ�",
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

//������
/*****************************/
const string KEY[18] = {"true","false","or","and","not","int","bool","string",
"while","do","if","then","else","end","repeat","until"};
/*****************************/

//�����ַ���
/**********************************/
const string SYM[] = {":=","<=",">=","<>",",","'","{","}",";",">",
"+","-","*","/","(",")","<","="};
/**********************************/

//������Ȼ�ظ���Ϊϸ�ڻ�����
/******************************************/
const string TYPES[]={"int","bool","string"};
const string BOOLVAR[]={"true","false"};
const string CONTROL[]={"while","do","if","then","else","end","repeat","until"};
const string MATHOP[]={"+","-","*","/"};
const string CMPOP[]={"<=",">=","<>",">","<","="};
//������ע����ֵֻʹ�ã�=
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

//Ҫ�õ��Ļ����룺
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
���õ����ݽṹ����
*/


//�������ݴʷ���������Ĳ���

	//type��ֵ��types��ߵ���һһ��Ӧ��
//ȫ��token��ÿ�ε���scan��token������һ�����ʣ�����������mode




struct row
{
	string id;
	int type;
};
//struct table
//��ĳ�ַ�ʽ�洢���ű�
//���������黹�ǹ�ϣ����֮�����Լ�д
//{
	
//};



/****************************
�ʷ�����ģ��
****************************/
//��string��ȡ��һ�����ʣ�����һ������word��ID��struct node��
//word��߻����һЩ������Ϣ����mode��ߣ�
bool scan(istream &input);
bool parsing(istream&input);
//1.parsingһ�δ���һ�У�����ÿ�ε���parsingֻ����һ��word��
//2.parsing����õ�һ�б��洢��һ��token�������
//3.����parsingʱ���token���в�Ϊ�գ���ֻ��token�������ȡ���ݣ��������ٴ���һ�� 
//����ֻ��һ�ֿ��ܵ�ʵ�֣�ֻ�����֮ǰ������ô���һ����������һ��֮��һ��ִ�У�������ֵ�ǹ̶��ġ�





/****************************
�﷨����ģ��
**************************/
void analyze(istream& input, ostream& output);//����������ȷ��
//
/****************************/

/****************************
���ű��ά������
�������е���������Զ���¼���ű�����id��Ҳ���Ǳ�ţ�������
***************************/
//�����м������⣺
//1.���÷�����û�б�Ҫ֪��row�Ĵ��ڣ����ǵ��÷�����һ��ָ���±����������row��Ӧ�����ԣ�ʵ���Ϸ���ֵ��һ��
//2.login�Ƿ��سɹ�����Ƿ������ָ�롣
row* newtempt(int type);//�Զ�����һ����ţ�����Ϊtype��Ӧ������
row* lookup(string id);//�����������ǲ����Ѿ������ڷ��ű����ˡ�
row* login(string id, int type);//����Ŀ�ʼ������һ��Ҳ�����µı�ţ����е�¼������
void inactive_stbl();
//���ڲ�֪����ֵ���ʽ����ô��������������ʱ����
/*****************************/

/***********************************
������ơ�
ÿ��emit����֪ʶ��һ�ܴ�����Ĵ�����ڶ��еױߣ�
ÿ�λ����Ժ�ֻҪ��������׵ĵ��ĵ�ַû�г��ֿ��ŵ��������Ҫ��������Զ������������ȴ��´λ��������
*/
//��ס��������Ҫһ����ǰ����еĲ���
void emit(const string &,const string &, const string &, const string &);
void emit(const string &,const string &, const string &, const int &);//ר������goto�������
void backpatch(int ,int);//�Ѻ�һ����ַ���ǰһ����ַ����Ķ�Ӧ��תλ��
int merge(int,int);//�ѵڶ�����β�ͺ͵�һ����ͷ��������������ͷ
void print();
void inactive_emit();
/***************************************/

void main();
bool isNormal();//mode�ж�,���ý����ĵط�
bool isErr();
//��main������ߵ���parsing�õ��Ķ���
//���ű���������У���½ID��ֵ���Ƿ��壬����
//��������½���ű�
//��ֵ����ѯ���ű������

//�����쳣��
class MyException
{
private:    
        // ������
        int m_errorId;
		string msg;
public:


        // ���캯��,����Ϊ�������
        MyException(int errorId)
        {
                m_errorId = errorId;
        }

        // �������캯��
        MyException( MyException& myExp)
        {
                this->m_errorId = myExp.m_errorId;
				this->msg=myExp.msg;
        }

       ~MyException()
        {
                // �������������������Ϣ
        }

       // ��ȡ������
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
#define COMMENTT 5		//ע��
#define ERRORWORDD 6

#define CODE_LEN 20280      //���볤��
#define WORD_LEN 20        //ÿ��������󳤶�
#define STR_LEN 80        //ÿ��������󳤶�

#define KEYWORD_SIZE 20
#define ERROR_SIZE 15
#define TOKENT_SIZE 1000
#define ID_SIZE 1000            //��ʶ������
#define NUM_SIZE 1000
#define SYM_SIZE 20
#define STR_SIZE 1000



class Word
{
public:

	static const CString keyword[];	//�ؼ��ּ���������
	static const CString symbol[];	//�ؼ��ּ���������
	static const CString speciasymbol[];
	

CArray<token,token&> tokenArray;	//��������
CArray<CString,CString&> errorArray;	//��������
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


