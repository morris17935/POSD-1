#ifndef TERM_H
#define TERM_H

#include <string>
#include <sstream>
using namespace std;


class Term {

public:
	virtual string symbol() { return _symbol; }

	virtual string value() { return _value; }

	bool match( Term &fortest) {}
	string _symbol;
	string _value;
	stringstream temp;
	stringstream forcompare;
	string type;
};
#endif