

#include "StdAfx.h"
#include"compiling.h"


extern int mode;
extern string token;
extern int par_line;
extern istream glo_input;
extern int code_index;

const char COL_CHAR[]="a0><=,'{};:+-*/() ";

const int DFA[][18]={
	{1,2,3,4,5,6,7,8,-3,9,10,11,12,13,14,15,16,0},
	{1,1},
	{-1,2},
	{0,0,0,0,17},
	{0,0,18,0,19},
	{0},
	{0},
	{7,7,7,7,7,7,0,7,7,7,7,7,7,7,7,7,7,7},
	{8,8,8,8,8,8,8,8,0,8,8,8,8,8,8,8,8,8},
	{0},
	{-4,-4,-4,-4,20, -4,-4,-4,-4,-4, -4,-4,-4,-4,-4, -4,-4,0},
	{0},
	{0},
	{0},
	{0},
	{0},
	{0},
	{0},
	{0},
	{0},
	{0}
};

bool ignoreCommen(istream &input);
bool getString(istream&input);
int col(char c);
int search_table(string word);
int search_code_index(string word);
static string buf="";
static int i=0;
static 	string word="";

bool scan(istream &input)
{
	bool tempt=parsing(input);
	if(mode>=err1)
	{
		MyException ex(mode-err1);
		ex.addMSG(token);
		throw ex;
	}
	if(mode==num)
	{
		code_index=NUM;
	}
	else if(mode==id)
	{
		code_index=ID;
	}
	else if(mode==str)
	{
		code_index=STRING;
	}
	else if(mode==sym||mode==key)
	{
		search_code_index(token);
	}
}
bool parsing(istream &input)
//1.parsing一次处理一行，但是每次调用parsing只返回一个word。
//2.parsing处理好的一行被存储在一个token队列里边
//3.调用parsing时如果token队列不为空，则只从token队列里读取数据，否则则再处理一行 
//以上只是一种可能的实现，只是配合之前做了那么多的一个函数，不一定之后一定执行，但返回值是固定的。
{
	//istream input=*glo_input;
	while(buf[i]==' '||buf[i]==9)i++;
	while(buf[i]=='\0')
	{
		if(!getline((input), buf))
		{
			token="#";
			mode=endd;
			code_index=END;
			i=0;
			buf="";
			word="";
			return false;

		}
		i=0;
		par_line++;
		while(buf[i]==' '||buf[i]==9)i++;
	}
	int cur_stat=0;
	int next_stat=0;
	word="";
	
	while((next_stat=DFA[cur_stat][col(buf[i])]))
	{
		cur_stat=next_stat;
		if(cur_stat==7)
		{
			i++;
			return getString(input);
		}
		if(cur_stat==8)
		{
			i++;
			return ignoreCommen(input);//调用函数来去除所有注释
		}
		word+=buf[i];
		if(next_stat<0)
		{
			token=word;
			mode=err1-next_stat-1;
			return true;
		}
		if(buf[++i]=='\0')
		{
			break;
		}
	}
	token=word;
	//接下来需要确定究竟是"KEY","SYM","ID","NUM","STR"的哪一个
	switch(cur_stat)
	{
	case 0: return scan(input);//说明整行的都是空格。
	case 7: mode=str;break;
	case 2: mode=num;break;
	case 1: mode=search_table(word);break;
	default:
		mode=sym;
	}
	return true;
}
bool getString(istream &input)
{
	string word="";
	while(buf[i]!='\'')
	{
		word+=buf[i];
		i++;
		if(buf[i]=='\0')
		{
			MyException ex(ERR2);
			string tempt="'";
			tempt.append(word);
			ex.addMSG(tempt);
			throw ex;
		}
	}
	token=word;
	i++;
	mode=str;
	return true;
}
bool ignoreCommen(istream &input)
{
	string word="";
	while(buf[i]!='}')
	{
		word+=buf[i];
		i++;
		if(buf[i]=='\0')break;
	}
	if(buf[i]=='}')
	//出现注释结束，应该要返回下一个token
	{
		i++;
		return scan(input);
	}
	word.append("\n\t");
	while(getline(input, buf))
	{
		par_line++;
		i=0;
		while(buf[i]!='}')
		{
			if(buf[i]=='\0')break;
			i++;
		}
		if(buf[i]=='}')
		//出现注释结束，应该要返回下一个token
		{
			i++;
			return scan(input);
		}
		word.append(buf);
		word.append("\n\t");
	}
	MyException ex(ERR3);
	string tempt="{";
	tempt.append(word);
	ex.addMSG(tempt);
	throw ex;
}
int col(char c)
{
	if((c<='Z'&&c>='A')||(c<='z'&&c>='a'))
	{
		c='a';
	}
	if(c>='0'&&c<='9')
	{
		c='0';
	}
	if(c==9)c=' ';
	for(int i=0;i<18;i++)
	{
		if(c==COL_CHAR[i])return i;
	}
	MyException ex(ERR1);
	ex.addMSG(word+c);
	throw ex;

}
int search_table(string word)
{
	for(int i=0; i<18;i++)
	{
		if(word==KEY[i])
			return key;
	}
	return id;
}

int search_code_index(string word)
{
	for(int i=0; i<34;i++)
	{
		if(word==CODES[i])
		{code_index=i;
			return i;
		}
	}
	return -1;
}