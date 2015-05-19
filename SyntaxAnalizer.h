#pragma once
#include "Global.h"
#include "Sentence.h"
#include "ExceptionProcesser.h"
#include <iomanip>

class SyntaxAnalizer
{
	vector<Sentence> sentences;
	vector<Token>	 tokens;
	vector<string>	 codeSource;

	vector<Segment>		segTable;
	vector<Label>		labelTable;
	map<string, string> assumeTable;

	void GenerateSentencesStruct();
	void GenerateJumpOpcodes();
	void ShowLabelTable();
	void ShowSegTable();
public:
	SyntaxAnalizer(vector<Token> _tokens, vector<string> _codeSource);
	~SyntaxAnalizer();
};
