#include "StdAfx.h"
#include"compiling.h"


//struct row
//{
//	string id;
//	int type;
//};

static int tempt_number=0;
const int CON=200;
static row* rows[CON];
static int top=0;
row* newtempt(int type)//自动生成一个标号，类型为type对应的类型
{
	stringstream ss;
	string tempt;
	ss<<"$t"<<tempt_number;
	ss>>tempt;
	row* newrow=new row;
	newrow->id=tempt;
	newrow->type=type;
	int i=CON-tempt_number-1;
	rows[i]=newrow;
	tempt_number++;
	return rows[i];
}
row* lookup(string id)//查找这个标号是不是已经存在于符号表里了。
{
	for(int i=0; i<top; i++)//查看是否在申明的变量里边
	{
		if(id==rows[i]->id)
			return rows[i];
	}
	for(int i=0; i<tempt_number; i++)//查看是否在临时变量里边
	{
		if(id==rows[CON-i-1]->id)
			return rows[i];
	}
	return NULL;
}
row* login(string id, int type)//程序的开始，遇到一个也许是新的标号，进行登录操作。
{
	row *tempt;
	tempt=lookup(id);
	if(tempt==NULL)
	{
		tempt=new row;
		tempt->id=id;
		tempt->type=type;
		rows[top]=tempt;
		top++;
		return rows[top-1];
	}
	else
	{
		//ERR10	重复申明的标识符
		MyException ex(ERR10);
		ex.addMSG(id);
		throw ex;
	}	
}

void inactive_stbl()
{

	for(int i=0; i<top; i++)//查看是否在申明的变量里边
	{
		delete rows[i];
	}
	for(int i=0; i<tempt_number; i++)//查看是否在临时变量里边
	{
		delete rows[CON-i-1];
	}
	top=0;
	tempt_number=0;
}