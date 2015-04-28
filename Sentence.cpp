#include "Sentence.h"


Sentence::Sentence(vector<Token> _wholeSentence) : wholeSentence(_wholeSentence)
{
}

void Sentence::divideSentence()
{
	int i = 0;
	if (wholeSentence[0].lexType == LexType::USER_IDENT)
	{
		labelOrName = wholeSentence[0];
		++i;
		if (wholeSentence.size() > 1 && wholeSentence[i].lexType == LexType::SINGLE_SYMB)
			++i;
	}

	if (((wholeSentence.size() > i) && (wholeSentence[i].lexType == LexType::DIRECTIVE || wholeSentence[i].lexType == LexType::COMMAND))\
		|| (wholeSentence.size() == 1 && wholeSentence[0].lexType == LexType::COMMAND))
	{
		command = wholeSentence[i];
		++i;
	}

	vector<Token> curOperand;
	while (i < wholeSentence.size())
	{
		curOperand.clear();
		while (i < wholeSentence.size() && wholeSentence[i].lex.text != ",")
		{
			curOperand.push_back(wholeSentence[i]);
			++i;
		}
		operands.push_back(Operand(curOperand));
		++i;
	}
}

void Sentence::showSentence()
{
	cout << setw(8) << labelOrName.lex.text << " " << setw(8) << command.lex.text << " ";
	if (!operands.empty())
	{
		for (auto iter : operands)
		{
			cout << " | ";
			for (auto iter2 : iter.operand)
				cout << iter2.lex.text;
		}
	}
	cout << endl;
}

Sentence::~Sentence()
{
}
