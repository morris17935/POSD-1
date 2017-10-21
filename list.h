#ifndef LIST_H
#define LIST_H

#include "term.h"
#include <string>
#include <vector>
#include <iostream>
#include "variable.h"
using std::vector;
using namespace std;

class List : public Term {
public:
	List(){ type = "List"; }
	List(vector<Term *>  & elements) :_args(elements) { type = "List"; }
	string symbol(){
		if (_args.size() != 0) {
			_symbol = "[";
			for (int i = 0; i < _args.size() - 1; i++) {
				if(int(_symbol.find(_args[i]->symbol())) < 0)
					_symbol = _symbol + _args[i]->symbol() + ", ";
			}
			if (_args.size() > 0){
				if (int(_symbol.find(_args[_args.size() - 1]->symbol())) < 0)
					_symbol = _symbol + _args[_args.size() - 1]->symbol() + "]";
				else {
					_symbol.pop_back();
					_symbol.pop_back();
					_symbol = _symbol + "]";
				}
			}	
			else
				_symbol = _symbol + "]";
			return _symbol;
		}
		else
			return "[]";
	}
	string value() {
		_value = "[";
		if (_args.size() > 0) {
			for (int i = 0; i < _args.size() - 1; i++) {
				if (_args[i]->value() == "")
					_value = _value + _args[i]->symbol() + ", ";
				else
					_value = _value + _args[i]->value() + ", ";
			}
			if (_args[_args.size() - 1]->value() == "")
				_value = _value + _args[_args.size() - 1]->symbol() + "]";
			else
				_value = _value + _args[_args.size() - 1]->value() + "]";
		}
		else 
			_value = _value + "]";
		return _value;
	}
  template <class Type>
  bool match(Type &compare) {
	  if (compare.type == "Variable")
	  {
		  Variable* temp = dynamic_cast<Variable*>(&compare);
		  return (*temp).match(*this);
	  }
	  else if (compare.type != "List")
		  return false;
	  else  if (compare.type == "List") {
		  List* help = dynamic_cast<List*>(&compare);
		  if (_args.size() == (help->_args).size()) {
			  for (int i = 0; i < _args.size(); i++){
				  if (_args[i]->type == "Variable" || ((help->_args)[i]->type == "Variable")){
					  if (_args[i]->type == "Variable" && ((help->_args)[i]->type == "Variable")) {
						  Variable* temp = dynamic_cast<Variable*>(_args[i]);
						  Variable* temp2 = dynamic_cast<Variable*>((help->_args)[i]);
						  if(((*temp).match(*temp2)) == false)
							  return false;
					  }
					  else if (_args[i]->type == "Variable") {
						  Variable* temp = dynamic_cast<Variable*>(_args[i]);
						  if(!(*temp).match(*((help->_args)[i])))
							  return false;
					  }
					  else {
						  Variable* temp2 = dynamic_cast<Variable*>((help->_args)[i]);
						  if(!(*temp2).match(*(_args[i])))
							  return false;
					  }
				  }
				  else if (_args[i]->value() != ((help->_args)[i]->value()))
					  return false;
			  }
				 
			  return true;
		  }
		  else
			  return false;
	  }
  }
  Term * head() {
	  if (_args.size() > 0) {
		  if (_args.size() > 0)
			  return _args[0];
		  else
			  throw string("Accessing head in an empty list");
	  }
	  else
		  throw string("Accessing head in an empty list");
  };
  List*  tail()  {
	  if (_args.size() > 0) {
		  vector<Term *> templating = _args;
		  templating.erase(templating.begin());
		  if (templating.size() >= 0) {
			  return (new List(templating));
		  }
	  }
	  else throw  string("Accessing tail in an empty list");
  };
	std::vector<Term *> _args;
};

#endif
