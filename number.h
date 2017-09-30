#ifndef NUMBER_H
#define NUMBER_H

#include <string>
#include "atom.h"
#include "variable.h"
#include <sstream>
using namespace std;

class Number {
public:
	Number(string s, double x) :_symbol(s), _value(x) { temp << _value; type = "Number"; }
	template <class Type>
	bool match(Type &compare) { 
		if (compare.type == "Variable") 
			{ return compare.match<Number>(*this); } 
		else return temp.str() == compare.value(); 
	}
	/*bool match(Atom a) { return temp.str() == a._symbol; }
	bool match(Number &a) { return temp.str() == a.value(); }
	bool match(Variable &a) { return a.match<Number>(*this); }*/
	string symbol() { return _symbol; }
	string value() { return temp.str(); }
	const string _symbol;
	const double _value;
	stringstream temp;
	string type;
};

#endif
