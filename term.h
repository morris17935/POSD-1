#ifndef TERM_H
#define TERM_H

#include <string>
#include <sstream>

using std::string;
template <class Type>
class Iterator;
class Term{
public:
  virtual string symbol() const {return _symbol;}
  virtual string value() const {return symbol();}
  virtual Iterator<Term*> * createIterator();
  virtual bool match(Term & a);
protected:
  Term ():_symbol(""){}
  Term (string s):_symbol(s) {}
  Term(double db){
    std::ostringstream strs;
    strs << db;
    _symbol = strs.str();
  }
  string _symbol;
};

#endif
