#ifndef PARSER_H
#define PARSER_H
#include <string>
#include <typeinfo>
using std::string;

#include "term.h"
#include "number.h"
#include "atom.h"
#include "variable.h"
#include "global.h"
#include "scanner.h"
#include "struct.h"
#include "list.h"
#include "node.h"

#include "utParser.h"

class Parser{
public:
  Parser(Scanner scanner) : _scanner(scanner), _terms(){}

  Term* createTerm(){
    int token = _scanner.nextToken();
    _currentToken = token;
    if(token == VAR){
      return new Variable(symtable[_scanner.tokenValue()].first);
    }else if(token == NUMBER){
      return new Number(_scanner.tokenValue());
    }else if(token == ATOM || token == ATOMSC){
      Atom* atom = new Atom(symtable[_scanner.tokenValue()].first);
      if(_scanner.currentChar() == '(' ) {
        return structure();
      }
      else
        return atom;
    }
    else if(token == '['){
      return list();
    }
    return nullptr;
  }

  Term * structure() {
    Atom structName = Atom(symtable[_scanner.tokenValue()].first);
    int startIndexOfStructArgs = _terms.size();
    _scanner.nextToken();
    createTerms();
    if(_currentToken == ')')
    {
      vector<Term *> args(_terms.begin() + startIndexOfStructArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfStructArgs, _terms.end());
      return new Struct(structName, args);
    } else {
      throw string("unexpected token");
    }
  }

  Term * list() {
    int startIndexOfListArgs = _terms.size();
    createTerms();
    if(_currentToken == ']')
    {
      vector<Term *> args(_terms.begin() + startIndexOfListArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfListArgs, _terms.end());
      return new List(args);
    } else {
      throw string("unexpected token");
    }
  }
  vector<Term *> & getTerms() {
    return _terms;
  }

  void matchings (){
    createTerms(); 
    createNode ();
    createNodeofRealation();
  }
  void createNode (){
    int EqualityCounter= 0;
    int SymbolofNode;
    vector<Node*> nodeofTerms ;
    for(int i = 0 ; i< _terms.size();i++){
      nodeofTerms.push_back(new Node(TERM,_terms[i],0,0));      
    }    
    for(int i = 0 ; i< _operation.size() ;i++){
      switch (_operation[i]){
        case ';': _nodeofOperation.push_back(new  Node (SEMICOLON));break;
        case ',':_nodeofOperation.push_back(new  Node (COMMA)); break;
        case '=': _nodeofOperation.push_back(new Node (EQUALITY , 0 , nodeofTerms[EqualityCounter],nodeofTerms[EqualityCounter+1])); 
        EqualityCounter +=2;
        break;
        default :break;
      }
    }    
  }

  void createNodeofRealation(){
    for(int i = 0 ; i< _operation.size() ;i++){
      if(_operation[i] == ',' || _operation[i] == ';' ){
        _nodeofOperation[i]->setchild(_nodeofOperation[i-1],_nodeofOperation[i+1]);
        for(int j = i+1 ; j<_operation.size()  ; j++){
          if(_operation[j]==','  || _operation[j] == ';'){
            _nodeofOperation[i]->setchild(_nodeofOperation[i-1],_nodeofOperation[j]);
            break;
          }
        }
      }
    }
    setRoot();
    matchingSameVariable();
  }

  void matchingSameVariable(){    
    vector <Term* > blockofVariableAndStruct ;
    recursive_inorder(_tree,blockofVariableAndStruct);   
  }
  void matchVariabletoNestedStruct(Struct* parm_Struct ,Term*  goalofVariable){
    Variable* variableofparmStruct ;
    Struct * nestedofStruct;
    
    for(int z = 0  ; z < parm_Struct->arity() ; z++){           
      if (variableofparmStruct = dynamic_cast<Variable*>(parm_Struct->args(z))) {
        if(variableofparmStruct->symbol() == goalofVariable->symbol()){
          variableofparmStruct->match(*goalofVariable) ;
        }
      }
      else if(nestedofStruct =  dynamic_cast<Struct*>(parm_Struct->args(z)) ){
         matchVariabletoNestedStruct(nestedofStruct,goalofVariable);
      }
    }
  }

  void recursive_inorder(Node *here , vector<Term*> & v)
  {
    if(here != NULL)
    {
      if(here->left != NULL && here->right != NULL && here->payload != SEMICOLON){
        recursive_inorder(here->left ,v);
        recursive_inorder(here->right,v);          
      }       
      if( here->term != 0 ){
        Variable * varb= dynamic_cast<Variable*>(here->term);
        Struct * Stru= dynamic_cast<Struct*>(here->term);
        if(varb)
          v.push_back(here->term);                       
        else if(Stru)
          v.push_back(here->term);                       
      }
      for(int i = 0 ; i<v.size() ; i++){
        for(int j = 0 ; j<v.size() ; j++){
          Struct* transStruct = dynamic_cast<Struct*>(v[j]);
          if(transStruct && i != j){
            matchVariabletoNestedStruct(transStruct ,v[i] );
          }
          if(v[i]->symbol() == v[j]->symbol() && i != j){        
            v[i]->match(*v[j]);  
            v.erase(v.begin()+ j);      
          }        
        }
      }
      //下方為Struct的遞迴
      if(here->left != NULL && here->right != NULL && here->payload == SEMICOLON){
        recursive_inorderToNodeofSEMICOLON(here ,v );
        matchInorderResult(v);
      }
    }
  }

  void matchInorderResult (vector <Term*> v ){
    for(int i = 0 ; i<v.size() ; i++){
      for(int j = 0 ; j<v.size() ; j++){
        Struct* transStruct = dynamic_cast<Struct*>(v[j]);
        if(transStruct && i != j){
          matchVariabletoNestedStruct(transStruct ,v[i] );
        }
        if(v[i]->symbol() == v[j]->symbol() && i != j){
          v[i]->match(*v[j]);  
          v.erase(v.begin()+ j);      
        }        
      }
    }
  }
  void recursive_inorderToNodeofSEMICOLON(Node *here , vector<Term*> & v){
    if(here != NULL)
    {
      if(here->left != NULL && here->right != NULL && here->payload == SEMICOLON){
        vector<Term*> v2 = {};
        recursive_inorder(here->left ,v);
        recursive_inorder(here->right,v2);          
        for(int i = 0 ; i< v2.size() ; i++){
          for(int j = 0 ; j < v2.size() ; j++){
            Struct* transStruct = dynamic_cast<Struct*>(v2[j]);
            if(transStruct && i != j){
              matchVariabletoNestedStruct(transStruct ,v2[i] );
            }
            if(v2[i]->symbol() == v2[j]->symbol() && i != j){          
              v2[i]->match(*v2[j]);  
              v2.erase(v2.begin()+ j);      
            }        
          }
        }  
      }    
     
    }
  }
  
  Node * expressionTree(){
    // setRoot();
    return _tree; 
  }
  void setRoot(){
    _tree = _nodeofOperation[0];
    bool setcount = 0;    
    for(int i = 0 ; i < _operation.size() ; i++){
      if (_operation[i] ==';'){
        if(setcount !=  1){
          _tree = _nodeofOperation[i];          
        }
        setcount = 1 ;         
      }
      else if(_operation[i] ==','){
        if(setcount !=  1){
          _tree = _nodeofOperation[i];          
        }
        setcount = 1 ;   
      }      
      else if(setcount == 0){
        _tree = _nodeofOperation[i];
      }
    }
  }



private:
  FRIEND_TEST(ParserTest, createArgs);
  FRIEND_TEST(ParserTest,ListOfTermsEmpty);
  FRIEND_TEST(ParserTest,listofTermsTwoNumber);
  FRIEND_TEST(ParserTest, createTerm_nestedStruct3);

  void createTerms() {
    Term* term = createTerm();
    if(term!=nullptr)
    {
      _terms.push_back(term);
      while((_currentToken = _scanner.nextToken()) == ',' || _currentToken == '=' ||_currentToken == ';') {
        _operation.push_back((_currentToken));
        _terms.push_back(createTerm());
      }
    }
  }

  Node * _tree ;
  vector<Term *> _terms;
  vector<int> _operation;
  vector<Node*> _nodeofOperation;
  Scanner _scanner;
  int _currentToken;
};
#endif
