#pragma once
#include "Global.h"

const char cLF = 0xA;
const char cCR = 0xD;

bool isCompilerDirective(string s);
bool isDataType(string s);
bool isRegister(string s);
bool isCommand(string s);
bool isInAlphabet(char ch);
bool isCharIdentifier(char ch);
bool isCharNumber(char ch);
bool isSingleCharacterLexem(char ch);
bool isCharLexemDivider(char ch);
bool isCharQuote(char ch);
bool isCharComment(char ch);
