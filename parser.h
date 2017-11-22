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
	Term* createTerm() {
		string token = _scanner.nextToken();
		if (token != "Error") {
			if (islower(token[0]) || isSpecialCh(token[0])) {
				if (_scanner.lookforward() == "(") {
					vector<Term*>temp;
					while (_scanner.lookforward() != ")") {
						Term*wanttopush = createTerm();
						if (wanttopush != NULL)
							temp.push_back(wanttopush);
					}
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
				while (_scanner.buffersize() > _scanner.position() && _scanner.lookforward() != "]") {
					Term*wanttopush = createTerm();
					if (wanttopush != NULL)
						temp.push_back(wanttopush);
				}
				if (_scanner.buffersize() == _scanner.position())
					throw string("unexpected token");
				if (_scanner.lookforward() == "]")
					_scanner.nextToken();
				return new List(temp);
			}
			else if (token == "," || token == ";" || token == "=") {
				if (token == ",")
					syntaxtree.push_back(new Node(COMMA));
				else if (token == ";")
					syntaxtree.push_back(new Node(SEMICOLON));
				else
					syntaxtree.push_back(new Node(EQUALITY));
			}
		}
		return NULL;
	}
	void duplicate() {
		vector<Term*>::iterator it = terms.begin();
		for (int i = 0; i < terms.size(); i++)
			for (int j = i + 1; j < terms.size(); j++) {
				if (terms[i]->symbol() == terms[j]->symbol()) {
					terms.erase(it + j);
					j--;
				}
			}
	}
	Node* expressionTree() {
		return syntaxtree[0];
	}
	void createTerms(){}
	vector<Term*> getTerms() {
		int parseposition = 0;
		while (_scanner.buffersize() > _scanner.position()) {
			Term*wanttopush = createTerm();
			if (wanttopush != NULL)
				terms.push_back(wanttopush);
			for (Node* temp : syntaxtree) {
				if (temp->payload == EQUALITY) {
					if (parseposition < terms.size() && temp->left == nullptr) {
						temp->left = new Node(TERM, terms[findthefirstsameterm(parseposition)]);
						parseposition++;
					}
					if (parseposition < terms.size() && temp->right == nullptr) {
						temp->right = new Node(TERM, terms[findthefirstsameterm(parseposition)]);
						parseposition++;
					}
				}
			}
		}
		duplicate();
		if(syntaxtree.size() == 0||syntaxtree[0]->payload != EQUALITY)
			return terms;
		for (int i = 0; i < syntaxtree.size();i++) {
			vector<Node*>::iterator fortemplate = syntaxtree.begin();
			if(syntaxtree[i]->payload != EQUALITY) {
				syntaxtree[i]->left = syntaxtree[i - 1];
				syntaxtree[i]->right = syntaxtree[i + 1];
				syntaxtree.erase(fortemplate + i - 1);
				syntaxtree.erase(fortemplate + i );
				i--;
			}
		}
		return terms;
	}
	int findthefirstsameterm(int parseposition) {
		for (int i = 0; i < terms.size(); i++)
			if (terms[i]->symbol() == terms[parseposition]->symbol())
				return i;
	}
private:
	Scanner _scanner;

};
#endif
