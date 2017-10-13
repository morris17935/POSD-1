#ifndef ATOM_H
#define ATOM_H

#include "Term.h"
using namespace std;

class Atom : public Term {
public:
	Atom(string s){ _symbol = s; type = "Atom"; }
	template <class Type>
	bool match(Type &compare) {
		if (compare.type == "Variable")
		{
			return compare.match<Atom>(*this);
		}
		else {
			forcompare << compare.symbol();
			return symbol() == forcompare.str();
		}
	}
};

#endif
