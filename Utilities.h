#pragma once
#include "Global.h"

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
