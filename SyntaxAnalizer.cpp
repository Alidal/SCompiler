#include "SyntaxAnalizer.h"


SyntaxAnalizer::SyntaxAnalizer(vector<Token> _tokens)
{
	tokens = _tokens;
	GenerateSentencesStruct();
}

void SyntaxAnalizer::GenerateSentencesStruct()
{
	vector<Token> curRow;
	for (int i = 0; i < tokens.size() - 1; ++i)
	{
		while (i < tokens.size()-1 && tokens[i].lex.row == tokens[i + 1].lex.row)
		{
			curRow.push_back(tokens[i]);
			++i;
		}
		curRow.push_back(tokens[i]);
		sentences.push_back(Sentence(curRow));
		sentences.back().divideSentence();
		sentences.back().showSentence();
		curRow.clear();
	}
}


SyntaxAnalizer::~SyntaxAnalizer()
{
}
