// SCompiler.cpp : Defines the entry point for the console application.
//
#pragma warning(disable: 4018)
#include "Global.h"
#include "LexicalAnalizer.h"
#include "SyntaxAnalizer.h"

int main(int argc, char* argv[])
{
	string name = "ErrTest";
	file.open(name + ".lst");
	LexicalAnalizer analizer(name + ".asm");
	SyntaxAnalizer syntAnalizer(analizer.getTokens(), analizer.getSourceCode());
	file.close();
	return 0;
}