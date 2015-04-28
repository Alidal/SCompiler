#pragma once
#include "Global.h"
#include <iostream>
#include <iomanip>
#include "Operand.h"

class Sentence
{
	vector<Token> wholeSentence;
	int			  sentenceSize;

	Token			labelOrName;
	Token		    command;
	vector<Operand> operands;
public:
	Sentence(vector<Token> _wholeSentence);

	void divideSentence();
	void showSentence();

	~Sentence();
};
