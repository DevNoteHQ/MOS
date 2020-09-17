
#ifndef STRING_HPP
#define STRING_HPP

class string {
private:
	char* cstr;
	unsigned size;
public:
	string();
	string(char str);
	string(const char* str);
	string(const string& str);
	~string();

	unsigned Length();

	operator char*();
	operator const char*();
	string& operator+=(const string& rhs);
	string& operator=(const string& rhs);
	friend string operator+(const string& lhs, const string& rhs);
	friend string operator+(const string& lhs, char rhs);
	friend string operator+(const string& lhs, const char* rhs);
	friend string operator+(char lhs, const string& rhs);
	friend string operator+(const char* lhs, const string& rhs);
};
#endif