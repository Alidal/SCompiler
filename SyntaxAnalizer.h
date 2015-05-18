#pragma once
#include "Global.h"
#include "Sentence.h"
#include <iomanip>

class SyntaxAnalizer
{
	vector<Sentence> sentences;
	vector<Token>	 tokens;

	vector<Segment>		segTable;
	vector<Label>		labelTable;
	map<string, string> assumeTable;

	void GenerateSentencesStruct();
	void ShowLabelTable();
	void ShowSegTable();
public:
	SyntaxAnalizer(vector<Token> _tokens);
	~SyntaxAnalizer();
};
