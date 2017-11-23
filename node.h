#ifndef NODE_H
#define NODE_H
#include <string>
#include "term.h"
using namespace std;
enum Operators { SEMICOLON, COMMA, EQUALITY, TERM };
bool final_answer = true;
class Node {
public:
	Node(Operators op) :payload(op){}
	Node(Operators op, Term *t) :payload(op), term(t){}
	Node* left = nullptr;
	Node* right = nullptr;
	Term*term = nullptr;;
	vector<Term*> readyforreset;
	vector<Term*> forreset;
	int counter = 1;
	Operators payload;
	bool evaluate() {
		return visit(this);
	}
	bool visit(Node*current) {
		if (current->left != nullptr) 
			if (!visit(current->left)) {
				final_answer = false;
			}
				
		if (current->payload == EQUALITY) {
			if (current->left->term->type == "Variable")
				return (dynamic_cast<Variable*>(current->left->term))->match(*(current->right->term));
			else if(current->left->term->type == "Struct")
				return (dynamic_cast<Struct*>(current->left->term))->match(*(current->right->term));
			else if (current->left->term->type == "List")
				return (dynamic_cast<List*>(current->left->term))->match(*(current->right->term));
			else if (current->left->term->type == "Atom")
				return (dynamic_cast<Atom*>(current->left->term))->match(*(current->right->term));
			else if (current->left->term->type == "Number")
				return (dynamic_cast<Number*>(current->left->term))->match(*(current->right->term));
		}		
		else if (current->payload == COMMA) {
			if (!visit(current->right))
				final_answer = false;
			return final_answer;
		}
		else if (current->payload == SEMICOLON) {
			final_answer = true;
			for (Term* temp : readyforreset) {
				for (Variable* temp2 : dynamic_cast<Variable*>(temp)->connect) {
					temp2->ptr = NULL;
				}
			}
			readyforreset.clear();
			if (!visit(current->right))
				final_answer = false;
			return final_answer;
		}
		else if (current->payload == TERM){
			if(current->term->type == "Variable")
				readyforreset.push_back(current->term);
			return true;
		}
	}
};
#endif