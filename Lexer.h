#pragma once
#include "Global.h"
#include "Utilities.h"
#include "ExceptionProcesser.h"

#include <fstream>
#include <iostream>
#include <iomanip>

class Lexer
{
private:
	vector<Lexem> lexems;
	vector<Token> tokens;
	vector<string> sourceCode;

	ErrInfo err;
	
	void GenerateLexemVector();
	void AnalizeLexems();
	void OutputTokens();
public:
	Lexer() = delete;
	Lexer(string fileName);
	vector<Token> getTokens();
	~Lexer();
};
