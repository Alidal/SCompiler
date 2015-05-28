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

	file << "ERROR ";
	file << "(" << err.row << "," << err.column << "): " << info << endl;
	file << err.codeRow << endl;

	file.width(err.column);
	file << "^" << endl;
	return *this;
}