#include "StdAfx.h"
#include"compiling.h"



extern int nextstat;
extern string token; 
extern int code_index;
istream* input;
CArray<gramexp,gramexp&> gramArray;


void program();
void declarations(int signal);
void varlist(int type);
stmt* statement();
expr* arithmetic_exp();
expr* term();
expr* factor();
expr* str_exp();
bexp* bool_exp();
bexp* bterm();
bexp* bfactor();

void analyze(istream& in, ostream& output)
{
	input=&in;
	scan(*input);
	//program(P)		->	declarations(D) stmt-sequence(S)
	cout<<"analyzing is on the way"<<endl;
	program();
	print();


	return;
}

void program()
{
	if(token=="#")
	{
		MyException ex(ERR14);
		ex.addMSG(token);
		throw ex;
	}
	declarations(0);
	stmt*S=statement();
	backpatch(S->chain, nextstat);
	if(code_index!=END)
	{
		//ERR11意外的程序结束
		MyException ex(ERR11);
		ex.addMSG(token);
		throw ex;
	}
	code_index=0;
	emit("HALT","-","-","-");
	cout<<"parsing has finished successfully"<<endl;
}

void declarations(int signal)
{
	int type = code_index;
	if(code_index!=BOOL1&&code_index!=INT1&&code_index!=STR)
	{
		if(signal==0)
		{
			MyException ex(ERR13);
			throw ex;

		}
		return;
	}
	scan(*input);
	varlist(type);
	if(code_index==SEM)
	{
		scan(*input);
		declarations(1);
	}
		//else 返回空
}

void varlist(int type)
{	
	if(code_index!=ID)
	{
		//ERR6	标识符匹配错误
		MyException ex(ERR6);
		ex.addMSG(token);
		throw ex;
	}
	login(token, type);
	scan(*input);
	if(code_index==COMMA)
	{	
		scan(*input);
		varlist(type);
	}
	//else 返回空
}

stmt* statement()
{
	stmt* S0=new stmt;
	stmt* S1;
	bexp* B;
	expr* E;
	row*p;
	S0->codebegin=nextstat;
	
	switch(code_index)
	{
	case IF:
		scan(*input);
		B=bool_exp();
		if(code_index!=THEN)
		{
			//ERR5	开始符号和后跟符号错误
			MyException ex(ERR5);
			string tempt="本该是THEN的";
			ex.addMSG(tempt.append(token));
			throw ex;
		}
		scan(*input);
		backpatch(B->tc, nextstat);
		S1=statement();
		if(code_index==ELSE)
		{
			scan(*input);
			S0->chain =merge(S1->chain, nextstat);
			emit("JMP","-","-","-");
			backpatch(B->fc, nextstat);
			stmt*S2=statement();
			S0->chain=merge(S0->chain,S2->chain);
		}
		else
		{
			S0->chain=merge(B->fc, S1->chain);
		}
		if(code_index!=END)
		{
			//ERR5	开始符号和后跟符号错误
			MyException ex(ERR5);
			string tempt="本该是END的";
			ex.addMSG(tempt.append(token));
			throw ex;
		}
		scan(*input);
		break;
	case WHILE:
		scan(*input);
		B=bool_exp();
		if(code_index!=DO)
		{
			//ERR5	开始符号和后跟符号错误
			MyException ex(ERR5);
			string tempt="本该是DO的";
			ex.addMSG(tempt.append(token));
			throw ex;
		}
		scan(*input);
		S0->chain=B->fc;
		backpatch(B->tc,nextstat);
		S1=statement();
		if(code_index!=END)
		{
			//ERR5	开始符号和后跟符号错误
			MyException ex(ERR5);
			string tempt="本该是END的";
			ex.addMSG(tempt.append(token));
			throw ex;
		}
		scan(*input);
		backpatch(S1->chain, S0->codebegin);
		emit("JMP","-","-",S0->codebegin); 
		break;
	case REPEAT:
		scan(*input);
		S1=statement();
		if(code_index!=UNTIL)
		{
			//ERR5	开始符号和后跟符号错误
			MyException ex(ERR5);
			string tempt="本该是until的";
			ex.addMSG(tempt.append(token));
			throw ex;
		}
		scan(*input);
		B=bool_exp();
		backpatch(B->fc, S0->codebegin);
		S0->chain=B->tc;
		break;
	case ID:
		S0->chain=-1;
		p=lookup(token);
		if(p==NULL)
		{
			//ERR9	未申明的标识符
			MyException ex(ERR9);
			ex.addMSG(token);
			throw ex;
		}
		scan(*input);
		if(code_index!=IS)
		{
			if(code_index==EQ)
			{
				//ERR8	符号错误
				MyException ex(ERR9);
				string tempt="本应是：=的=";
				ex.addMSG(tempt);
				throw ex;
			}
			//ERR5	开始符号和后跟符号错误
			MyException ex(ERR5);
			string tempt="本应是：=的";
			ex.addMSG(tempt.append(token));
			throw ex;
		}
		scan(*input);
		switch(p->type)
		{
		case 0: 
			E=arithmetic_exp();	
			emit("MOV",E->id,"-", p->id);
			break;
		case 1:
			p=newtempt(1);
			B=bool_exp();
			backpatch (B->tc, nextstat);
			emit("MOV","TRUE","-",p->id);
			emit("JMP","-","-",nextstat+2);
			backpatch(B->fc, nextstat);
			emit("MOV","FALSE","-", p->id);
			break;
		case 2:
			E=str_exp();
			emit("MOV", E->id,"-", p->id);
			break;
		}
		break;
	default:
	//ERR5	开始符号和后跟符号错误
		MyException ex(ERR5);
		ex.addMSG(token);
		throw ex;
	}
	if(code_index==SEM)
	{
		scan(*input);
		backpatch(S0->chain, nextstat);
		S1=statement();
		S0->chain= S1->chain;
	}
	return S0;
}
expr* arithmetic_exp()
{
	expr*E1=term();
	int tempt;
	while(code_index==ADD||code_index==SUB)
	{
		tempt=code_index;
		scan(*input);
		expr*E2=term();
		if(E2->type!=INT1)
		{
			//ERR12	运算对象类型不相同
			MyException ex(ERR12);
			ex.addMSG(E2->id);
			throw ex;

		}
		if(tempt==ADD)
		{
			emit("ADD", E1->id, E2->id, E1->id);
		}
		else
		{
			emit("SUB", E1->id, E2->id, E1->id);
		}
	}
	return E1;
}


expr* term()
{
	int tempt;
	expr*E1=factor();
	while(code_index==MUL||code_index==DIV)
	{
		tempt=code_index;
		scan(*input);
		expr*E2=term();
		if(tempt==MUL)
		{
			emit("MUL", E1->id, E2->id, E1->id);
		}
		else
		{
			emit("DIV", E1->id, E2->id, E1->id);
		}
	}
	return E1;
}

expr* factor()
{

	if(code_index==LBRA) 
	{
		scan(*input);
		expr*E= arithmetic_exp();
		if(code_index!=RBRA)
		{
			//ERR7	括号匹配错误（（、）不匹配）
			MyException ex(ERR7);
			string tempt="本应是)的";
			ex.addMSG(tempt.append(token));
			throw ex;
		}
		scan(*input);
		return E;
	}
	else if(code_index==NUM)
	{
		string tempt=token;
		scan(*input);
		expr*E=new expr;
		row*p=newtempt(INT1);
		emit("MOV",tempt,"-",p->id);
		E->id=p->id;
		E->type=INT1;
		return E;
	}
	else if(code_index==ID)
	{
		string tempt=token;
		scan(*input);
		row*R=lookup(tempt);
		if(R==NULL)
		{
			//ERR9	未申明的标识符
			MyException ex(ERR9);
			ex.addMSG(R->id);
			throw ex;
		}
		if(R->type!=INT1)
		{
			//ERR12	运算对象类型不相同
			MyException ex(ERR12);
			ex.addMSG(R->id);
			throw ex;
		}
		row*p=newtempt(INT1);
		emit("MOV",tempt,"-",p->id);
		expr*E=new expr;
		E->id=p->id;
		E->type=INT1;
		return E;
	}
	else
	{
		//ERR5	开始符号和后跟符号错误
		MyException ex(ERR5);
		string tempt="本该是int类型的id或者数字的";
		ex.addMSG(tempt.append(token));
		throw ex;	
	}
}

expr* str_exp()
{
	if(code_index==STRING)
	{
		string tempt=token;
		tempt.insert(0,"'");
		tempt.append("'");
		scan(*input);
		expr* E=new expr;
		E->id=tempt;
		E->type=STR;
		return E;
	}
	else if(code_index==ID)
	{
		string tempt=token;
		scan(*input);
		row*R=lookup(tempt);
		if(R==NULL)
		{
			//ERR9	未申明的标识符
			MyException ex(ERR9);
			ex.addMSG(tempt);
			throw ex;	
		}
		if(R->type!=STR)
		{
			//ERR12	运算对象类型不相同
			MyException ex(ERR12);
			ex.addMSG(R->id);
			throw ex;	
		}
		expr* E=new expr;
		E->id=tempt;
		E->type=STR;
		return E;
	}
	else
	{
		//ERR5	开始符号和后跟符号错误
		MyException ex(ERR5);
		string tempt="本该是string类型ID或字符串的";
		ex.addMSG(tempt.append(token));
		throw ex;
	}
}

bexp* bool_exp()
{
	bexp*B1= bterm();
	bexp*B2;
	while(code_index==OR)
	{
		scan(*input);
		backpatch(B1->fc, nextstat);
		B2=bterm();
		B1->tc=merge(B1->tc,B2->tc);
		B1->fc=B2->fc;
	}
	return B1;
}

bexp* bterm()

{
	bexp*B1=bfactor();
	bexp*B2;
	while(code_index==AND)
	{
		scan(*input);
		backpatch(B1->tc, nextstat);
		B2=bfactor();
		B1->fc=merge(B1->fc, B2->fc);
		B1->tc=B2->tc;
		
	}
	return B1;
}

bexp* bfactor()
{
	bexp* B=new bexp;
	row* p;
	string tempt="";
	switch(code_index)
	{
	case TRUE1:
		scan(*input);
		B->tc=nextstat;
		B->codebegin=nextstat;
		emit("JMP","-","-",0);
	case FALSE1:
		scan(*input);
		B->fc=nextstat;
		B->codebegin=nextstat;
		emit("JMP","-","-",0);
	case ID:

		p=lookup(token);
		if(p==NULL)
		{
			//ERR9	未申明的标识符
			MyException ex(ERR9);
			ex.addMSG(token);
			throw ex;
		}
		if(p->type!=BOOL1)
		{
			goto def;
		}
		else
		{
			tempt=token;
			scan(*input);
			B->codebegin=nextstat;
			emit("JNE",token,"-",nextstat+1);
			B->tc=nextstat;
			emit("JMP","-","-",0);
			B->fc=nextstat;
			emit("JMP","-","-",0);
		}
			
	case NOT:
		{
			scan(*input);
			bexp*B1=bfactor();
			B->tc=B1->fc;
			B->fc=B1->tc;
			B->codebegin=B1->codebegin;	
		}
	case LBRA:
		{
			scan(*input);
			B=bool_exp();
			if(code_index!=RBRA)
			{
				//ERR7	括号匹配错误（（、）不匹配）
				MyException ex(ERR7);
				string tempt="本应是)的";
				ex.addMSG(tempt.append(token));
				throw ex;
			}
			scan(*input);
			break;
		}
	default:
		{
def:		expr*E1=arithmetic_exp();
			int tempt=code_index;
			scan(*input);
			if(tempt!=GRA&&tempt!=LES&&tempt!=NE&&tempt!=EQ&&tempt!=GE&&tempt!=LE)
			{
				//ERR5	开始符号和后跟符号错误
				MyException ex(ERR5);
				throw ex;
			}
			expr*E2=arithmetic_exp();
			B->codebegin=nextstat;
			B->tc=nextstat;
			string op;
			switch(tempt)
			{
			case GRA: op="JG";break;
			case LES: op="JL";break;
			case NE: op="JNE";break;
			case EQ: op="JE";break;
			case GE: op="JGE";break;
			case LE: op="JLE";break;
			}
			emit(op, E1->id, E2->id, 0);
			B->fc=nextstat;
			emit("JMP","-","-",0);
		}
	}
	return B;
}




int mode;
string token;
int par_line=-1;
int code_index=0;
int line=0;