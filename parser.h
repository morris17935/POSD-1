#ifndef PARSER_H
#define PARSER_H
#include <string>
using std::string;
#include "term.h"
#include "atom.h"
#include "variable.h"
#include "struct.h"
#include "list.h"
#include "global.h"
#include "number.h"
#include "scanner.h"
#include <sstream>
#include <iostream>
using namespace std;
class Parser{
public:
  Parser(Scanner scanner) : _scanner(scanner){}
  vector<Term*> terms;
  vector<Term*> reverseterms;
  Term* createTerm(){
    string token = _scanner.nextToken();
    if(token != "Error"){
        if(islower(token[0]) || isSpecialCh(token[0])){
          if(_scanner.lookforward() == "("){
            vector<Term*>temp;
            while(_scanner.lookforward() != ")"){
                Term*wanttopush = createTerm();
                if(wanttopush != NULL)
                    temp.push_back(wanttopush);
            }
            return new Struct(Atom(token),temp);
          }
          else
            return new Atom(token);
        }
        else if(isupper(token[0]) || token[0] == '_'){
          return new Variable(token);
        }
        else if(isdigit(token[0])){
          stringstream temp(token);
          double store;
          temp >> store;
          return new Number(store);
        }
        else if(token == "["){
          vector<Term*>temp;
          while(_scanner.buffersize() > _scanner.position() && _scanner.lookforward() != "]"){
            Term*wanttopush = createTerm();
            if(wanttopush != NULL)
                temp.push_back(wanttopush);
          }
          if (_scanner.buffersize() == _scanner.position())
              throw string("unexpected token");
          if (_scanner.lookforward() == "]")
              _scanner.nextToken();
          return new List(temp);
        }
    }
    return NULL;
  }
  vector<Term*> expressiontree(){
	for(Term* temp : terms){
		 vector<Term*>::iterator it = reverseterms.begin();
		 reverseterms.insert(it,temp);
	}
	return reverseterms;
  }
  vector<Term*> getterms()
  {
	  while (_scanner.buffersize() > _scanner.position()) {
		  Term*wanttopush = createTerm();
		  if (wanttopush != NULL)
            terms.push_back(wanttopush);
	  }
	  return terms;
  }
private:
  Scanner _scanner;
};
#endif
