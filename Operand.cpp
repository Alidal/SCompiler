#include "Operand.h"

Operand::Operand(vector<Token> _operand)
{
	operand = _operand;

	if (operand.size() == 1)
	{
		if (operand[0].lexType == LexType::REG32)
			type = OpType::OPREG32;
		else if (operand[0].lexType == LexType::REG16)
			type = OpType::OPREG16;
		else if (operand[0].lexType == LexType::REG8)
			type = OpType::OPREG8;
		else if (operand[0].lexType == LexType::HEX_CONST || operand[0].lexType == LexType::BIN_CONST || operand[0].lexType == LexType::DEC_CONST)
			type = OpType::IMM;
		else if (operand[0].lexType == LexType::USER_IDENT)
			type = OpType::LABEL;
		else if (operand[0].lexType == LexType::TEXT_CONST)
			type = OpType::TXT;
	}
	else
	{
		type = OpType::MEM;
		int i = 0;
		while (i < operand.size() && operand[i].lex.text != "[")
			++i;
		++i;
		while (i < operand.size() && operand[i].lex.text != "]")
		{
			address.push_back(operand[i]);
			++i;
		}
	}
}

Operand::~Operand()
{
}