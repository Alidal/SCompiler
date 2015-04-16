#pragma once
#include "Global.h"
#include "Utilities.h"
#include "ExceptionProcesser.h"

#include <fstream>
#include <algorithm>
#include <iostream>
#include <iomanip>

class Lexer
{
private:
	struct Lexem
	{
		string text;
		int row;
		int column;
	};

	struct Token
	{
		Lexem lex;
		LexType lexType;
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
