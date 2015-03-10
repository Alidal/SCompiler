#include "Lexer.h"


Lexer::Lexer(string fileName)
{
	ifstream sourceFile(fileName);
	if (sourceFile.is_open())
	{
		string buf;
		while (getline(sourceFile, buf))
		{
			_sourceCode.push_back(buf);
		}
		sourceFile.close();

		for (auto &i : _sourceCode)
		{
			transform(i.begin(), i.end(), i.begin(),::toupper);
		}
		GenerateLexemVector();
		AnalizeLexems();
		OutputTokens();
	}
	else
	{
		//TODO Throw exception
	}
}

void Lexer::GenerateLexemVector()
{
	int i = 0;
	string buf;
	for (auto curRow : _sourceCode)
	{
		i = 0;
		buf.clear();

		while (i < curRow.length())
		{
			if (!isInAlphabet(curRow[i]))
			{
				//TODO Throw exception "wrong character"
				if (!buf.empty())
					_lexems.push_back(buf);
				buf.clear();
				++i;
			}
			else if (isCharLexemDivider(curRow[i]))
			{
				if (!buf.empty())
					_lexems.push_back(buf);
				buf.clear();
				++i;
			}
			else if (isSingleCharacterLexem(curRow[i]))
			{
				_lexems.push_back(buf);
				buf.clear();

				buf += curRow[i];
				_lexems.push_back(buf);
				buf.clear();
				++i;
			}
			else if (isCharQuote(curRow[i]))
			{
				buf += curRow[i];
				++i;
				while (i < curRow.length() && !isCharQuote(curRow[i]))
				{
					buf += curRow[i];
					++i;
				}

				if (i == curRow.length())
				{
					//TODO Throw exception "no close quote"
				}
				else
				{
					buf += curRow[i];
				}
				_lexems.push_back(buf);
				buf.clear();
				++i;
				
			}
			else if (isCharComment(curRow[i]))
			{
				if (!buf.empty())
					_lexems.push_back(buf);
				//TODO Maybe add comments
				i = curRow.length();
			}
			else
			{
				buf += curRow[i];
				++i;
			}
		}

		if (!buf.empty())
			_lexems.push_back(buf);
	}
	for (auto it : _lexems)
		cout << it << endl;
}

void Lexer::AnalizeLexems()
{
	for (auto iter : _lexems)
	{
		if (isCommand(iter))
			_tokens.insert(pair<string, LexType>(iter, LexType::COMMAND));
		else if (isDataType(iter))
			_tokens.insert(pair<string, LexType>(iter, LexType::DATA_TYPE));
		else if (is32Register(iter))
			_tokens.insert(pair<string, LexType>(iter, LexType::REG32));
		else if (is16Register(iter))
			_tokens.insert(pair<string, LexType>(iter, LexType::REG16));
		else if (is8Register(iter))
			_tokens.insert(pair<string, LexType>(iter, LexType::REG8));
		else if (isSegmentRegister(iter))
			_tokens.insert(pair<string, LexType>(iter, LexType::SEG_REG));
		else if (isDirective(iter))
			_tokens.insert(pair<string, LexType>(iter, LexType::DIRECTIVE));
		else if (isCharQuote(iter[0]))
			_tokens.insert(pair<string, LexType>(iter, LexType::TEXT_CONST));
		else if (isCharNumber(iter[0]))
		{
			try
			{
				stoi(iter);
			}
			catch (std::invalid_argument &e)
			{
				//TODO Throw exception "wrong number"
				continue;
			}

			if (iter[iter.length()] == 'B')
				_tokens.insert(pair<string, LexType>(iter, LexType::BIN_CONST));
			else if (iter[iter.length()] == 'H')
				_tokens.insert(pair<string, LexType>(iter, LexType::HEX_CONST));
			else if (iter[iter.length()] == 'D' || isCharNumber(iter[iter.length()]))
				_tokens.insert(pair<string, LexType>(iter, LexType::DEC_CONST));
		}
		else if (iter.length() == 1)
		{
			if (isSingleCharacterLexem(iter[0]))
				_tokens.insert(pair<string, LexType>(iter, LexType::SINGLE_SYMB));
			else
				_tokens.insert(pair<string, LexType>(iter, LexType::USER_IDENT));
		}
		else
			_tokens.insert(pair<string, LexType>(iter, LexType::USER_IDENT));
	}
}

void Lexer::OutputTokens()
{
	int i = 0;
	string s;
	for (auto iter : _tokens)
	{
		cout << "#" << ++i << " Token:" << iter.first << " - ";
		switch (iter.second)
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
		}
		cout << s << endl;
	}
}

Lexer::~Lexer()
{
}
