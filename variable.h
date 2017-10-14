#ifndef VARIABLE_H
#define VARIABLE_H
#include <string>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include "atom.h"
#include "term.h"
using namespace std;

class Variable : public Term {
public:
	Variable(string s) { _symbol = s;  type = "Variable"; }
	Variable() { type = "Variable"; }
  string value(){ 
	  if(_value != "")
		return _value; 
	  else if (connect.size() != 0) {
		  return connect[connect.size() - 1]->_symbol;
	  }
	  else
		 return _symbol;
  }
  template <class Type>
  bool match( Type &compare ){
	  if  (compare.type == "Variable" && compare.value() == compare.symbol()) {
		  Variable* help = dynamic_cast<Variable*>(&compare);
		  connect.push_back(help);
		  help->connect.push_back(this);
	  }
	  else if(compare.type == "Variable" || compare.type == "Struct") {
		forcompare.str("");
		forcompare << compare.value();
		if(ptr == NULL||*ptr == forcompare.str()){
			 _value = forcompare.str();
			 ptr = &_value;
			 check(compare);
			 return true;
		}
			else return false;
	}
	  else {
		  forcompare.str("");
		  forcompare << compare.symbol();
		  if (ptr == NULL || *ptr == forcompare.str()) {
			  _value = forcompare.str();
			  ptr = &_value;
			  check(compare);
			  return true;
		  }
		  else return false;
	 }
  }
  template <class Type>
  void check(Type &compare){
	  for (int i = 0; i < connect.size(); i++) {
		  if (connect[i]->value() == connect[i]->symbol() || connect[i]->value() == connect[i]->connect[connect[i]->connect.size()-1]->symbol()) {
			  connect[i]->match(compare);
		  }
	  }
  }
  vector<Variable *> connect;
private:
  string*ptr = NULL;
};

#endif
