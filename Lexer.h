#pragma once
#include "Global.h"
#include "Utilities.h"

#include <fstream>
#include <algorithm>
#include <map>
#include <iostream>

class Lexer
{
private:
	enum class LexType {USER_IDENT, COMMAND, SINGLE_SYMB, TEXT_CONST, DATA_TYPE, BIN_CONST,\
						DEC_CONST, HEX_CONST, DIRECTIVE, REG32, REG16, REG8, SEG_REG};
	vector<string> _lexems;
	map<string, LexType> _tokens;
	vector<string> _sourceCode;
	
	void GenerateLexemVector();
	void AnalizeLexems();
	void OutputTokens();
public:
	Lexer() = delete;
	Lexer(string fileName);
	~Lexer();
};
