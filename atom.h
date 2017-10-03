#ifndef ATOM_H
#define ATOM_H

#include <string>
#include <sstream>
using namespace std;

class Atom {
public:
  Atom (string s):_symbol(s) { type = "Atom"; }
  template <class Type>
	  bool match(Type &compare) {
	  if (compare.type == "Variable")
	  {
		  return compare.match<Atom>(*this);
	  }
	  else {
            forcompare << compare.value();
            return value() == forcompare.str();
		}
  }
  string value() { return _symbol; }
  string _symbol;
  stringstream forcompare;
  string type;
};

#endif
