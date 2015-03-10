#pragma once
#include "Utilities.h"
#include <iostream>

const string compilerDirectivesArray[] = { "END", "SEGMENT", "ENDS", "ASSUME" };
const string dataTypesArray[] = { "DB", "DW", "DD" };
const string registersArray[] = { "EAX", "ECX", "EDX", "EBX", "ESP", "EBP", "ESI", "EDI", \
								"AX", "CX", "DX", "BX", "SP", "BP", "SI", "DI", "AH", "AL", \
								"CH", "CL", "DH", "DL", "BH", "BL", "CS", "DS", "SS", "ES", "FS", "GS" };
const string commandsArray[] = { "NOP", "SHR", "NOT", "ADC", "SUB", "JC", "JMP" };

const set<string> compilerDirectives(compilerDirectivesArray, compilerDirectivesArray + 4);
const set<string> dataTypes(dataTypesArray, dataTypesArray + 3);
const set<string> registers(registersArray, registersArray + 30);
const set<string> commands(commandsArray, commandsArray + 7);
const string alphabet = "1234567890 ABCDEFGHIJKLMNOPQRSTUVWXYZ_@?$,:[]+-\'\"; " + (char)0x9;
const string identifierChars = "1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ_@?$";
const string numberChars = "1234567890";
const string singleCharLexems = ",:[]+-";
const string lexemDividers = string(1, (char)0x9) + " ";
const string quoteChars = "\'\"";
const char   commentChar = ';';

bool isCompilerDirective(string s)
{
	return compilerDirectives.find(s) != compilerDirectives.end();
}
bool isDataType(string s)
{
	return dataTypes.find(s) != dataTypes.end();
}

bool isRegister(string s)
{
	return registers.find(s) != registers.end();
}

bool isCommand(string s)
{
	return commands.find(s) != commands.end();
}

bool isInAlphabet(char ch)
{
	//cout << endl << "LOG:" << ch << " = " << numberChars.find(ch) << " - " << string::npos << endl;
	return alphabet.find(ch) != string::npos;
}

bool isCharIdentifier(char ch)
{
	return identifierChars.find(ch) != string::npos;
}

bool isCharNumber(char ch)
{
	return numberChars.find(ch) != string::npos;
}

bool isSingleCharacterLexem(char ch)
{
	return singleCharLexems.find(ch) != string::npos;
}

bool isCharLexemDivider(char ch)
{
	return lexemDividers.find(ch) != string::npos;
}

bool isCharQuote(char ch)
{
	return quoteChars.find(ch) != string::npos;
}

bool isCharComment(char ch)
{
	return ch == commentChar;
}