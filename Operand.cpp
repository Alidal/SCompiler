#include "Operand.h"


Operand::Operand(vector<Token> _operand)
{
	operand = _operand;
}

Operand::Operand()
{
}

void Operand::SetOperand(vector<Token> _operand)
{
	operand = _operand;
}

Operand::~Operand()
{
}
