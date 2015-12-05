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
row* newtempt(int type)//�Զ�����һ����ţ�����Ϊtype��Ӧ������
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
row* lookup(string id)//�����������ǲ����Ѿ������ڷ��ű����ˡ�
{
	for(int i=0; i<top; i++)//�鿴�Ƿ��������ı������
	{
		if(id==rows[i]->id)
			return rows[i];
	}
	for(int i=0; i<tempt_number; i++)//�鿴�Ƿ�����ʱ�������
	{
		if(id==rows[CON-i-1]->id)
			return rows[i];
	}
	return NULL;
}
row* login(string id, int type)//����Ŀ�ʼ������һ��Ҳ�����µı�ţ����е�¼������
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
		//ERR10	�ظ������ı�ʶ��
		MyException ex(ERR10);
		ex.addMSG(id);
		throw ex;
	}	
}

void inactive_stbl()
{

	for(int i=0; i<top; i++)//�鿴�Ƿ��������ı������
	{
		delete rows[i];
	}
	for(int i=0; i<tempt_number; i++)//�鿴�Ƿ�����ʱ�������
	{
		delete rows[CON-i-1];
	}
	top=0;
	tempt_number=0;
}