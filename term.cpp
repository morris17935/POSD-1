#include "atom.h"
#include "variable.h"
#include "list.h"
#include <typeinfo>
#include "iterator.h"
bool Term::match(Term & a){
  if (typeid(a) ==  typeid(Variable))
    return a.match(*this);
  else
    return symbol() == a.symbol();
}
Iterator <Term*>* Term::createIterator() {
	return new NullIterator<Term*>(this);
}