
#ifndef STRING_HPP
#define STRING_HPP

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
	string operator+=(const string& q);
	string operator=(const string& q);
};

#endif