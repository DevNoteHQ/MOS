
#include "string.hpp"

string::string() {
	cstr = 0;
}

string::string(char str) {
	size = 1;
	cstr = new char[size + 1];
	*cstr = str;
}

string::string(const char *str) {
	size = strlen(str);
	cstr = new char[size + 1];
	strcpy(cstr, str);
}

string::string(const string& q) {
	size = q.size;
	cstr = new char[size + 1];
	strcpy(cstr, q.cstr);
}

string::~string() {
	if (cstr)
		delete[] cstr;
}

unsigned string::Length() {
	return size;
}

string::operator char*() {
	return cstr;
}

string::operator const char* () {
	return cstr;
}

string& string::operator= (const string& rhs) {
	if (this == &rhs) return *this;

	if (cstr)
		delete[] cstr;
	size = rhs.size;
	cstr = new char[size + 1];
	strcpy(cstr, rhs.cstr);
	return *this;
}

string& string::operator+= (const string& rhs) {
	size = size + rhs.size;
	char *tmp = new char[size + 1];
	strcpy(tmp, cstr);
	strcat(tmp, rhs.cstr);
	delete[] cstr;
	cstr = tmp;
	return *this;
}

string operator+ (const string& lhs, const string& rhs) {
	string s;
	s.size = lhs.size + rhs.size;
	s.cstr = new char[s.size + 1];
	strcpy(s.cstr, lhs.cstr);
	strcat(s.cstr, rhs.cstr);
	return s;
}

string operator+ (const string& lhs, char rhs) {
	string s;
	s.size = lhs.size + 1;
	s.cstr = new char[s.size + 1];
	strcpy(s.cstr, lhs.cstr);
	*(s.cstr + lhs.size) = rhs;
	return s;
}

string operator+ (const string& lhs, const char* rhs) {
	string s;
	s.size = lhs.size + strlen(rhs);
	s.cstr = new char[s.size + 1];
	strcpy(s.cstr, lhs.cstr);
	strcat(s.cstr, rhs);
	return s;
}

string operator+ (char lhs, const string& rhs) {
	string s;
	s.size = 1 + rhs.size;
	s.cstr = new char[s.size + 1];
	*s.cstr = lhs;
	strcpy((s.cstr + 1), rhs.cstr);
	return s;
}

string operator+ (const char* lhs, const string& rhs) {
	string s;
	s.size = strlen(lhs) + rhs.size;
	s.cstr = new char[s.size + 1];
	strcpy(s.cstr, lhs);
	strcat(s.cstr, rhs.cstr);
	return s;
}