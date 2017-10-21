#ifndef NUMBER_H
#define NUMBER_H

#include "term.h"
using namespace std;

class Number : public Term {
public:
	Number(double x) { temp << x; _symbol = temp.str();type = "Number"; }
	template <class Type>
	bool match(Type &compare) {
		if (compare.type == "Variable")
		{
			return compare.match<Number>(*this);
		}
		else {
			forcompare << compare.symbol();
			return symbol() == forcompare.str();
		}
	}
	string value() {
		if (_value != "")
			return _value;
		else return symbol();
	}
};

#endif
