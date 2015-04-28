#pragma once
#include "Global.h"
#include "Sentence.h"
#include "ExceptionProcesser.h"

#include <iomanip>

class SyntaxAnalizer
{
	vector<Sentence> sentences;
	vector<Token> tokens;

	void GenerateSentencesStruct();
public:
	SyntaxAnalizer(vector<Token> _tokens);
	~SyntaxAnalizer();
};

