#pragma once
#include "Global.h"
#include "Utilities.h"
#include <fstream>
#include <cctype>
#include <iostream>

class Lexer
{
private:
	enum class lexTypes {USER_IDENT, COMMAND_IDENT, ONE_SYMB};
	vector<string> _lexemas;
	string _sourceCode;
	
	void GenerateLexemVector();
public:
	Lexer() = delete;
	Lexer(string fileName);
	~Lexer();
};
