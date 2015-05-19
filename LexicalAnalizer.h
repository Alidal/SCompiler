#pragma once
#include "Global.h"
#include "Utilities.h"
#include "ExceptionProcesser.h"

#include <fstream>
#include <iostream>
#include <iomanip>

class LexicalAnalizer
{
private:
	vector<Lexem> lexems;
	vector<Token> tokens;
	vector<string> sourceCode;

	void GenerateLexemVector();
	void AnalizeLexems();
	void OutputTokens();
public:
	LexicalAnalizer() = delete;
	LexicalAnalizer(string fileName);
	vector<Token>  getTokens();
	vector<string> getSourceCode();
	~LexicalAnalizer();
};
