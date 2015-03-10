#include "Lexer.h"


Lexer::Lexer(string fileName)
{
	ifstream sourceFile(fileName);
	if (sourceFile.is_open())
	{
		char buf;
		while (sourceFile >> std::noskipws >> buf)
		{
			_sourceCode += toupper(buf);
		}
		sourceFile.close();
		//cout << _sourceCode << endl << endl;
		GenerateLexemVector();
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
	while (i < _sourceCode.length())
	{
		if (!isInAlphabet(_sourceCode[i]))
		{
			//TODO Throw exception
			if (buf != "")
				_lexemas.push_back(buf);
			buf.clear();
			++i;
		}
		else if (isCharLexemDivider(_sourceCode[i]))
		{
			if(buf != "")
				_lexemas.push_back(buf);
			++i;
			buf.clear();
		}
		else if (isSingleCharacterLexem(_sourceCode[i]))
		{
			_lexemas.push_back(buf);
			buf.clear();

			buf += _sourceCode[i];
			_lexemas.push_back(buf);
			++i;
			buf.clear();
		}
		else
		{
			buf += _sourceCode[i];
			++i;
		}
	}
	for (auto it : _lexemas)
		cout << it << endl;
}

Lexer::~Lexer()
{
}
