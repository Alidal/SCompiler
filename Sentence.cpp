#include "Sentence.h"

Sentence::Sentence(vector<Token> _wholeSentence, vector<Segment> &_segTable, vector<Label> &_labelTable, map<string, string> &_assumeTable):\
		wholeSentence(_wholeSentence),
		segTable(_segTable),
		labelTable(_labelTable),
		assumeTable(_assumeTable)
{
	command.lex.text = "";
	labelOrName.lex.text = "";
	commandCode = "";
	modRM = "";
	byteSIB = "";
	segChangePref = "";
	addrModeChangePref_Operand = "";
	addrModeChangePref_Address = "";
	imm = "";
	displacepment = "";
}

string Sentence::generateCommandWithOpType(string command)
{
	for (auto iter : operands)
	{
		if (iter.type == OPREG8)
			command += "_reg8";
		else if (iter.type == OPREG16 || iter.type == OPREG32)
			command += "_reg16-32";
		else if (iter.type == MEM)
			command += "_mem";
		else if (iter.type == IMM)
			command += "_imm";
	}
	return command;
}

void Sentence::divideSentence()
{
	int i = 0;
	if (wholeSentence[0].lexType == LexType::USER_IDENT)
	{
		labelOrName = wholeSentence[0];
		++i;
		if (wholeSentence.size() > 1 && wholeSentence[i].lexType == LexType::SINGLE_SYMB)
			++i;
	}

	if (((wholeSentence.size() > i) && (wholeSentence[i].lexType == LexType::DIRECTIVE || wholeSentence[i].lexType == LexType::COMMAND))\
		|| (wholeSentence.size() == 1 && wholeSentence[0].lexType == LexType::COMMAND))
	{
		command = wholeSentence[i];
		++i;
	}

	vector<Token> curOperand;
	while (i < wholeSentence.size())
	{
		curOperand.clear();
		while (i < wholeSentence.size() && wholeSentence[i].lex.text != ",")
		{
			curOperand.push_back(wholeSentence[i]);
			++i;
		}
		operands.push_back(Operand(curOperand));
		++i;
	}
}

void Sentence::updateLabelAndSegmentTables(int &curGlobalOffset)
{
	Label tempLabel;
	tempLabel.value = 0;

	if (command.lex.text != "SEGMENT" && command.lex.text != "ENDS" && labelOrName.lex.text != "" \
	&& (command.lex.text == "" || isDirective(command.lex.text)))
	{
		//check repeating labels in table
		for (auto l_iter : labelTable)
			if (l_iter.name == labelOrName.lex.text)
			{
				tempLabel.value = -1;
				break;
			}

		if (tempLabel.value != -1)
		{
			tempLabel.name = labelOrName.lex.text;
			tempLabel.value = curGlobalOffset;
			tempLabel.segName = curSeg.name;

			labelTable.push_back(tempLabel);
		}
	}

	if (command.lex.text == "SEGMENT")
	{
		curSeg.name = labelOrName.lex.text;
		sentenceSegment = curSeg.name;
	}
	else if (command.lex.text == "ENDS")
	{
		curSeg.length = curGlobalOffset;
		segTable.push_back(curSeg);
		curSeg.name = "";
		curGlobalOffset = 0;
	}
}

void Sentence::generateSentenceAttributes(int &curGlobalOffset)
{
	
	sentenceSize = 0;
	if (command.lex.text == "SEGMENT" || command.lex.text == "ENDS")
	{}
	else if (command.lex.text == "ASSUME")
	{
		for (auto iter : operands)
			assumeTable.insert(std::pair<string, string>(iter.operand[2].lex.text, iter.operand[0].lex.text));
	}
	else if (command.lex.text == "DD")
		sentenceSize = 4;
	else if (command.lex.text == "DW")
		sentenceSize = 2;
	else if (command.lex.text == "DB")
	{
		if (operands.size() != 0 && operands[0].type != TXT)
			sentenceSize = 1;
	}
	else if (command.lex.text != "")
	{
		commandCode   = getCommandCode(generateCommandWithOpType(command.lex.text));
		sentenceSize += getCommandSize(generateCommandWithOpType(command.lex.text));
	}
	
	for (auto iter : operands)
	{
		if (iter.type == TXT)
		{
			sentenceSize += iter.operand[0].lex.text.size() - 2; //text constant size - 2 quotes
			imm = stringToHex(iter.operand[0].lex.text);
		}
		else if (iter.type == OPREG16 || iter.type == OPREG32)
			++sentenceSize; // addr mode change pref
		else if (iter.type == IMM)
		{
			if(command.lex.text != "SHR")
				switch (iter.operand[0].lexType)
				{
				case LexType::BIN_CONST:
					imm = intToHex(iter.operand[0].lex.text, 2);
					break;
				case LexType::DEC_CONST:
					imm = intToHex(iter.operand[0].lex.text, 10);
					break;
				case LexType::HEX_CONST:
					imm = setReversedByteSequence(iter.operand[0].lex.text, sentenceSize); //x32
					break;
				default:
					break;
				}
				
		}
		else if (iter.type == MEM)
		{
			//check segment change pref
			for (int i = 0; i < iter.operand.size(); ++i)
			{
				if (!curSeg.name.empty() && iter.operand[i].lexType == LexType::SEG_REG && iter.operand[i + 1].lex.text == ":")
				{
					for(auto label_iter : labelTable)
						if (label_iter.name == iter.operand[i+2].lex.text && label_iter.segName == getLabelSegment(iter.operand[i + 2].lex.text, labelTable,assumeTable))
						{
							segChangePref = getSegmentPrefix(iter.operand[i].lex.text);
						}
						else
						{
							//TODO Throw error "WRONG SEGMENT FOR VARIABLE"
						}
				}

				else if (iter.operand[i].lexType == LexType::USER_IDENT)
				{
					string labelSeg = getLabelSegment(iter.operand[i].lex.text, labelTable, assumeTable);
					if ((labelSeg == "DS" && iter.address[0].lex.text == "BP") || \
						(labelSeg == "SS" && iter.address[0].lex.text != "BP") || \
						(labelSeg != "DS" && labelSeg != ""))
					{
						segChangePref = getSegmentPrefix(labelSeg);
					}
				}
			}
			//end checking segment change prefix

			//check addr mode change prefix
			for (auto iter : operands)
			{
				if (!iter.address.empty()) //for address
					for (auto op_iter : iter.address)
						if (op_iter.lexType == LexType::REG32)
						{
							++sentenceSize;
							addrModeChangePref_Address = "67|";
						}
				if(iter.type == OPREG32) //for operands
				{
					++sentenceSize;
					addrModeChangePref_Operand = "66|";
				}
			}
			//end checking addr mode change prefix
		}
	}

	//check byte mod r/m
	if (!operands.empty() && command.lex.text != "ASSUME")
		modRM = intToHex(getModRMByte(operands), 2);
		//modRM = getModRMByte(operands);
	//end checking byte mod r/m

	if (!segChangePref.empty())
	{
		++sentenceSize;
		segChangePref += ":";
	}
	//end segment change pref

	sentenceSegment = curSeg.name;
	curOffset = curGlobalOffset;
	updateLabelAndSegmentTables(curGlobalOffset);

	curGlobalOffset += sentenceSize;
}

void Sentence::showSentence()
{
	if (!sentenceSegment.empty())
		cout << setfill('0') << setw(4) << intToHex(to_string(curOffset), 10) << setfill(' ');

	if(!segChangePref.empty())
		cout << setw(4) << segChangePref;
	if (!addrModeChangePref_Address.empty())
		cout << setw(4) << addrModeChangePref_Address;
	if (!addrModeChangePref_Operand.empty())
		cout << setw(4) << addrModeChangePref_Operand;
	if (!commandCode.empty())
		cout << setw(3) << commandCode;

	if (!modRM.empty())
		cout << setw(3) << modRM;

	for (int i = 0; i < imm.size(); ++i)
	{
		if (i % 21 == 0 && i != 0)
		{
			cout << endl;
			cout << setw(5) << " ";
		}
		else if(i == 0)
			cout << " ";
		cout << imm[i];
	}

	cout << " " << labelOrName.lex.text << " " << command.lex.text << " ";

	if (!operands.empty())
	{
		for (int i = 0; i < operands.size(); ++i)
		{
			for (auto iter : operands[i].operand)
			{
				cout << iter.lex.text;

				switch (iter.lexType)
				{
				case LexType::BIN_CONST:
					cout << "B";
				break;
				case LexType::HEX_CONST:
					cout << "H";
					break;

				default:
					break;
				}
			}
			if (i < operands.size() - 1)
				cout << ",";
		}
	}
	cout << endl;
}

Sentence::~Sentence()
{
}