#ifndef VARIABLE_H
#define VARIABLE_H
#include <string>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include "atom.h"
using namespace std;

class Variable{
public:
	Variable(string s) :_symbol(s) {}
	Variable() { type = "Variable"; }
  string value(){ return _value; }
  template <class Type>
  bool match( Type &compare ){
    forcompare.str("");
    forcompare << compare.value();
    if(ptr == NULL||*ptr == forcompare.str()){
      _value = forcompare.str();
	  ptr = &_value;
	  return true;
    }
	else return false;
  }
 string const _symbol;
 string type;
private:
  string*ptr = NULL;
  string _value;
  stringstream forcompare;
};

#endif
