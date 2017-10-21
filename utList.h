#ifndef UTLIST_H
#define UTLIST_H

#include <string>
using namespace std;

#include "list.h"
#include "struct.h"
#include "atom.h"
#include "number.h"
#include "variable.h"
#include <iostream>
// When create a new list without any item
// Then #symbol() of the list should return "[]"
TEST (List, constructor) {
	List temp;
	EXPECT_EQ(string("[]"), temp.symbol());
}

// Given there are two perfect numbers: 8128
// When create a new list with the perfect Number
// Then #symbol() of the list should return "[8128]"
TEST(List, Numbers) {
	Number _8128_1(8128);
	Number _8128_2(8128);
	vector<Term *> args = { &_8128_1, &_8128_2 };
	List temp(args);
	EXPECT_EQ(string("[8128]"), temp.symbol());
}

// Given there are two atoms: "terence_tao", "alan_mathison_turing"
// When create a new list with the Atoms
// Then #symbol() of the list should return "[terence_tao, alan_mathison_turing]"
TEST(List, Atoms) {
	Atom terence_tao("terence_tao");
	Atom alan_mathison_turing("alan_mathison_turing");
	vector<Term *> args = { &terence_tao, &alan_mathison_turing };
	List temp(args);
	EXPECT_EQ(string("[terence_tao, alan_mathison_turing]"), temp.symbol());
}

// Given there are two variables: X, Y
// When create a new list with the variables
// Then #symbol() of the list should return "[X, Y]"
TEST(List, Vars) {
	Variable X("X");
	Variable Y("Y");
	vector<Term *> args = { &X, &Y };
	List temp(args);
	EXPECT_EQ(string("[X, Y]"), temp.symbol());
}

// ?- tom = [496, X, terence_tao].
// false.
TEST(List, matchToAtomShouldFail) {
	Atom tom("tom");
	Atom terence_tao("terence_tao");
	Variable X("X");
	Number _496(496);
	vector<Term *> args = { &_496,  &X, &terence_tao };
	List temp(args);
	EXPECT_FALSE(tom.match(temp));
}

// ?- 8128 = [496, X, terence_tao].
// false.
TEST(List, matchToNumberShouldFail) {
	Number _8128(8128);
	Number _496(496);
	Variable X("X");
	Atom terence_tao("terence_tao");
	vector<Term *> args = { &_496,  &X, &terence_tao };
	List temp(args);
	EXPECT_FALSE(_8128.match(temp));
}

// ?- s(X) = [496, X, terence_tao].
// false.
TEST(List, matchToStructShouldFail) {
	Variable X("X");
	vector<Term *> v2 = { &X };
	Struct s(Atom("s"), v2);
	Number _496(496);
	Atom terence_tao("terence_tao");
	vector<Term *> args = { &_496,  &X, &terence_tao };
	List temp(args);
	EXPECT_FALSE(s.match(temp));
}

// ?- Y = [496, X, terence_tao].
// Y = [496, X, terence_tao].
TEST(List, matchToVarShouldSucceed) {
	Variable Y("Y");
	Variable X("X");
	Number _496(496);
	Atom terence_tao("terence_tao");
	vector<Term *> args = { &_496,  &X, &terence_tao };
	List temp(args);
	EXPECT_TRUE(Y.match(temp));
}

// ?- X = [496, X, terence_tao].
// false.
TEST(List, matchToVarOccuredInListShouldFail) {
	Variable X("X");
	Number _496(496);
	Atom terence_tao("terence_tao");
	vector<Term *> args = { &_496,  &X, &terence_tao };
	List temp(args);
	EXPECT_FALSE(X.match(temp));
}

// ?- [496, X, terence_tao] = [496, X, terence_tao].
// true.
TEST(List, matchToSameListShouldSucceed) {
	Variable X("X");
	Number _496(496);
	Atom terence_tao("terence_tao");
	vector<Term *> args = { &_496,  &X, &terence_tao };
	List temp(args);
	EXPECT_TRUE(temp.match(temp));
}

// ?- [496, X, terence_tao] = [496, Y, terence_tao].
// true.
TEST(List, matchToSameListWithDiffVarNameShouldSucceed) {
	Variable X("X");
	Variable Y("Y");
	Number _496(496);
	Atom terence_tao("terence_tao");
	vector<Term *> args = { &_496,  &X, &terence_tao };
	vector<Term *> args2 = { &_496,  &Y, &terence_tao };
	List temp(args);
	List temp2(args2);
	EXPECT_TRUE(temp.match(temp2));
}

// ?- [496, X, terence_tao] = [496, 8128, terence_tao].
// X = 8128.
TEST(List, matchToVarToAtominListShouldSucceed) {
	Variable X("X");
	Number _496(496);
	Number _8128(8128);
	Atom terence_tao("terence_tao");
	vector<Term *> args = { &_496,  &_8128, &terence_tao };
	vector<Term *> args2 = { &_496,  &X, &terence_tao };
	List temp(args);
	List temp2(args2);
	temp2.match(temp);
	EXPECT_TRUE(X.match(_8128));
}

// ?- Y = [496, X, terence_tao], X = alan_mathison_turing.
// Y = [496, alan_mathison_turing, terence_tao],
// X = alan_mathison_turing.
TEST(List, matchVarinListToAtomShouldSucceed) {
	Variable X("X");
	Variable Y("Y");
	Number _496(496);
	Atom terence_tao("terence_tao");
	Atom alan_mathison_turing("alan_mathison_turing");
	vector<Term *> args = { &_496,  &X, &terence_tao };
	List temp(args);
	Y.match(temp);
	X.match(alan_mathison_turing);
	EXPECT_EQ("[496, alan_mathison_turing, terence_tao]" , Y.value());
	EXPECT_TRUE(X.match(alan_mathison_turing));
}

// Example: 
// ?- [first, second, third] = [H|T].
// H = first, T = [second, third].
TEST(List, headAndTailMatching1) {
  Atom f("first"), s("second"), t("third");
  vector<Term *> args = {&f, &s, &t};
  List l(args);

  EXPECT_EQ(string("first"), l.head()->symbol());
  EXPECT_EQ(string("[second, third]"), l.tail()->value());
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
// H = first, T = [second, third].
TEST(List, headAndTailMatching3) {
	Atom f("first"), s("second"), t("third");
	vector<Term *> args2 = { &f};
	List temp(args2);
	vector<Term *> args = { &temp, &s, &t };
	List l(args);
	EXPECT_EQ(string("[first]"), l.head()->value());
	EXPECT_EQ(string("[second, third]"), l.tail()->value());
}

// ?- [first, second, third] = [first, second, H|T].
// H = third, T = [].
TEST(List, headAndTailMatching4) {
	Atom f("first"), s("second"), t("third");
	vector<Term *> args2 = { &f };
	List temp(args2);
	vector<Term *> args = { &temp, &s, &t };
	List l(args);
	EXPECT_EQ(string("third"), l.tail()->tail()->head()->value());
	EXPECT_EQ(string("[]"), l.tail()->tail()->tail()->value());
} 

// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing head in an empty list" as an exception.
TEST (List, emptyExecptionOfHead) {
	List temp;
	try
	{
		temp.head()->value();
	}
	catch( ...)
	{
	}
	
}

// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing tail in an empty list" as an exception.
TEST (List, emptyExecptionOfTail) {
	List temp;
	try
	{
		temp.tail()->value();
	}
	catch (...)
	{
	}
}




#endif
