#ifndef NODE_H
#define NODE_H
#include <string>
#include "term.h"
#include "global.h"
using namespace std;
enum Operators { SEMICOLON, COMMA, EQUALITY,DOT,TERM };
bool final_answer = true;
bool flag = true;
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
		result = "";
		final_answer = true;
		if(visit(this)){
			if(!result.empty()){
				result.pop_back();
				result.pop_back();
				result += ".";
			}
			else
				result += "true.";
			return true;
		}
		else {
			int found = 0;
			found = result.find_last_of(";");
			if(found<0)
				result = "false.";
			else{
				result.erase(found,result.size()  - found);
				result+=".";
			}
			return false;
		}
	}
	bool visit(Node*current) {
		if (current->left != nullptr) 
			if (!visit(current->left)) {
				final_answer = false;
			}
				
		if (current->payload == EQUALITY) {
			if (current->left->term->type == "Variable"){
				if((dynamic_cast<Variable*>(current->left->term))->match(*(current->right->term)) == true && current->right->term->type != "Variable"){
					int found = 0;
					while(found>=0){
						found = int(result.find(current->left->term->symbol(),found + 1));
						if(found>0 && result[found + current->left->term->symbol().size() + 1] != '='){
							result.erase(found,current->left->term->symbol().size());
							result.insert(found,current->right->term->symbol());
						}
					}
					if(int(result.find(current->left->term->symbol() + " = " + current->right->term->value())) < 0 && current->left->term->symbol() != current->right->term->symbol())
						result = result + current->left->term->symbol() + " = " + current->right->term->value() + ", ";
					else if(int(result.find(current->left->term->symbol() + " = " + current->right->term->value())) >= 0 && int(result.find(current->left->term->symbol() + " = " + current->right->term->value())) < int(result.find(";"))){
						result = result + current->left->term->symbol() + " = " + current->right->term->value() + ", ";
					}
				}
				return (dynamic_cast<Variable*>(current->left->term))->match(*(current->right->term));
			}
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
			if(!final_answer){
				int found = 0;
				flag = false;
				found = result.find_last_of(";");
				if(found<0)
					result = "false.";
				else{
					result.erase(found,result.size()  - found);
					result+="; ";
				}
			}
			return final_answer;
		}
		else if (current->payload == SEMICOLON) {
			final_answer = true;
			if(result[result.size()-2] != ';'){
				result.pop_back();
				result.pop_back();
				result += "; ";
			}
			else if(flag){
				result += "true; ";
			}
			flag = true;
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