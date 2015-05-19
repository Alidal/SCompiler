#include "LexicalAnalizer.h"

LexicalAnalizer::LexicalAnalizer(string fileName)
{
	ifstream sourceFile(fileName);
	if (sourceFile.is_open())
	{
		string buf;
		while (getline(sourceFile, buf))
			sourceCode.push_back(buf);

		sourceFile.close();

		bool isQuote = false;
		for (auto &iter : sourceCode)
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

		GenerateLexemVector();
		AnalizeLexems();
		//OutputTokens();
	}
	else
	{
		ERROR << "File can\'t be opened. Check source file name.";
		exit(1);
	}
}

void LexicalAnalizer::GenerateLexemVector()
{
	int i;
	Lexem buf;
	buf.row = 0;
	buf.column = 1;
	for (auto curRow : sourceCode)
	{
		i = 0;
		buf.text.clear();
		++buf.row;

		err.row = buf.row;
		err.codeRow = sourceCode[buf.row - 1];

		while (i < curRow.length())
		{
			err.column = i + 1;
			if (!isInAlphabet(curRow[i]))
			{
				err.errText = "Wrong character";
				ERROR << err;

				buf.text += curRow[i];

				buf.column = ++i;
			}
			else if (isCharLexemDivider(curRow[i]))
			{
				if (!buf.text.empty())
					lexems.push_back(buf);

				buf.column = i + 1;
				buf.text.clear();
				++i;
			}
			else if (isSingleCharacterLexem(curRow[i]))
			{
				if (!buf.text.empty())
				{
					lexems.push_back(buf);
					buf.column = i + 1;
					buf.text.clear();
				}

				buf.text += curRow[i];
				lexems.push_back(buf);
				buf.column = i + 1;
				buf.text.clear();
				++i;
			}
			else if (isCharQuote(curRow[i]))
			{
				buf.text += curRow[i];
				++i;
				while (i < curRow.length() && !isCharQuote(curRow[i]))
				{
					buf.text += curRow[i];
					++i;
				}

				if (i == curRow.length())
				{
					err.errText = "No close quote";
					ERROR << err;
				}
				else
					buf.text += curRow[i];

				lexems.push_back(buf);
				buf.column = i + 1;
				buf.text.clear();
				++i;
			}
			else
			{
				buf.text += curRow[i];
				++i;
			}
		}

		if (!buf.text.empty())
			lexems.push_back(buf);
		buf.column = i + 1;
	}
}

void LexicalAnalizer::AnalizeLexems()
{
	Token temp;
	for (auto iter : lexems)
	{
		temp.lex.text = iter.text;
		temp.lex.row = iter.row;
		temp.lex.column = iter.column;

		if (isCommand(iter.text))
			temp.lexType = LexType::COMMAND;
		else if (is32Register(iter.text))
			temp.lexType = LexType::REG32;
		else if (is16Register(iter.text))
			temp.lexType = LexType::REG16;
		else if (is8Register(iter.text))
			temp.lexType = LexType::REG8;
		else if (isSegmentRegister(iter.text))
			temp.lexType = LexType::SEG_REG;
		else if (isDirective(iter.text))
			temp.lexType = LexType::DIRECTIVE;
		else if (isCharQuote(iter.text[0]) && isCharQuote(iter.text[iter.text.length() - 1]))
			temp.lexType = LexType::TEXT_CONST;
		else if (isCharQuote(iter.text[0]) && !isCharQuote(iter.text[iter.text.length() - 1])) //TODO Try to optimize
			temp.lexType = LexType::WRONG_LEX;
		else if (isCharNumber(iter.text[0]))
		{
			string::size_type sz = 0;
			int base = 10;

			if (iter.text[iter.text.length() - 1] == 'B')
			{
				temp.lexType = LexType::BIN_CONST;
				base = 2;
			}
			else if (iter.text[iter.text.length() - 1] == 'H')
			{
				temp.lexType = LexType::HEX_CONST;
				base = 16;
			}
			else if (iter.text[iter.text.length() - 1] == 'D' || isCharNumber(iter.text[iter.text.length() - 1]))
				temp.lexType = LexType::DEC_CONST;

			if (!isCharNumber(iter.text[iter.text.length() - 1]))
				temp.lex.text.pop_back();

			stoll(iter.text, &sz, base);
			if (sz < iter.text.length() - 1)
			{
				err.column = iter.column + sz + 1;
				err.row = iter.row;
				err.codeRow = sourceCode[iter.row - 1];
				err.errText = "Wrong number";
				ERROR << err;

				temp.lexType = LexType::WRONG_LEX;
			}
		}
		else if (iter.text.length() == 1)
		{
			if (isSingleCharacterLexem(iter.text[0]))
				temp.lexType = LexType::SINGLE_SYMB;
			else
				temp.lexType = LexType::USER_IDENT;
		}
		else
		{
			temp.lexType = LexType::USER_IDENT;
			for (auto n_iter : iter.text)
				if (!isInAlphabet(n_iter))
				temp.lexType = LexType::WRONG_LEX;
		}

		tokens.push_back(temp);
	}
}

void LexicalAnalizer::OutputTokens()
{
	int i = 0;
	string s;
	for (auto iter : tokens)
	{
		cout << "(" << setw(2) << iter.lex.row << "," << setw(2) << iter.lex.column << "): " << setw(8) << iter.lex.text << " - ";
		switch (iter.lexType)
		{
		case LexType::USER_IDENT:
			s = "USER_IDENT";
			break;
		case LexType::COMMAND:
			s = "COMMAND";
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

vector<Token> LexicalAnalizer::getTokens()
{
	return tokens;
}

vector<string> LexicalAnalizer::getSourceCode()
{
	return sourceCode;
}

LexicalAnalizer::~LexicalAnalizer()
{
}