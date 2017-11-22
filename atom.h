#ifndef ATOM_H
#define ATOM_H

#include "term.h"
#include "variable.h"
using namespace std;

class Atom : public Term {
public:
	Atom(string s){ _symbol = s; type = "Atom"; }
	Atom(const Atom& temp) { _symbol = temp._symbol; }
	template <class Type>
	bool match(Type &compare) {
		if (compare.type == "Variable")
		{
			return (dynamic_cast<Variable*>(&compare))->match<Atom>(*this);
		}
		else {
			forcompare << compare.symbol();
			return symbol() == forcompare.str();
		}
	}
	string value() { 
		if(_value != "")  
			return _value; 
		else return symbol();
	}
};

#endif
