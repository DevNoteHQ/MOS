
#include "string.hpp"

string::string()
{
	cstr = 0;
}

string::string(char *str)
{
	cstr = new char[strlen(str) + 1];
	strcpy(cstr, str);
}

string::string(string& q)
{
	if (this == &q)
		return;
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

string string::operator +(const string &q) const
{
	string s;
	s.cstr = new char[strlen(cstr) + strlen(q.cstr) + 1];
	strcpy(s.cstr, cstr);
	strcat(s.cstr, q.cstr);
	return s;
}

string string::operator +=(const string &q)
{
	string s;
	s.cstr = new char[strlen(cstr) + strlen(q.cstr) + 1];
	strcpy(s.cstr, cstr);
	strcat(s.cstr, q.cstr);
	strcpy(cstr, s.cstr);
	return *this;
}

string string::operator =(const string &q)
{
	if (this != &q)
	{
		if (cstr)
			delete[] cstr;
		cstr = new char[strlen(q.cstr) + 1];
		strcpy(cstr, q.cstr);
	}
	return *this;
}