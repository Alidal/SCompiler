#include "Lexer.h"


Lexer::Lexer(string fileName)
{
	ifstream sourceFile(fileName);
	if (sourceFile.is_open())
	{
		string buf;
		while (getline(sourceFile, buf))
			_sourceCode.push_back(buf);

		sourceFile.close();

		bool isQuote = false;
		for (auto &iter : _sourceCode)
		{
			int i = 0;
			while (i < iter.length())
			{
				if (isCharQuote(iter[i]) && !isQuote)
					isQuote = true;
				else if (isCharQuote(iter[i]) && isQuote)
					isQuote = false;

				if (!isQuote)
					iter[i] = toupper(iter[i]);
				++i;
			}
			isQuote = false;
		}
		/*for (auto &i : _sourceCode)
			transform(i.begin(), i.end(), i.begin(), ::toupper);*/
		
		GenerateLexemVector();
		AnalizeLexems();
		OutputTokens();
	}
	else
	{
		ERROR << "File can\'t be opened. Check source file name.";
		exit;
	}
}

void Lexer::GenerateLexemVector()
{
	int i;
	Lexem buf;
	buf.row = 0;
	buf.colomn = 1;
	for (auto curRow : _sourceCode)
	{
		i = 0;
		buf.lexem.clear();
		++buf.row;

		while (i < curRow.length())
		{
			if (!isInAlphabet(curRow[i]))
			{
				err.colomn = buf.colomn;
				err.row = buf.row;
				err.sourceRow = _sourceCode[buf.row - 1];
				err.errText = "Wrong character";
				ERROR << err;

				if (!buf.lexem.empty())
					_lexems.push_back(buf);
				
				buf.colomn = i + 1;
				buf.lexem.clear();
				++i;
			}
			else if (isCharLexemDivider(curRow[i]))
			{
				if (!buf.lexem.empty())
					_lexems.push_back(buf);

				buf.colomn = i + 1;
				buf.lexem.clear();
				++i;
			}
			else if (isSingleCharacterLexem(curRow[i]))
			{
				_lexems.push_back(buf);
				buf.colomn = i + 1;
				buf.lexem.clear();

				buf.lexem += curRow[i];
				_lexems.push_back(buf);
				buf.colomn = i + 1;
				buf.lexem.clear();
				++i;
			}
			else if (isCharQuote(curRow[i]))
			{
				buf.lexem += curRow[i];
				++i;
				while (i < curRow.length() && !isCharQuote(curRow[i]))
				{
					buf.lexem += curRow[i];
					++i;
				}

				if (i == curRow.length())
				{
					err.colomn = buf.colomn;
					err.row = buf.row;
					err.sourceRow = _sourceCode[buf.row - 1];
					err.errText = "No close quote";
					ERROR << err;
				}
				else
					buf.lexem += curRow[i];

				_lexems.push_back(buf);
				buf.colomn = i + 1;
				buf.lexem.clear();
				++i;
				
			}
			else if (isCharComment(curRow[i]))
			{
				if (!buf.lexem.empty())
					_lexems.push_back(buf);
				buf.colomn = i + 1;
				//TODO Maybe add comments
				i = curRow.length();
			}
			else
			{
				buf.lexem += curRow[i];
				++i;
			}
		}

		if (!buf.lexem.empty())
			_lexems.push_back(buf);
		buf.colomn = i + 1;

	}
}

void Lexer::AnalizeLexems()
{
	Token temp;
	for (auto iter : _lexems)
	{
		temp.lexem = iter.lexem;
		temp.row = iter.row;
		temp.colomn = iter.colomn;

		if (isCommand(iter.lexem))
			temp.lexType = LexType::COMMAND;
		else if (isDataType(iter.lexem))
			temp.lexType = LexType::DATA_TYPE;
		else if (is32Register(iter.lexem))
			temp.lexType = LexType::REG32;
		else if (is16Register(iter.lexem))
			temp.lexType = LexType::REG16;
		else if (is8Register(iter.lexem))
			temp.lexType = LexType::REG8;
		else if (isSegmentRegister(iter.lexem))
			temp.lexType = LexType::SEG_REG;
		else if (isDirective(iter.lexem))
			temp.lexType = LexType::DIRECTIVE;
		else if (isCharQuote(iter.lexem[0]) && isCharQuote(iter.lexem[iter.lexem.length() - 1]))
			temp.lexType = LexType::TEXT_CONST;
		else if (isCharQuote(iter.lexem[0]) && !isCharQuote(iter.lexem[iter.lexem.length() - 1])) //TODO Try to optimize
			temp.lexType = LexType::WRONG_LEX;
		else if (isCharNumber(iter.lexem[0]))
		{
			string::size_type sz = 0;
			int base = 10;

			if (iter.lexem[iter.lexem.length() - 1] == 'B')
			{
				temp.lexType = LexType::BIN_CONST;
				base = 2;
			}
			else if (iter.lexem[iter.lexem.length() - 1] == 'H')
			{
				temp.lexType = LexType::HEX_CONST;
				base = 16;
			}
			else if (iter.lexem[iter.lexem.length() - 1] == 'D' || isCharNumber(iter.lexem[iter.lexem.length() - 1]))
				temp.lexType = LexType::DEC_CONST;

			if (!isCharNumber(iter.lexem[iter.lexem.length() - 1]))
				iter.lexem.pop_back();

			stoll(iter.lexem, &sz, base); //TODO Fix numbers check
			//cout << "Base: " << base << " : " << iter.lexem << " = " << stoi(iter.lexem, &sz, base) << " : sz = " << sz << endl;
			if (sz == iter.lexem.length() && (temp.lexType != LexType::HEX_CONST && !isCharNumber(iter.lexem[iter.lexem.length() - 1])))
			{
				err.colomn = iter.colomn;
				err.row = iter.row;
				err.sourceRow = _sourceCode[iter.row - 1];
				err.errText = "Wrong number";
				ERROR << err;

				temp.lexType = LexType::WRONG_LEX;
			}

		}
		else if (iter.lexem.length() == 1)
		{
			if (isSingleCharacterLexem(iter.lexem[0]))
				temp.lexType = LexType::SINGLE_SYMB;
			else
				temp.lexType = LexType::USER_IDENT;
		}
		else
			temp.lexType = LexType::USER_IDENT;

		_tokens.push_back(temp);
	}
}

void Lexer::OutputTokens()
{
	int i = 0;
	string s;
	for (auto iter : _tokens)
	{
		cout << "(" << iter.row << "," << iter.colomn << "): " << iter.lexem << " - ";
		switch (iter.lexType)
		{
		case LexType::USER_IDENT:
			s = "USER_IDENT";
			break;
		case LexType::COMMAND:
			s = "COMMAND";
			break;
		case LexType::DATA_TYPE:
			s = "DATA_TYPE";
			break;
		case LexType::DIRECTIVE:
			s = "DIRECTIVE";
			break;
		case LexType::SINGLE_SYMB:
			s = "SINGLE_SYMB";
			break;
		case LexType::TEXT_CONST:
			s = "TEXT_CONST";
			break;
		case LexType::BIN_CONST:
			s = "BIN_CONST";
			break;
		case LexType::DEC_CONST:
			s = "DEC_CONST";
			break;
		case LexType::HEX_CONST:
			s = "HEX_CONST";
			break;
		case LexType::REG32:
			s = "REG32";
			break;
		case LexType::REG16:
			s = "REG16";
			break;
		case LexType::REG8:
			s = "REG8";
			break;
		case LexType::SEG_REG:
			s = "SEG_REG";
			break;
		case LexType::WRONG_LEX:
			s = "WRONG LEXEM";
			break;
		}
		cout << s << endl;
	}
}

Lexer::~Lexer()
{
}
