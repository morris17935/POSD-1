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
	  if (ptr != NULL) {
		  if(ptr->type == "Atom" || ptr->type == "Number")
			return ptr->symbol();
		  else
			return ptr->value();
	  }
	  else if (trigger != -1) {
		  return connect[trigger]->_symbol;
	  }
	  else
		 return _symbol;
  }
  template <class Type>
  bool match( Type &compare ){
	  if (compare.type == "Atom" || compare.type == "Number"){
		  forcompare.str("");
		  forcompare << compare.symbol();
		  if (ptr == NULL || value() == forcompare.str()) {
			  _value = forcompare.str();
			  ptr = &compare;
			  check(compare);
			  return true;
		  }
		  else return false;
	  }
	  else if(compare.type == "Struct"|| compare.type == "List") {
		forcompare.str("");
		forcompare << compare.value();
		if (int(compare.symbol().find(symbol())) >= 0)
			return false;
		else if(ptr == NULL|| value() == forcompare.str()){
			 _value = forcompare.str();
			 ptr = &compare;
			 check(compare);
			 return true;
		}
			else return false;
	}
	  Variable* help = dynamic_cast<Variable*>(&compare);
	  if (compare.type == "Variable" && help->ptr !=  NULL) {
		  forcompare.str("");
		  forcompare << compare.value();
		  if (ptr == NULL || ptr->value() == forcompare.str()) {
			  _value = forcompare.str();
			  ptr = &compare;
			  check(compare);
			  return true;
		  }
		  else return false;
	  }
	  else if (compare.type == "Variable" && help->ptr == NULL&& ptr != NULL) {
		  connect.push_back(help);
		  help->connect.push_back(this);
		  trigger = connect.size() - 1;
		  help->ptr = ptr;
		  return true;
	  }
	  else  {
		  connect.push_back(help);
		  help->connect.push_back(this);
		  trigger = connect.size() - 1;
		  return true;
	  }
  }
  template <class Type>
  void check(Type &compare){
	  for (int i = 0; i < connect.size(); i++) {
		  if (connect[i]->ptr == NULL) {
			  connect[i]->match(compare);
		  }
	  }
  }
  vector<Variable *> connect;
  int trigger = -1;
  Term*ptr = NULL;
};

#endif
