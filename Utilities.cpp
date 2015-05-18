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

map<string, string> commandBytes;
map<string, string> segmentReplacePrefix;
map<string, string> regNumbers;
map<string, string> reg16Combinations;

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

string stringToHex(const string input)
{
	const char* const alphabet = "0123456789ABCDEF";
	size_t len = input.length();	
	string res = "";

	for (int i = 1; i < len - 1; ++i)
	{
		const unsigned char c = input[i];
		res.push_back(alphabet[c >> 4]);
		res.push_back(alphabet[c & 15]);
		res.push_back(' ');
	}

	return res;
}

void initSegmentReplacePrefixes()
{
	segmentReplacePrefix.insert(std::pair<string, string>("DS", "3E"));
	segmentReplacePrefix.insert(std::pair<string, string>("GS", "65"));
	segmentReplacePrefix.insert(std::pair<string, string>("ES", "26"));
	segmentReplacePrefix.insert(std::pair<string, string>("CS", "2E"));
	segmentReplacePrefix.insert(std::pair<string, string>("SS", "36"));
	segmentReplacePrefix.insert(std::pair<string, string>("FS", "64"));
}

void initCommandBytes()
{
	commandBytes.insert(std::pair<string, string>("NOP", "90"));
	commandBytes.insert(std::pair<string, string>("SHR_reg8_imm", "D0"));
	commandBytes.insert(std::pair<string, string>("SHR_reg16-32_imm", "D1"));
	commandBytes.insert(std::pair<string, string>("NOT_mem", "F6"));
	commandBytes.insert(std::pair<string, string>("ADC_mem_reg8", "10"));
	commandBytes.insert(std::pair<string, string>("ADC_mem_reg16-32", "11"));
	commandBytes.insert(std::pair<string, string>("SUB_reg8_mem", "2A"));
	commandBytes.insert(std::pair<string, string>("SUB_reg16-32_mem", "2B"));
	commandBytes.insert(std::pair<string, string>("JC", "72"));
	commandBytes.insert(std::pair<string, string>("JMP", "EB"));
}

void initRegNumbers()
{
	regNumbers.insert(std::pair<string, string>("EAX", "000"));
	regNumbers.insert(std::pair<string, string>("ECX", "001"));
	regNumbers.insert(std::pair<string, string>("EDX", "010"));
	regNumbers.insert(std::pair<string, string>("EBX", "011"));
	regNumbers.insert(std::pair<string, string>("EBP", "101"));
	regNumbers.insert(std::pair<string, string>("ESI", "110"));
	regNumbers.insert(std::pair<string, string>("EDI", "111"));

	regNumbers.insert(std::pair<string, string>("AX", "000"));
	regNumbers.insert(std::pair<string, string>("CX", "001"));
	regNumbers.insert(std::pair<string, string>("DX", "010"));
	regNumbers.insert(std::pair<string, string>("BX", "011"));
	regNumbers.insert(std::pair<string, string>("BP", "101"));
	regNumbers.insert(std::pair<string, string>("SI", "110"));
	regNumbers.insert(std::pair<string, string>("DI", "111"));

	regNumbers.insert(std::pair<string, string>("AL", "000"));
	regNumbers.insert(std::pair<string, string>("CL", "001"));
	regNumbers.insert(std::pair<string, string>("DL", "010"));
	regNumbers.insert(std::pair<string, string>("BL", "011"));
	regNumbers.insert(std::pair<string, string>("AH", "101"));
	regNumbers.insert(std::pair<string, string>("CH", "101"));
	regNumbers.insert(std::pair<string, string>("DH", "110"));
	regNumbers.insert(std::pair<string, string>("BH", "111"));
}

void initReg16Combinations()
{
	reg16Combinations.insert(std::pair<string, string>("BX+SI", "000"));
	reg16Combinations.insert(std::pair<string, string>("BX+DI", "001"));
	reg16Combinations.insert(std::pair<string, string>("BP+SI", "010"));
	reg16Combinations.insert(std::pair<string, string>("BP+DI", "011"));
	reg16Combinations.insert(std::pair<string, string>("SI", "100"));
	reg16Combinations.insert(std::pair<string, string>("DI", "101"));
	reg16Combinations.insert(std::pair<string, string>("BX", "111"));
}

string intToHex(const string input, short base)
{
	stringstream stream;
	string result = "";
	if(!input.empty())
	{
		stream << std::hex << stoi(input, nullptr, base);
		result = stream.str();
		transform(result.begin(), result.end(), result.begin(), ::toupper);
	}
	return result;
}

string setReversedByteSequence(const string input, short size)
{
	string temp;
	for (int i = 0; i < size*2 - input.size(); ++i)
		temp.push_back('0');
	temp += input;

	string result = "";

	for (int i = temp.size() - 2; i >= 0; i -= 2)
	{
		result.push_back(temp[i]);
		result.push_back(temp[i + 1]);
	}

	return result;
}

int getCommandSize(string name)
{
	return commandBytes.find(name)->second.size() / 2;
}

string getCommandCode(string name)
{
	return commandBytes.find(name)->second;
}

string getSegmentPrefix(string name)
{
	return segmentReplacePrefix.find(name)->second;
}

string getRegisterNumber(string name)
{
	return regNumbers.find(name)->second;
}

string get16RegistersCombination(string name)
{
	return reg16Combinations.find(name)->second;
}

string getLabelSegment(string label, vector<Label> labelTable, map<string,string> assumeTable)
{
	string fullSegName;
	for (int i = 0; i < labelTable.size(); ++i)
		if (labelTable[i].name == label)
		{
			fullSegName = labelTable[i].segName;
			break;
		}


	if (fullSegName.size() != 0)
		return assumeTable.find(fullSegName)->second;
	else
	{
		//TODO throw error "No such label"
	}
	return "";
}

string getModRMByte(vector<Operand> operands)
{
	string mod = "";
	string reg;
	string rm;
	bool isIMM = false;

	// for commands with one operand
	if (operands.size() == 1)
	{
		mod = "10";
		if(!operands[0].address.empty())
		{
			rm = "010"; //EDX-DX-DL
			switch (operands[0].address[0].lexType)
			{
			case LexType::REG32:
				if (operands[0].address[2].lexType == LexType::REG32)
					reg = "100"; //SIB
				else
					reg = getRegisterNumber(operands[0].address[0].lex.text);
			break;
			case LexType::REG16:
				if (operands[0].address[2].lexType == LexType::REG16)
				{
					for (auto op_iter : operands[0].address)
						reg += op_iter.lex.text;
					reg = get16RegistersCombination(reg);
				}
				else
					//TODO Throw error "Wrong registers pair"
				break;
			}
		}
		else
		{
		}
	}
	else //for commands with multiple operands
	{
		mod = "10";
		string destinationReg;
		string firstReg = "";
		string secondReg = "";
		bool is16Addr = false;

		for (auto iter : operands)
		{
			if (!iter.address.empty())
			{
				if (iter.address[0].lexType == LexType::REG16)
				{
					for (auto op_iter : iter.address)
						firstReg += op_iter.lex.text;

					is16Addr = true;
				}
				else
				{
					firstReg  = iter.address[0].lex.text;
					secondReg = iter.address[2].lex.text;
				}
			}
			else
			{
				if (iter.type == OPREG32 || iter.type == OPREG16)
					destinationReg = iter.operand[0].lex.text;
				else if (iter.type == IMM)
				{
					isIMM = true;
					mod = "11";
				}
			}
		}
		rm = getRegisterNumber(destinationReg);
		if (isIMM)
			reg = "101"; //for SHR command
		if (is16Addr)
			reg = get16RegistersCombination(firstReg);
		else if(!isIMM)
		{
			reg = getRegisterNumber(firstReg);
			if (!secondReg.empty())
				reg = "100"; //SIB
		}
	}

	if(!rm.empty() && !reg.empty())
		if(isIMM)
			return mod + reg + rm;
		else
			return mod + rm + reg;

	return "";
}
