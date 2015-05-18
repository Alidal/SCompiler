#pragma once
#include "Global.h"
#include "Operand.h"
#include <iostream>
#include <iomanip>
#include <map>
#include <algorithm>
#include <sstream>

using namespace std;

bool isDirective(string s);
bool isDataType(string s);
bool is32Register(string s);
bool is16Register(string s);
bool is8Register(string s);
bool isSegmentRegister(string s);
bool isCommand(string s);
bool isInAlphabet(char ch);
bool isCharIdentifier(char ch);
bool isCharNumber(char ch);
bool isSingleCharacterLexem(char ch);
bool isCharLexemDivider(char ch);
bool isCharQuote(char ch);
bool isCharComment(char ch);

string stringToHex(const string input);
string intToHex(const string input, short base);
string setReversedByteSequence(const string input, short size);

string getCommandCode(string name);
string getSegmentPrefix(string name);
string getLabelSegment(string label, vector<Label> labelTable, map<string, string> assumeTable);
string getLabelOffset(string label, vector<Label> labelTable);
string getModRMByte(vector<Operand> operands);
string getSIBByte(vector<Operand> operands);
int	   getCommandSize(string name);

void   initRegNumbers();
void   initCommandBytes();
void   initSegmentReplacePrefixes();
void   initReg16Combinations();