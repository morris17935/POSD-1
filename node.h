#ifndef NODE_H
#define NODE_H
#include "term.h"

enum Operators {SEMICOLON, COMMA, EQUALITY, TERM};

class Node {
public:
  Node(Operators op):payload(op), term(0), left(0), right(0) {}
  Node(Operators op, Term *t, Node *l, Node *r):payload(op), term(t), left(l), right(r) {}

  void setchild(Node *l, Node *r){
    left = l ;
    right = r;
  }

  bool evaluate(){
    
    if(payload == COMMA  ){
      return (left->evaluate() && right->evaluate()) ;
    }
    else if(payload == SEMICOLON){
      bool leftSide = left->evaluate() ;
      bool rightSide = right->evaluate();
      return (leftSide || rightSide ) ;      
    }
    else if(payload == EQUALITY){
      return (left->term->match(*(right->term))) ;      
    }
    return false;
  }
  Operators payload ;    

public:
  Term* term ;
  Node* left ;
  Node* right ;
};

#endif
