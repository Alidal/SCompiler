// SCompiler.cpp : Defines the entry point for the console application.
//
#pragma warning(disable: 4018)
#include <iostream>

#include "LexicalAnalizer.h"
#include "SyntaxAnalizer.h"

int main(int argc, char* argv[])
{
	LexicalAnalizer analizer("Test.asm");
	SyntaxAnalizer syntAnalizer(analizer.getTokens(), analizer.getSourceCode());
	return 0;
}