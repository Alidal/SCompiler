#include "ExceptionProcesser.h"

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

	for (int i = 0; i < info.column; ++i)
		cout << " ";
	cout << "^" << endl;
	
	return *this;
}

ExceptionProcesser& ExceptionProcesser::operator<<(string info)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 4);
	cout << "ERROR: ";
	SetConsoleTextAttribute(hConsole, 7);
	cout << info << endl;
	return *this;
}