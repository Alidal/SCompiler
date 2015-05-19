#include "ExceptionProcesser.h"

ErrInfo err;

ExceptionProcesser* ExceptionProcesser::m_instance = nullptr;

ExceptionProcesser* ExceptionProcesser::GetInstance()
{
	if (m_instance == nullptr)
		m_instance = new ExceptionProcesser();

	return m_instance;
}

ExceptionProcesser::ExceptionProcesser()
{
}

ExceptionProcesser::~ExceptionProcesser()
{
}

ExceptionProcesser& ExceptionProcesser::operator<<(ErrInfo info)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 4);
	cout << "ERROR ";
	SetConsoleTextAttribute(hConsole, 7);
	cout << "(" << info.row << "," << info.column << "): " << info.errText << endl;
	cout << info.codeRow << endl;

	cout.width(info.column);
	cout << "^" << endl;

	return *this;
}

ExceptionProcesser& ExceptionProcesser::operator<<(string info)
{

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 4);
	cout << "ERROR ";
	SetConsoleTextAttribute(hConsole, 7);
	cout << "(" << err.row << "," << err.column << "): " << info << endl;
	cout << err.codeRow << endl;

	cout.width(err.column);
	cout << "^" << endl;
	/*HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 4);
	cout << "ERROR: ";
	SetConsoleTextAttribute(hConsole, 7);
	cout << info << endl;*/
	return *this;
}