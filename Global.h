#pragma once

#include <set>
#include <vector>
#include <map>
#include <string>

using namespace std;

enum class LexType {
	USER_IDENT, COMMAND, SINGLE_SYMB, TEXT_CONST, BIN_CONST, \
	DEC_CONST, HEX_CONST, DIRECTIVE, REG32, REG16, REG8, SEG_REG, WRONG_LEX
};

enum OpType {
	OPREG8, OPREG16, OPREG32, IMM, MEM, LABEL, TXT
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

struct Segment
{
	string name;
	int length;
};

struct Label
{
	string name;
	int value;
	string segName;
};

static Segment curSeg;