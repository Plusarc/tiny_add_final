#include "StdAfx.h"
#include "compiling.h"



const CString Word::keyword[KEYWORD_SIZE] ={_T("true"),_T("false"),_T("or"),_T("and"),
	                 _T("not"),_T("int"),_T("bool"),_T("string"),_T("while"),_T("do"),
                   _T("if"),_T("then"),_T("else"),_T("end"),_T("repeat"),_T("until"),_T("read")};   //保留字表

const CString Word::symbol[SYM_SIZE]={_T(">"),_T("<="),_T(">="),_T("="),_T(","),_T("'"),  
	                                                         _T("{"),_T("}"),_T(";"),_T(":="),_T("+"),_T("-"),_T("*"),_T("/")
															 ,_T("("),_T(")"),_T("<"),_T("=")};  //符号表

const CString Word::speciasymbol[3]={_T("<="),_T(">="),_T(":=")};

token token1;


//int bracket=0;
//int strsym=0;
//int commentsym=0;



CString num_table[NUM_SIZE];         //常数表
CString id_table[ID_SIZE];            //ID标识符表
CString str_table[STR_SIZE];          //字符串表
int idpoint=0;               //ID表指针
int numpoint=0;           //常数表指针
int strpoint=0;           //字符串表指针

token tokenbuffer[TOKENT_SIZE];     //token表
int tokenpoint=0;                      //token表指针


const TCHAR chrArry[] =_T("><=>,'{};:=+-*/()<=");

bool is_num(TCHAR read){            //判断是否为常数
	if(read<='9'&&read>='0')return true;
	else return false;
}

bool is_letter(TCHAR read){             //判断是否为字母
	if((read<='z'&&read>='a')||(read<='Z'&&read>='A'))return true;
	else return false;
}

bool is_space(TCHAR chr)
{
	//检测空白字符
	switch(chr) 
	{
	case '\t':	//tab
	case ' ':	//空格
	case '\n':	//换行
	case '\r':	//回车
	case '\f':	//走纸
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

int is_key(CString word){                  //判断是否为关键字
	for(int i=0;i<KEYWORD_SIZE;i++){
		if(word.Compare(Word::keyword[i])==0){return i+1;}     
	}
	return 0;
}

int is_sym(CString word){                  //判断是否为关键字
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

	int condition= -1;		//当前标识,标识目前的状态，是数字，注释，or字符串
	CString newword;	//缓冲字符串
	int line = 1;	//当前行数
	TCHAR choose=' ';
	bool wordcondition=false;
	bool worderror=false;

	for(int point=0; point<(int)sourceCode.GetLength(); point++)
	{  
		if((point==(int)sourceCode.GetLength()-1)&&commentsym!=0){
			CString msg(_T("注释错误，无法继续词法分析！"));
	        errorArray.Add(msg);
			return;}
		const TCHAR read = sourceCode[point];         //字符

		//空白
		if(is_space(read))            //判断是否为空格，包括空格回车，换行
		{
			if (sourceCode[point]=='\n')
			{   //if(strsym!=0)cout<<line<<"行单引号错误"<<endl;////////////////////*********************单引号不配对
				if(bracket!=0){CString msg;
		msg.Format(_T("行号:%d\t\t括号不配对:%s"),line,newword);
	     errorArray.Add(msg);bracket=0;}//////////////////////////////小括号不配对
				
				line++;
			}

			if (condition!=COMMENTT)               //如果状态不为注释，则设置为空，准备开始下一个状态
			{   
				//if(condition!=-1);//////////////////***************************************SAVE
				condition=-1;
				newword="";
			}

			continue;                                    //返回继续执行下一次for循环
		}

		//注释
		if(read=='{' )                               
		{ commentsym++;
		if(commentsym!=0&&commentsym!=1){
				CString msg(_T("注释错误，无法继续词法分析！"));
	        errorArray.Add(msg);return;}////////////////////////*************///////////////////****************报错，然后return
			condition=COMMENTT;             //nsign设置为注释状态
			continue;                                      //下一次for循环
		}
		else if(read=='}')                        //如果遇到}，注释完成
		{
			commentsym--;
			if(commentsym!=0&&commentsym!=1){
				CString msg(_T("注释错误，无法继续词法分析！"));
	        errorArray.Add(msg);return;}////////////////////////****************报错，然后return
			condition= -1;
			continue;
		}
		else if (condition==COMMENTT)     //如果状态为注释
		{
			continue;
		}


		bool rightcondition= false;               //如果当前读入不为注释，开始正式的识别过程

		if(condition==STRR)choose='S';
		else if(is_num(read))choose='N';
		else if(is_letter(read))choose='L';
		else choose=read;
		//数字
		switch(choose){
		case 'L':
			if(condition==-1)condition=LETTERSS;
			newword+=read;           //当前字符串加上读入的字符
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
		//msg.Format(_T("行号:%d\t\t非法的字符:%s"),line,newword);
	 //    errorArray.Add(msg);///////////////////错误提示//////////错误提示
		// condition=ERRORWORD;

		newword+=read;
		CString msg;
		if(condition!=ERRORWORDD){
		//msg.Format(_T("行号:%d\t\t非法的字符:%s"),line,newword);
	    // errorArray.Add(msg);///////////////////错误提示//////////错误提示
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

	case ERRORWORDD:////////////////////////////////////////////若在标示符中，则认为标示符错误，数字错误，单个，字符错误
		
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
			if(is_key(str)){token1.kind="KEY";token1.value=newword;token1.line.Format(_T("%d"),line);tokenArray.Add(token1);}////////////////////////////**********************key加入token
			else{token1.kind="ID";token1.value=newword;tokenArray.Add(token1);}//////////////////*********************; 加入符号表，token
		}
		else{CString msg;
		msg.Format(_T("行号:%d"),line);
		msg+=_T("  非法的标示符 ");
		msg+=newword;
	     errorArray.Add(msg);}///////////////////错误提示
		break;

		
	case NUMM:
		if(!worderror){token1.kind="NUM";token1.value=newword;token1.line.Format(_T("%d"),line);tokenArray.Add(token1);}/////////num加入符号表，token
		else{CString msg;
		msg.Format(_T("行号:%d"),line);
		msg+=_T("  非法的数值常量 ");
		msg+=newword;
	     errorArray.Add(msg);}///////////////////错误提示///////////////错误提示
		break;

	case STRR:
		if(!worderror){token1.kind="STR";token1.value=newword;token1.line.Format(_T("%d"),line);tokenArray.Add(token1);}//////////////////////加入符号表，token
		else{CString msg;
		msg.Format(_T("行号:%d"),line);
		msg+=_T("  非法的字符串常量 ");
		msg+=newword;
	     errorArray.Add(msg);}///////////////////错误提示//////////////错误提示
			break;

	case SYMM:
		if(is_sym(newword)){token1.kind="SYM";token1.value=newword;token1.line.Format(_T("%d"),line);tokenArray.Add(token1);}////////////////加入符号表，token
		else{CString msg;
		msg.Format(_T("行号:%d"),line);
		msg+=_T("  非法的符号");
		msg+=newword;
	     errorArray.Add(msg);}///////////////////错误提示//////////错误提示
		break;

	case ERRORWORDD:
		CString msg;
		msg.Format(_T("行号:%d"),line);
		msg+=_T("  包含非法的字符 ");
		msg+=newword;
	     errorArray.Add(msg);///////////////////错误提示//////////错误提示
		 break;
	}
	newword="";
	worderror=false;
	wordcondition=false;
	condition=-1;
	}
}






