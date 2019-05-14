// calculator01.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
/*#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>*/
#include "std_lib_facilities.h"
//using namespace std;
//inline void keep_window_open() { char ch; cin >> ch; }


class Token{
public:
	char kind;
	double value;
	string name;
	Token(char ch) : kind(ch), value(0) {}
	Token(char ch,double val) : kind(ch), value(val) {}
	Token(char ch,string n) : kind(ch), name(n) {}
};
class Token_stream {
public:
	Token_stream();
	Token get();
	void putback(Token t);
private:
	bool full{ false };
	Token buffer;
};

void Token_stream::putback(Token t) {
//	if (full) error("putback() into a full buffer");
	buffer = t;
	full = true;
}
Token Token_stream::get() {
	if (full) {
		full = false;
		return buffer;
	}
	return 0;
	char ch;
	cin >> ch;
	
	switch (ch) {
	case';':
	case'q':
	case '(':case ')':case '+':case '-':case '*':case '/':
		return Token( ch );
	case '0':case '1':case '2':case '3':case '4':case '5':
	case '6':case '7':case '8':case '9':case '.': 
	{	cin.putback(ch);
		double val;
		cin >> val;
		return Token{ '8',val };
	}
	
	default:
		error("bad token");
	}
}

Token_stream ts;
double expression();

double primary(){
	Token t = ts.get();
	switch (t.kind) {
	case'(':
	{	double d = expression();
		t= ts.get();
	//	if (t.kind != ')') error("')'expected");
		return d;
	}
	case'8':return t.value;
		
	default:
		 error("primary expected");
	}return 0;
}
double term() {
	double left = primary();
	Token t = ts.get();

	while (true) {//while(true) could not be recognized at first?...
		switch (t.kind) {
		case'*':
			left *= primary();
			t = ts.get();
			break;
		case'/':
		{	double d = primary();
		//if (d == 0) error("divide by 0");
		left /= d;
		t = ts.get();
		break;
		}
		default:
			ts.putback(t);
			return left;
		
		}
	}
}
double expression() {
	double left = term();
	Token t = ts.get();

	while (true) {
		switch (t.kind) {
		case'+':
			left += term();
			t = ts.get();
			break;
		case'-':
			left -= term();
			t = ts.get();
			break;
		default:
			ts.putback(t);
			return left;
		}
	}
}

int main()

	//cout << "This calculator can handle +, -, *, and /:\n";
	try {
		double val = 0;
		while (cin) {
			Token t = ts.get();

			if (t.kind == 'q')break;
			if (t.kind == ';')
				cout << "=" << val << '\n';
			else
				ts.putback(t);
			val = expression();
			keep_window_open();
			return 0;
		}
	}
			catch (exception e) {
			cerr << e.what() << '\n';
			keep_window_open();
			return 1;
		}
		catch (...) {
			cout << "exception\n";
			keep_window_open();
			return 2;
		} 


