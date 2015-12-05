#include "StdAfx.h"
#include "compiling.h"



const CString Word::keyword[KEYWORD_SIZE] ={_T("true"),_T("false"),_T("or"),_T("and"),
	                 _T("not"),_T("int"),_T("bool"),_T("string"),_T("while"),_T("do"),
                   _T("if"),_T("then"),_T("else"),_T("end"),_T("repeat"),_T("until"),_T("read")};   //�����ֱ�

const CString Word::symbol[SYM_SIZE]={_T(">"),_T("<="),_T(">="),_T("="),_T(","),_T("'"),  
	                                                         _T("{"),_T("}"),_T(";"),_T(":="),_T("+"),_T("-"),_T("*"),_T("/")
															 ,_T("("),_T(")"),_T("<"),_T("=")};  //���ű�

const CString Word::speciasymbol[3]={_T("<="),_T(">="),_T(":=")};

token token1;


//int bracket=0;
//int strsym=0;
//int commentsym=0;



CString num_table[NUM_SIZE];         //������
CString id_table[ID_SIZE];            //ID��ʶ����
CString str_table[STR_SIZE];          //�ַ�����
int idpoint=0;               //ID��ָ��
int numpoint=0;           //������ָ��
int strpoint=0;           //�ַ�����ָ��

token tokenbuffer[TOKENT_SIZE];     //token��
int tokenpoint=0;                      //token��ָ��


const TCHAR chrArry[] =_T("><=>,'{};:=+-*/()<=");

bool is_num(TCHAR read){            //�ж��Ƿ�Ϊ����
	if(read<='9'&&read>='0')return true;
	else return false;
}

bool is_letter(TCHAR read){             //�ж��Ƿ�Ϊ��ĸ
	if((read<='z'&&read>='a')||(read<='Z'&&read>='A'))return true;
	else return false;
}

bool is_space(TCHAR chr)
{
	//���հ��ַ�
	switch(chr) 
	{
	case '\t':	//tab
	case ' ':	//�ո�
	case '\n':	//����
	case '\r':	//�س�
	case '\f':	//��ֽ
		return true;
		break;
	}

	return false;
}



bool is_connect(TCHAR chr)
{
	

	for(int i=0; i<=18; ++i)
	{
		if (chrArry[i] == chr)
		{
			return true;
		}
	}

	return false;
}

int is_key(CString word){                  //�ж��Ƿ�Ϊ�ؼ���
	for(int i=0;i<KEYWORD_SIZE;i++){
		if(word.Compare(Word::keyword[i])==0){return i+1;}     
	}
	return 0;
}

int is_sym(CString word){                  //�ж��Ƿ�Ϊ�ؼ���
	for(int i=0;i<17;i++){
		if(word.Compare(Word::symbol[i])==0){return i+1;     }     
	}
	return 0;
}

bool is_specialsym(CString word){
for(int i=0;i<3;i++){
		if(word.Compare(Word::speciasymbol[i])==0){return true;}     
	}
	return false;
}

int insert_id(CString value){
	
	if(idpoint<ID_SIZE) {id_table[idpoint++]=value;
	
	return (idpoint-1);}
	else return 0;
}

int insert_num(CString value){
	if(numpoint<NUM_SIZE) {num_table[numpoint++]=value;return (numpoint-1);}
	else return 0;
}

int insert_str(CString value){
	if(strpoint<STR_SIZE) {str_table[strpoint++]=value;return (strpoint-1);}
	else return 0;
}



void Word::wordAnalyse(CString sourceCode)
{
	//m_ErrorArray.RemoveAll();
	//m_DataArray.RemoveAll();

	int condition= -1;		//��ǰ��ʶ,��ʶĿǰ��״̬�������֣�ע�ͣ�or�ַ���
	CString newword;	//�����ַ���
	int line = 1;	//��ǰ����
	TCHAR choose=' ';
	bool wordcondition=false;
	bool worderror=false;

	for(int point=0; point<(int)sourceCode.GetLength(); point++)
	{  
		if((point==(int)sourceCode.GetLength()-1)&&commentsym!=0){
			CString msg(_T("ע�ʹ����޷������ʷ�������"));
	        errorArray.Add(msg);
			return;}
		const TCHAR read = sourceCode[point];         //�ַ�

		//�հ�
		if(is_space(read))            //�ж��Ƿ�Ϊ�ո񣬰����ո�س�������
		{
			if (sourceCode[point]=='\n')
			{   //if(strsym!=0)cout<<line<<"�е����Ŵ���"<<endl;////////////////////*********************�����Ų����
				if(bracket!=0){CString msg;
		msg.Format(_T("�к�:%d\t\t���Ų����:%s"),line,newword);
	     errorArray.Add(msg);bracket=0;}//////////////////////////////С���Ų����
				
				line++;
			}

			if (condition!=COMMENTT)               //���״̬��Ϊע�ͣ�������Ϊ�գ�׼����ʼ��һ��״̬
			{   
				//if(condition!=-1);//////////////////***************************************SAVE
				condition=-1;
				newword="";
			}

			continue;                                    //���ؼ���ִ����һ��forѭ��
		}

		//ע��
		if(read=='{' )                               
		{ commentsym++;
		if(commentsym!=0&&commentsym!=1){
				CString msg(_T("ע�ʹ����޷������ʷ�������"));
	        errorArray.Add(msg);return;}////////////////////////*************///////////////////****************����Ȼ��return
			condition=COMMENTT;             //nsign����Ϊע��״̬
			continue;                                      //��һ��forѭ��
		}
		else if(read=='}')                        //�������}��ע�����
		{
			commentsym--;
			if(commentsym!=0&&commentsym!=1){
				CString msg(_T("ע�ʹ����޷������ʷ�������"));
	        errorArray.Add(msg);return;}////////////////////////****************����Ȼ��return
			condition= -1;
			continue;
		}
		else if (condition==COMMENTT)     //���״̬Ϊע��
		{
			continue;
		}


		bool rightcondition= false;               //�����ǰ���벻Ϊע�ͣ���ʼ��ʽ��ʶ�����

		if(condition==STRR)choose='S';
		else if(is_num(read))choose='N';
		else if(is_letter(read))choose='L';
		else choose=read;
		//����
		switch(choose){
		case 'L':
			if(condition==-1)condition=LETTERSS;
			newword+=read;           //��ǰ�ַ������϶�����ַ�
		break;

		case 'N':
			if(condition==-1)condition=NUMM;
			newword+=read;
		break;

		case 'S':

			newword+=read;
			break;

		case '\'':
			if(condition==STRR){condition=-1,strsym--;}
			if(condition!=STRR){condition=STRR,strsym++;}
			
			break;
			
		case '<':
       condition=SYMM;
		newword+=read;
	   break;
	case '>':
		condition=SYMM;
		newword+=read;
	   break;

	case ':':
		condition=SYMM;
		newword+=read;
	  break;

	case '(':
		condition=SYMM;
		newword+=read;
		bracket++;
	   break;
	  

	case ')':
		bracket--;
	condition=SYMM;
		newword+=read;
	   break;
	
	case ',':
	case ';':
	case '+':
	case '-':
	case '*':
	case '=':
	case '/':
	 condition=SYMM;
		newword+=read;
	  break;

	default:
		//newword+=read;
		//CString msg;
		//msg.Format(_T("�к�:%d\t\t�Ƿ����ַ�:%s"),line,newword);
	 //    errorArray.Add(msg);///////////////////������ʾ//////////������ʾ
		// condition=ERRORWORD;

		newword+=read;
		CString msg;
		if(condition!=ERRORWORDD){
		//msg.Format(_T("�к�:%d\t\t�Ƿ����ַ�:%s"),line,newword);
	    // errorArray.Add(msg);///////////////////������ʾ//////////������ʾ
		 condition=ERRORWORDD;
		}
		
		}

		
		TCHAR choose=chooseCondition(condition,point,sourceCode,wordcondition,worderror,newword);
		switch(choose){
			case 'F':continue;
			case 'C':continue;
			break;
		    case 'A':save(condition,wordcondition,newword,wordcondition,worderror,line,newword);
		}
		}
		}
		
		
		






TCHAR Word::chooseCondition(int &condition,int &point,CString &code,bool &wordcondition,bool &worderror,CString &newword){
    TCHAR nextview=' ';
	switch(condition){
	case LETTERSS:
		if(is_letter(code[point+1])||is_num(code[point+1]))nextview='C';
		else if(is_connect(code[point+1])||is_space(code[point+1])){nextview='A';wordcondition=true;}
		else {nextview='F';worderror=true;}
		break;

	case NUMM:
		if(is_num(code[point+1]))nextview='C';
		else if(is_letter(code[point+1])){nextview='F';worderror=true;}
		else if (is_connect(code[point+1])||is_space(code[point+1])){nextview='A';wordcondition=true;}
		break;

	case SYMM:
		if(is_specialsym(newword)){nextview='A';wordcondition=true;break;}
		if(is_connect(code[point+1]))nextview='C';
		else {nextview='A';wordcondition=true;}
		break;

	case STRR:
		if(code[point+1]=='\''){nextview='A';point++;wordcondition=true;}
		else if(code[point+1]=='\n'||code[point+1]=='\r'){nextview='A';wordcondition=true;worderror=true;}
		else{nextview='C';}
		break;

	case ERRORWORDD:////////////////////////////////////////////���ڱ�ʾ���У�����Ϊ��ʾ���������ִ��󣬵������ַ�����
		
		if(!is_connect(code[point+1]))nextview='C';
		else{nextview='A';wordcondition=true;}
	}
	return nextview;
}

//Token(int row, int kind, CString str)
//{
//	m_Kind = kind;
//	m_Row = row;
//	m_Str = str;
//	
//}


void Word::save(int &condition,bool &wordconditon,CString &str,bool &wordcondition,bool &worderror,int &line,CString &newword){
	if(wordcondition){
	switch(condition){
	case LETTERSS:
		if(!worderror){
			if(is_key(str)){token1.kind="KEY";token1.value=newword;token1.line.Format(_T("%d"),line);tokenArray.Add(token1);}////////////////////////////**********************key����token
			else{token1.kind="ID";token1.value=newword;tokenArray.Add(token1);}//////////////////*********************; ������ű�token
		}
		else{CString msg;
		msg.Format(_T("�к�:%d"),line);
		msg+=_T("  �Ƿ��ı�ʾ�� ");
		msg+=newword;
	     errorArray.Add(msg);}///////////////////������ʾ
		break;

		
	case NUMM:
		if(!worderror){token1.kind="NUM";token1.value=newword;token1.line.Format(_T("%d"),line);tokenArray.Add(token1);}/////////num������ű�token
		else{CString msg;
		msg.Format(_T("�к�:%d"),line);
		msg+=_T("  �Ƿ�����ֵ���� ");
		msg+=newword;
	     errorArray.Add(msg);}///////////////////������ʾ///////////////������ʾ
		break;

	case STRR:
		if(!worderror){token1.kind="STR";token1.value=newword;token1.line.Format(_T("%d"),line);tokenArray.Add(token1);}//////////////////////������ű�token
		else{CString msg;
		msg.Format(_T("�к�:%d"),line);
		msg+=_T("  �Ƿ����ַ������� ");
		msg+=newword;
	     errorArray.Add(msg);}///////////////////������ʾ//////////////������ʾ
			break;

	case SYMM:
		if(is_sym(newword)){token1.kind="SYM";token1.value=newword;token1.line.Format(_T("%d"),line);tokenArray.Add(token1);}////////////////������ű�token
		else{CString msg;
		msg.Format(_T("�к�:%d"),line);
		msg+=_T("  �Ƿ��ķ���");
		msg+=newword;
	     errorArray.Add(msg);}///////////////////������ʾ//////////������ʾ
		break;

	case ERRORWORDD:
		CString msg;
		msg.Format(_T("�к�:%d"),line);
		msg+=_T("  �����Ƿ����ַ� ");
		msg+=newword;
	     errorArray.Add(msg);///////////////////������ʾ//////////������ʾ
		 break;
	}
	newword="";
	worderror=false;
	wordcondition=false;
	condition=-1;
	}
}






