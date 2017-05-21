
#ifndef LIBMOS_H
#define LIBMOS_H

class string
{
private:
	char* cstr;
public:
	string();
	string(char* str);
	string(string& str);
	~string();

	operator char*();
	operator const char*();
	string operator+(const string& q)const;
	string operator=(const string& q);
};

class Converter
{
public:
	string ToString(int i);
};

Converter Convert;

#endif