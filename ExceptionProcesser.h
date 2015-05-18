#pragma once
#include "Global.h"
#include <iostream>
#include <Windows.h>
#undef ERROR
#define ERROR *ExceptionProcesser::GetInstance()

struct ErrInfo
{
	string errText;
	string codeRow;
	int row;
	int column;
};

class ExceptionProcesser
{
private:
	static ExceptionProcesser* m_instance;
public:
	ExceptionProcesser();
	~ExceptionProcesser();
	static ExceptionProcesser* GetInstance();
	ExceptionProcesser& operator << (string info);
	ExceptionProcesser& operator << (ErrInfo info);
};
