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
		cout << _sourceCode << endl;
	}
	else
	{
		//TODO Throw exception
	}
}


Lexer::~Lexer()
{
}
