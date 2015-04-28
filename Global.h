#pragma once

#include <set>
#include <vector>
#include <string>

using std::string;

enum class LexType {
	USER_IDENT, COMMAND, SINGLE_SYMB, TEXT_CONST, BIN_CONST, \
	DEC_CONST, HEX_CONST, DIRECTIVE, REG32, REG16, REG8, SEG_REG, WRONG_LEX
};

enum class OpType {
	MEMORY, REGISTER, CONSTANT
};

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

using namespace std;
