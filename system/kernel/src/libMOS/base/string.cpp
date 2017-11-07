
#include "string.hpp"

string::string()
{
	cstr = 0;
}

string::string(const char *str)
{
	cstr = new char[strlen(str) + 1];
	strcpy(cstr, str);
}

string::string(const string& q)
{
	cstr = new char[strlen(q.cstr) + 1];
	strcpy(cstr, q.cstr);
}

string::~string()
{
	if (cstr)
		delete[] cstr;
}

string::operator char*()
{
	return cstr;
}

string::operator const char* ()
{
	return cstr;
}

string& string::operator= (const string& rhs)
{
	if (this == &rhs) return *this;

	if (cstr)
		delete[] cstr;
	cstr = new char[strlen(rhs.cstr) + 1];
	strcpy(cstr, rhs.cstr);
	return *this;
}

string& string::operator+= (const string& rhs)
{
	uint32_t size = strlen(cstr) + strlen(rhs.cstr) + 1;
	char *tmp = new char[size];
	strcpy(tmp, cstr);
	strcat(tmp, rhs.cstr);
	delete[] cstr;
	cstr = tmp;
	return *this;
}

string operator+ (const string& lhs, const string& rhs)
{
	return string(lhs) += rhs;
}

string operator+ (const string& lhs, char rhs)
{
	return string(lhs) += string(rhs);
}

string operator+ (const string& lhs, const char* rhs)
{
	return string(lhs) += string(rhs);
}

string operator+ (char lhs, const string& rhs)
{
	return string(lhs) += rhs;
}

string operator+ (const char* lhs, const string& rhs)
{
	return string(lhs) += rhs;
}