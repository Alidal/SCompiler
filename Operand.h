#pragma once
#include "Global.h"
#include <iostream>
class Operand
{
public:
	Operand(vector<Token> _operand);

	OpType type;

	Token		  label;
	vector<Token> operand;
	vector<Token> address;
	~Operand();
};
