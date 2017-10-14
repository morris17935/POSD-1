#ifndef STRUCT_H
#define STRUCT_H

#include "atom.h"
#include "term.h"
#include <vector>
#include <string>

using namespace std;

class Struct :public Term
{
public:
	Struct(Atom const &name, vector<Term *> &args) : _args(&args), _name(name){ type = "Struct"; }

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
	Atom name() {
		return _name;
	}
	Term * args(int index) {
		return (*_args)[index];
	}

	string symbol() {
		_symbol = _name.symbol() + "(";
		for (int i = 0; i < (*_args).size() - 1; i++) {
			_symbol = _symbol + (*_args)[i]->symbol() + ", ";
		}
		_symbol = _symbol + (*_args)[(*_args).size() - 1]->symbol() + ")";
		return _symbol;
	}
	string value() {
		_value = _name.symbol() + "(";
		for (int i = 0; i < (*_args).size() - 1; i++) {
			if((*_args)[i]->value() == "")
				_value =  _value + (*_args)[i]->symbol() + ", ";
			else {
				_value = _value + (*_args)[i]->value() + ", ";
			}
		}
		if ((*_args)[(*_args).size() - 1]->value() == "")
			_value = _value + (*_args)[(*_args).size() - 1]->symbol() + ")";
		else
			_value = _value + (*_args)[(*_args).size() - 1]->value() + ")";
		return _value;
	}
std::vector<Term *> *_args;
private:
	Atom _name;
	
};

#endif