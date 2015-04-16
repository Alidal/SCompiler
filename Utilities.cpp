#pragma once
#include "Utilities.h"

const string directivesArray[] = { "END", "SEGMENT", "ENDS", "ASSUME", "DB", "DW", "DD" };
const string registers32Array[] = { "EAX", "ECX", "EDX", "EBX", "ESP", "EBP", "ESI", "EDI" };
const string registers16Array[] = { "AX", "CX", "DX", "BX", "SP", "BP", "SI", "DI" }; 
const string registers8Array[] = { "AH", "AL", "CH", "CL", "DH", "DL", "BH", "BL" };
const string segmentRegistersArray[] = { "CS", "DS", "SS", "ES", "FS", "GS" };
const string commandsArray[] = { "NOP", "SHR", "NOT", "ADC", "SUB", "JC", "JMP" };

const set<string> directives(directivesArray, directivesArray + 7);
const set<string> registers32(registers32Array, registers32Array + 8);
const set<string> registers16(registers16Array, registers16Array + 8);
const set<string> registers8(registers8Array, registers8Array + 8);
const set<string> segmentRegisters(segmentRegistersArray, segmentRegistersArray + 6);
const set<string> commands(commandsArray, commandsArray + 7);
const string alphabet = string("1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ_@?$,:()[]+-\'\"; ") + (char)0x9;
const string identifierChars = "1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ_@?$";
const string numberChars = "1234567890";
const string singleCharLexems = ",:()[]+-";
const string lexemDividers = string(1, (char)0x9) + " ";
const string quoteChars = "\'\"";
const char   commentChar = ';';

bool isDirective(string s)
{
	return directives.find(s) != directives.end();
}

bool is32Register(string s)
{
	return registers32.find(s) != registers32.end();
}

bool is16Register(string s)
{
	return registers16.find(s) != registers16.end();
}

bool is8Register(string s)
{
	return registers8.find(s) != registers8.end();
}

bool isSegmentRegister(string s)
{
	return segmentRegisters.find(s) != segmentRegisters.end();
}

bool isCommand(string s)
{
	return commands.find(s) != commands.end();
}

bool isInAlphabet(char ch)
{
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