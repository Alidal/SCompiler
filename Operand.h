#pragma once
#include "Global.h"
#include <iostream>
class Operand
{
public:
	Operand(vector<Token> _operand);

	OpType type;

	vector<Token> operand;
	vector<Token> address;
	~Operand();
};
