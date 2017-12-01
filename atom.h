#ifndef ATOM_H
#define ATOM_H

#include <string>
#include <sstream>
#include "term.h"
using std::string;

class Atom : public Term{
public:
  Atom(string s):Term(s) {}
};

#endif
