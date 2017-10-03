#ifndef NUMBER_H
#define NUMBER_H

#include <string>
#include "atom.h"
#include "variable.h"
#include <sstream>
using namespace std;

class Number {
public:
	Number(double x) : _value(x) { temp << _value; _symbol = temp.str();type = "Number"; }
	template <class Type>
	bool match(Type &compare) {
		if (compare.type == "Variable")
			{ return compare.match<Number>(*this); }
		else {
            forcompare << compare.value();
            return symbol() == forcompare.str();
		}
	}
	string symbol() { return _symbol; }
	string value() { return _symbol; }
	string _symbol;
	const double _value;
	stringstream temp;
	stringstream forcompare;
	string type;
};

#endif
