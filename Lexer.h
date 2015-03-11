#pragma once
#include "Global.h"
#include "Utilities.h"
#include "ExceptionProcesser.h"

#include <fstream>
#include <algorithm>
#include <map>
#include <iostream>

struct Token
{
	string lexem;
	LexType lexType;
	int row;
	int colomn;
};
class Lexer
{
private:
	struct Lexem
	{
		string lexem;
		int row;
		int colomn;
	};

	vector<Lexem> _lexems;
	vector<Token> _tokens;
	vector<string> _sourceCode;

	ErrInfo err;
	
	void GenerateLexemVector();
	void AnalizeLexems();
	void OutputTokens();
public:
	Lexer() = delete;
	Lexer(string fileName);
	~Lexer();
};
