#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include <iostream>
#include <cstdlib>
#include "atom.h"
using namespace std;

class Variable{
public:
	Variable(string s) :_symbol(s) { ptr = &_value; type = "Variable"; }
	Variable() { type = "Variable"; }
  string value(){ return _value; }
  template <class Type>
  bool match( Type &compare ){
    if(ptr == NULL||*ptr == compare.value()){
      _value = compare.value();
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
};

#endif
