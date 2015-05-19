#pragma once
#include "Global.h"
#include <iostream>
#include <iomanip>
#include "Utilities.h"
#include "ExceptionProcesser.h"
#include "Operand.h"

class Sentence
{
	vector<Token>		wholeSentence;
	vector<Segment>		&segTable;
	vector<Label>		&labelTable;
	map<string, string> &assumeTable;

	Token			labelOrName;
	Token		    command;
	vector<Operand> operands;
	int    sentenceSize;
	int	   curOffset;
	int	   displacepmentSize;
	string sentenceSegment;

	///////////////////
	string commandCode;
	string modRM;
	string byteSIB;
	string segChangePref;
	string addrModeChangePref_Operand;
	string addrModeChangePref_Address;
	string imm;
	string displacepment;
	string jmpOffset;
	///////////////////

	string generateCommandWithOpType(string);
	void   updateLabelAndSegmentTables(int &curGlobalOffset);
public:
	Sentence(vector<Token> _wholeSentence, vector<Segment> &_segTable, vector<Label> &_labelTable, map<string, string> &_assumeTable);

	void divideSentence();
	void generateSentenceAttributes(int &curGlobalOffset);
	void generateJumpOpcode();
	void showSentence();

	~Sentence();
};
