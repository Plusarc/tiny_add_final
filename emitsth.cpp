#include "StdAfx.h"
#include"compiling.h"

extern CArray<gramexp,gramexp&> gramArray;

struct buff
{
	int lineNumber;
	string op;
	string s1;
	string s2;
	string d;
	buff* next;
};
buff* buffs[100];
int nextstat =0;

void printline(int n)
{
	buff *p = buffs[n];
	cout<<n<<"\t"<<p->op<<"\t"<<p->s1<<"\t"<<p->s2<<"\t"<<p->d<<endl;
}

void emit(const string &e1,const string &e2, const string &e3, const string &e4)
{
	buff *b=new buff;
	b->lineNumber=nextstat;;
	b->op=e1;
	b->s1=e2;
	b->s2=e3;
	b->d=e4;
	b->next=NULL;
	buffs[nextstat]=b;
	nextstat++;
	printline(nextstat-1);
	return;
}
void emit(const string &e1,const string &e2, const string &e3, const int &adr)//专门用于goto语句的语句
{
	buff*b=new buff;
	stringstream ss;
	string tempt;
	ss<<adr;
	ss>>tempt;
	b->lineNumber=nextstat;
	b->op=e1;
	b->s1=e2;
	b->s2=e3;
	b->d=tempt;
	b->next=NULL;
	buffs[nextstat]=b;
	nextstat++;
	printline(nextstat-1);
	return;
}
void backpatch(int needtolink,int adr)//把后一个地址回填到前一个地址链表的对应跳转位置
{
	if(needtolink==-1)return;
	stringstream ss;
	string str;
	ss<<adr;
	ss>>str;
	buff* tempt=buffs[needtolink];
	do
	{
		tempt->d=str;
		printline(tempt->lineNumber);
		tempt=tempt->next;
	}
	while(tempt!=NULL);
	return;
}
int merge(int needtolink,int link)//把第二链表尾巴和第一链表头相连，返回链表头
{
	if(link==-1)return needtolink;
	buff* tail;
	buff* head;
	head=buffs[link];
	tail=buffs[needtolink];
	while(head->next!=NULL)head=head->next;
	head->next=buffs[needtolink];
	return link;
}



void print()
{
	buff*p;
	for(int i=0 ; i<nextstat; i++)
	{
		p=buffs[i];
		cout<<i<<"\t"<<p->op<<"\t"<<p->s1<<"\t"<<p->s2<<"\t"<<p->d<<endl;

	gramexp y1;
	
	y1.line.Format(_T("%d"), i);
	y1.op=p->op.c_str();
	y1.s1=p->s1.c_str();
	y1.s2=p->s2.c_str();
	y1.s0=p->d.c_str();
	gramArray.Add(y1);

	}
}

void inactive_emit()
{
	for(int i=0 ; i<nextstat; i++)
	{
		delete buffs[i];
	}
	nextstat=0;
}