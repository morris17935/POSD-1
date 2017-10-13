#ifndef STRUCT_H
#define STRUCT_H

#include "atom.h"
#include "Term.h"
#include <vector>
#include <string>

using namespace std;

class Struct :public Term
{
public:
	Struct(Atom &name, vector<Term *> &args) : _args(&args), _name(name.symbol()){ type = "Struct"; }

	template <class Type>
	bool match(Type &compare) {
		if (compare.type != "Struct")
		{
			return false;
		}
		else {
			return value() == compare.value();
		}
	}
	string name() {
		return _name;
	}
	string symbol() {
		_symbol = _name + "(";
		for (int i = 0; i < (*_args).size(); i++) {
			_symbol = _symbol + (*_args)[i]->symbol() + ",";
		}
		_symbol[_symbol.size() - 1] = ')';
		return _symbol;
	}
	string value() {
		_value = _name + "(";
		for (int i = 0; i < (*_args).size(); i++) {
			if((*_args)[i]->value() == "")
				_value =  _value + (*_args)[i]->symbol() + ",";
			else {
				_value = _value + (*_args)[i]->value() + ",";
			}
		}
		_value[_value.size() - 1] = ')';
		return _value;
	}
private:
	string _name;
	std::vector<Term *> *_args;
};

#endif