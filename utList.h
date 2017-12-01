#ifndef UTLIST_H
#define UTLIST_H

#include <string>
using std::string;

#include "list.h"
#include "struct.h"
#include "atom.h"
#include "number.h"
#include "variable.h"

// When create a new list without any item
// Then #symbol() of the list should return "[]"
TEST (List, constructor) {
  List l ;
  EXPECT_EQ( "[]" , l.value()) ;  
}

// Given there are two perfect Numbers: 8128, 496
// When create a new list with the perfect Number
// Then #symbol() of the list should return "[496, 8128]"
TEST(List, Numbers) {

  Number n_496(496),n_8128(8128);
  vector <Term*> args = {&n_496,&n_8128};
  List l (args);
  EXPECT_EQ(string("[496, 8128]") , l.value()) ;  
  
}

// Given there are two atoms: "terence_tao", "alan_mathison_turing"
// When create a new list with the Atoms
// Then #symbol() of the list should return "[terence_tao, alan_mathison_turing]"
TEST(List, Atoms) {

  Atom terence_tao("terence_tao") , alan_mathison_turing("alan_mathison_turing");
  vector <Term*> args = {&terence_tao , &alan_mathison_turing};
  List l (args);
  EXPECT_EQ("[terence_tao, alan_mathison_turing]" , l.value());

}

// Given there are two variables: X, Y
// When create a new list with the variables
// Then #symbol() of the list should return "[X, Y]"
TEST(List, Vars) {

  Variable X("X") , Y("Y");
  vector <Term*> args = {&X , &Y};
  List l (args);
  EXPECT_EQ("[X, Y]" , l.value());

}

// ?- tom = [496, X, terence_tao].
// false.
TEST(List, matchToAtomShouldFail) {

  Atom tom("tom") ,terence_tao("terence_tao");
  Variable X ("X");
  Number n_496(496);
  vector <Term * > args = {&n_496, &X , &terence_tao}; 
  List l(args);
  EXPECT_FALSE(tom.match(l));

}

// ?- 8128 = [496, X, terence_tao].
// false.
TEST(List, matchToNumberShouldFail) {

  Atom terence_tao("terence_tao");
  Variable X ("X");
  Number n_496(496) , n_8182(8128);
  vector <Term * > args = {&n_496, &X , &terence_tao}; 
  List l(args);
  EXPECT_FALSE(n_8182.match(l));

}

// ?- s(X) = [496, X, terence_tao].
// false.
TEST(List, matchToStructShouldFail) {

  Atom X_name("X") ;
  Variable X("X") ;
  Number n_496(496) ;
  Atom terence_tao("terence_tao");  
  vector<Term * > struct_arg = {&X};
  vector<Term * > list_arg = { &n_496 , &X , &terence_tao };
  List l(list_arg) ;
  Struct s( X_name , struct_arg ) ;
  EXPECT_FALSE(s.match(l));  

}

// ?- Y = [496, X, terence_tao].
// Y = [496, X, terence_tao].
TEST(List, matchToVarShouldSucceed) {

  Variable X("X") ,Y("Y");
  Number n_496(496) ;
  Atom terence_tao("terence_tao");  
  vector<Term * > list_arg = { &n_496 , &X , &terence_tao };
  List l(list_arg) ;
  EXPECT_TRUE(Y.match(l));
  EXPECT_EQ("[496, X, terence_tao]" , Y.value());  

}

// ?- X = [496, X, terence_tao].
// false.
TEST(List, matchToVarOccuredInListShouldFail) {

  Variable X ("X");
  Number n_496(496) ;
  Atom terence_tao("terence_tao");  
  vector<Term * > list_arg = { &n_496 , &X , &terence_tao };
  List l(list_arg) ;
  EXPECT_FALSE(X.match(l));
  
}

// ?- [496, X, terence_tao] = [496, X, terence_tao].
// true.
TEST(List, matchToSameListShouldSucceed) {

  Variable X ("X");
  Number n_496(496) ;
  Atom terence_tao("terence_tao");  
  vector<Term * > list_arg = { &n_496 , &X , &terence_tao };
  List l (list_arg);
  List l2 (list_arg);  
  EXPECT_TRUE(l.match(l2));

}

// ?- [496, X, terence_tao] = [496, Y, terence_tao].
// true.
TEST(List, matchToSameListWithDiffVarNameShouldSucceed) {

  Variable X ("X"),Y("Y");
  Number n_496(496) ;
  Atom terence_tao("terence_tao");  
  vector<Term * > list_arg = { &n_496 , &X , &terence_tao };
  vector<Term * > list_arg2 = { &n_496 , &Y , &terence_tao };  
  List l (list_arg);
  List l2 (list_arg2);  
  EXPECT_TRUE(l.match(l2));

}

// ?- [496, X, terence_tao] = [496, 8128, terence_tao].
// X = 8128.
TEST(List, matchToVarToAtominListShouldSucceed) {

  Variable X ("X");
  Number n_496(496) ,n_8128(8128);
  Atom terence_tao("terence_tao");  
  vector<Term * > list_arg = { &n_496 , &X , &terence_tao };
  vector<Term * > list_arg2 = { &n_496 , &n_8128 , &terence_tao };  
  List l (list_arg);
  List l2 (list_arg2);  
  EXPECT_TRUE(l.match(l2));
  EXPECT_EQ("8128",X.value());

}

// ?- Y = [496, X, terence_tao], X = alan_mathison_turing.
// Y = [496, alan_mathison_turing, terence_tao],
// X = alan_mathison_turing.
TEST(List, matchVarinListToAtomShouldSucceed) {

  Variable X ("X"),Y("Y");
  Number n_496(496);
  Atom terence_tao("terence_tao"),alan_mathison_turing("alan_mathison_turing");  
  vector<Term * > list_arg = { &n_496 , &X, &terence_tao   };
  List l (list_arg);
  X.match(alan_mathison_turing);
  Y.match(l);
  EXPECT_EQ("[496, alan_mathison_turing, terence_tao]",Y.value());  
  EXPECT_EQ("alan_mathison_turing",X.value());

}

// Example: 
// ?- [first, second, third] = [H|T].
// H = first, T = [second, third].
TEST(List, headAndTailMatching1) {

  Atom f("first"), s("second"), t("third");
  vector<Term *> args = {&f, &s, &t};
  List l(args);
  EXPECT_EQ("first", l.head()->symbol());
  EXPECT_EQ("[second, third]", l.tail()->value());

}

// Example:
// ?- [first, second, third] = [first, H|T].
// H = second, T = [third].
TEST(List, headAndTailMatching2) {

  Atom f("first"), s("second"), t("third");
  vector<Term *> args = {&f, &s, &t};
  List l(args);

  EXPECT_EQ(string("second"), l.tail()->head()->value());
  EXPECT_EQ(string("[third]"), l.tail()->tail()->value());

}

// ?- [[first], second, third] = [H|T].
// H = [first], T = [second, third].
TEST(List, headAndTailMatching3) {

  Atom f("first"), s("second"), t("third");
  vector<Term *> args_fir = {&f};  
  List l(args_fir);
  vector<Term *> args_rest = {&l, &s, &t};
  List l2(args_rest);
  
  EXPECT_EQ("[first]", l2.head()->value());
  EXPECT_EQ("[second, third]", l2.tail()->value());

}

// ?- [first, second, third] = [first, second, H|T].
// H = third, T = [].
TEST(List, headAndTailMatching4) {

  Atom f("first"), s("second"), t("third");
  vector<Term *> args = {&f, &s, &t};
  List l(args);
  EXPECT_EQ("third", l.tail()->tail()->head()->value());
  EXPECT_EQ("[]", l.tail()->tail()->tail()->value());  

}
 //
// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing head in an empty list" as an exception.
TEST (List, emptyExecptionOfHead) {

  List l;
  try{
    l.head();
  }
  catch(string  e){
    EXPECT_EQ("Accessing head in an empty list",e);
  }

}

// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing tail in an empty list" as an exception.
TEST (List, emptyExecptionOfTail) {

  List l;
  try{
    l.tail();
  }
  catch(string  e){
    EXPECT_EQ("Accessing tail in an empty list",e);
  }

}

#endif
