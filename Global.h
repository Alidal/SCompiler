#pragma once

#include <set>
#include <vector>
#include <string>

enum class LexType {
	USER_IDENT, COMMAND, SINGLE_SYMB, TEXT_CONST, DATA_TYPE, BIN_CONST, \
	DEC_CONST, HEX_CONST, DIRECTIVE, REG32, REG16, REG8, SEG_REG, WRONG_LEX
};

using namespace std;
