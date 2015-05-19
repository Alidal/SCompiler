#include "SyntaxAnalizer.h"

SyntaxAnalizer::SyntaxAnalizer(vector<Token> _tokens, vector<string> _codeSource) :
	tokens(_tokens),
	codeSource(_codeSource)
{
	initCommandBytes();
	initSegmentReplacePrefixes();
	initRegNumbers();
	initReg16Combinations();

	GenerateSentencesStruct();
	GenerateJumpOpcodes();
	for (auto iter : sentences)
		iter.showSentence();

	ShowLabelTable();
	ShowSegTable();
}

void SyntaxAnalizer::GenerateSentencesStruct()
{
	vector<Token> curRow;
	int rowIter = 0;
	int curOffset = 0;
	for (int i = 0; i < tokens.size() - 1; ++i)
	{
		err.codeRow = codeSource[rowIter + 1];
		err.row = rowIter + 1;
		err.column = 1;

		while (i < tokens.size() - 1 && tokens[i].lex.row == tokens[i + 1].lex.row)
		{
			curRow.push_back(tokens[i]);
			++i;
		}
		curRow.push_back(tokens[i]);
		sentences.push_back(Sentence(curRow,segTable,labelTable,assumeTable));
		sentences.back().divideSentence();
		sentences.back().generateSentenceAttributes(curOffset);
		curRow.clear();
		++rowIter;
	}
}

void SyntaxAnalizer::GenerateJumpOpcodes()
{
	for (auto &iter : sentences)
		iter.generateJumpOpcode();
}


void SyntaxAnalizer::ShowLabelTable()
{
	cout << endl << setw(8) << "NAME" << setw(8) << "VALUE" << setw(16) << "SEGMENT NAME" << endl;
	for (auto iter : labelTable)
		cout << setfill(' ') << setw(8) << iter.name << setw(4) << " " << setfill('0') << setw(4) \
			 << intToHex(to_string(iter.value), 10) << setfill(' ') << setw(16) << iter.segName << endl;
}

void SyntaxAnalizer::ShowSegTable()
{
	cout << endl << setw(8) << "NAME" << setw(10) << "LENGTH" << endl;
	for (auto iter : segTable)
		cout << setw(8) << iter.name << setw(6) << " " << setfill('0') << setw(4) << intToHex(to_string(iter.length), 10) << setfill(' ') << endl;
}

SyntaxAnalizer::~SyntaxAnalizer()
{
}