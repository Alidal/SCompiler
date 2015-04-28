// SCompiler.cpp : Defines the entry point for the console application.
//
#include <iostream>

#include "Lexer.h"
#include "SyntaxAnalizer.h"
using namespace std;

int main(int argc, char* argv[])
{
	Lexer analizer("Test.asm");
	SyntaxAnalizer syntAnalizer(analizer.getTokens());
	return 0;
}
