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
#include "node.h"
#include <sstream>
#include <iostream>

using namespace std;
class Parser {
public:
	Parser(Scanner scanner) : _scanner(scanner) {}
	vector<Term*> terms;
	vector<Term*> reverseterms;
	vector<Node*> syntaxtree;
	Term* originalcreateTerm(){
		string token = _scanner.nextToken();
		if (token != "Error") {
			if (islower(token[0]) || isSpecialCh(token[0])) {
				if (_scanner.lookforward() == "(") {
					vector<Term*>temp;
					while (_scanner.lookforward() != ")" && _scanner.lookforward() != ";") {
						Term*wanttopush = originalcreateTerm();
						if (wanttopush != NULL)
							temp.push_back(wanttopush);
					}
					if(_scanner.lookforward() == ";")
						throw string("Unbalanced operator");
					return new Struct(Atom(token), temp);
				}
				else if(!isSpecialCh(token[0]))
					return new Atom(token);
				
			}
			else if (isupper(token[0]) || token[0] == '_') {
				return new Variable(token);
			}
			else if (isdigit(token[0])) {
				stringstream temp(token);
				double store;
				temp >> store;
				return new Number(store);
			}
			else if (token == "[") {
				vector<Term*>temp;
				while (_scanner.buffersize() > _scanner.position() && _scanner.lookforward() != "]" && _scanner.lookforward() != ";") {
					Term*wanttopush = originalcreateTerm();
					if (wanttopush != NULL)
						temp.push_back(wanttopush);
				}
				if(_scanner.lookforward() == ";")
					throw string("Unbalanced operator");
				if (_scanner.buffersize() == _scanner.position())
					throw string("unexpected token");
				if (_scanner.lookforward() == "]")
					_scanner.nextToken();
				return new List(temp);
			}
		}
		return NULL;
	}
	Term* createTerm() {
		string token = _scanner.nextToken();
		if (token != "Error") {
			if (islower(token[0]) || isSpecialCh(token[0])) {
				if (_scanner.lookforward() == "(") {
					vector<Term*>temp;
					while (_scanner.lookforward() != ")" && _scanner.lookforward() != ";") {
						Term*wanttopush = originalcreateTerm();
						if (wanttopush != NULL)
							temp.push_back(wanttopush);
					}
					if(_scanner.lookforward() == ";")
						throw string("Unbalanced operator");
					return new Struct(Atom(token), temp);
				}
				else if(!isSpecialCh(token[0]))
					return new Atom(token);
				
			}
			else if (isupper(token[0]) || token[0] == '_') {
				return new Variable(token);
			}
			else if (isdigit(token[0])) {
				stringstream temp(token);
				double store;
				temp >> store;
				return new Number(store);
			}
			else if (token == "[") {
				vector<Term*>temp;
				while (_scanner.buffersize() > _scanner.position() && _scanner.lookforward() != "]" && _scanner.lookforward() != ";") {
					Term*wanttopush = originalcreateTerm();
					if (wanttopush != NULL)
						temp.push_back(wanttopush);
				}
				if(_scanner.lookforward() == ";")
					throw string("Unbalanced operator");
				if (_scanner.buffersize() == _scanner.position())
					throw string("unexpected token");
				if (_scanner.lookforward() == "]")
					_scanner.nextToken();
				return new List(temp);
			}
			if (token == "," || token == ";" || token == "="||token == ".") {
				if (token == ",")
					syntaxtree.push_back(new Node(COMMA));
				else if (token == ";")
					syntaxtree.push_back(new Node(SEMICOLON));
				else if (token == "=")
					syntaxtree.push_back(new Node(EQUALITY));
				else if (token == ".")
				  	syntaxtree.push_back(new Node(DOT));
			}
		}
		return NULL;
	}
	void matchings(){
		int parseposition = 0;
		while (_scanner.buffersize() > _scanner.position()) {
			Term*wanttopush = createTerm();
			if (wanttopush != NULL)
				terms.push_back(wanttopush);
			for (Node* temp : syntaxtree) {
				if (temp->payload == EQUALITY) {
					if (parseposition < terms.size() && temp->left == nullptr) {
						temp->left = new Node(TERM, terms[parseposition]);
						parseposition++;
					}
					if (parseposition < terms.size() && temp->right == nullptr) {
						temp->right = new Node(TERM, terms[parseposition]);
						parseposition++;
					}
				}
			}
		}

		if(syntaxtree.size() > 0 && syntaxtree[syntaxtree.size() - 1]->payload == DOT){
			for (int i =  syntaxtree.size() - 1 ; i >= 0 ; i--) {
				if(syntaxtree.size()!=1){
					vector<Node*>::iterator fortemplate = syntaxtree.begin();
					if(syntaxtree[i]->payload == COMMA ) {
						if(syntaxtree[i + 1]->payload == DOT){
							if(syntaxtree[i]->payload == COMMA)
								throw string("Unexpected ',' before '.'");
						}
						else if(i >= 1 && syntaxtree[i - 1]->payload == DOT){
							if(syntaxtree[i]->payload == COMMA)
								throw string("Unexpected ',' after '.'");
						}
						if(syntaxtree[i-1]->payload == EQUALITY && syntaxtree[i+1]->payload == EQUALITY)
						{
							syntaxtree[i]->left = syntaxtree[i - 1];
							syntaxtree[i]->right = syntaxtree[i + 1];
							syntaxtree.erase(fortemplate + i - 1);
							syntaxtree.erase(fortemplate + i );
							i--;
						}
					}
				}
			}
		}


		if(syntaxtree.size() > 0 && syntaxtree[syntaxtree.size() - 1]->payload == DOT){
			for (int i =  syntaxtree.size() - 1 ; i >= 0 ; i--) {
				if(syntaxtree.size()!=1){
					vector<Node*>::iterator fortemplate = syntaxtree.begin();
					if(syntaxtree[i]->payload != EQUALITY && syntaxtree[i]->payload != DOT && syntaxtree[i]->left == nullptr && syntaxtree[i]->right == nullptr) {
						if(syntaxtree[i + 1]->payload == DOT){
							if(syntaxtree[i]->payload == COMMA)
								throw string("Unexpected ',' before '.'");
							else if(syntaxtree[i]->payload == SEMICOLON)
								throw string("Unexpected ';' before '.'");
						}
						else if(i >= 1 && syntaxtree[i - 1]->payload == DOT){
							if(syntaxtree[i]->payload == COMMA)
								throw string("Unexpected ',' after '.'");
							else if(syntaxtree[i]->payload == SEMICOLON)
								throw string("Unexpected ';' after '.'");
						}
						syntaxtree[i]->left = syntaxtree[i - 1];
						syntaxtree[i]->right = syntaxtree[i + 1];
						syntaxtree.erase(fortemplate + i - 1);
						syntaxtree.erase(fortemplate + i );
						i--;
					}
				}
			}
		}
		else if(syntaxtree.size() > 0 && syntaxtree[syntaxtree.size() - 1]->payload != DOT)
			throw string("Missing token '.'");
		duplicate();
	}
	bool buildExpression(){
		matchings();
		return expressionTree()->evaluate();
	  }
	Node* expressionTree() {
		if(syntaxtree[0]->payload == DOT)
			throw string(terms[0]->symbol() + " does never get assignment");
		return syntaxtree[0];
	}
	void duplicate() {
		vector<Term*>::iterator it = terms.begin();
		for (int i = 0; i < terms.size(); i++)
			for (int j = i + 1; j < terms.size(); j++) {
				if (terms[i]->symbol() == terms[j]->symbol() && terms[i]->type == "Variable" && terms[j]->type == "Variable") {
					(dynamic_cast<Variable*>(terms[j]))->match(*(terms[i]));
				}
				else if(terms[i]->type == "Struct" && terms[j]->type == "Variable" && terms[i]->symbol().find(terms[j]->symbol()) != string::npos){
					findthevariable(terms[i] , terms[j]);
				}
				else if(terms[i]->type == "Variable" && terms[j]->type == "Struct" && terms[j]->symbol().find(terms[i]->symbol()) != string::npos){
					findthevariable(terms[j] , terms[i]);
				}
			}
	}
	void createTerms(){
		int parseposition = 0;
		while (_scanner.buffersize() > _scanner.position()) {
			Term*wanttopush = createTerm();
			if (wanttopush != NULL)
				terms.push_back(wanttopush);
		}
	}
	void findthevariable(Term*temp , Term*temp2){;
		for(Term * timelimit : dynamic_cast<Struct*>(temp)->_args){
			if(timelimit->symbol() == temp2->symbol())
				(dynamic_cast<Variable*>(timelimit))->match(*(temp2));
			else if(timelimit->symbol().find(temp2->symbol()) > 0 && (timelimit->type == "Struct" || timelimit->type == "List")){
				findthevariable(timelimit , temp2);
			}
		}
	}
	vector<Term*> getTerms() {
		return terms;
	}
	int findthefirstsameterm(int parseposition) {
		for (int i = 0; i < terms.size(); i++){
			if (terms[i]->symbol() == terms[parseposition]->symbol())
				return i;
		}
	}
private:
	Scanner _scanner;

};
#endif
