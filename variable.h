#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include "term.h"
#include "list.h"
#include <typeinfo>

using std::string;

class Variable : public Term {
public:
  Variable(string s):Term(s), _inst(0){}
  string value() const {
    if (_inst)
      return _inst->value();
    else
      return Term::value();
  }
  bool match( Term & term ){
    bool ret = true;
    if (this == &term)
      return ret;
    if(!_inst){      
      if (typeid(term) ==  typeid(List)){
        List * ls= dynamic_cast<List*>(&term);
         std::cout << "Variable_List:"+ls->symbol()<< std::endl;
         ret =  ls->match(*this);
        _inst = &term ;
        return ret;
      }
      _inst = &term ;
      return ret;
    }
    return _inst->match(term);
  }
private:
  Term * _inst;
};

#endif
