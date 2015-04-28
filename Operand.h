#pragma once
#include "Global.h"

class Operand
{
	
public:
	Operand(vector<Token> _operand);
	Operand();
	vector<Token> operand;

	void SetOperand(vector<Token> _operand);
	~Operand();
};

