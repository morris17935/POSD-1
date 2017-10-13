#ifndef VARIABLE_H
#define VARIABLE_H
#include <string>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include "atom.h"
#include "Term.h"
using namespace std;

class Variable : public Term {
public:
	Variable(string s) { _symbol = s;  type = "Variable"; }
	Variable() { type = "Variable"; }
  string value(){ return _value; }
  template <class Type>
  bool match( Type &compare ){
	  cout << compare.value() + "  111" << endl ;
	  if (compare.type == "Variable" && compare.value() != "") {
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
	  else if (compare.type == "Variable" && compare.value() == "") {
		  connect.push_back(&compare);
		  compare.connect.push_back(this);
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
		  if (connect[i]->value() == "") {
			  cout << connect[i]->symbol() << endl;
			  connect[i]->match(compare);
		  }
	  }
  }
private:
  string*ptr = NULL;
};

#endif
