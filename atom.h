#ifndef ATOM_H
#define ATOM_H

#include <string>

using std::string;

class Atom {
public:
  Atom (string s):_symbol(s) { type = "Atom"; }
  template <class Type>
	  bool match(Type &compare) {
	  if (compare.type == "Variable")
	  {
		  return compare.match<Atom>(*this);
	  }
	  else return value() == compare.value();
  }
  bool match(Atom a) {return _symbol == a._symbol;}
  string value() { return _symbol; }
  string _symbol;
  string type;
};

#endif
