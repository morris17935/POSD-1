#ifndef UTVARIABLE_H
#define UTVARIABLE_H
#include "variable.h"
#include "number.h"
#include "atom.h"
#include "struct.h"
#include <vector>
using namespace std;
TEST(Variable, constructor){
  Variable X("X");
  ASSERT_EQ("X", X._symbol);
}

TEST(Variable , matching){
  Atom tom("tom");
  Variable X("X");
  X.match(tom);
  ASSERT_EQ( "tom", X.value());
}

TEST (Variable , haveValue){
  Atom tom ("tom");
  Atom jerry ("jerry");
  Variable X("X");
  ASSERT_TRUE(X.match(tom));
  ASSERT_FALSE(X.match(jerry));
}

// ?- X=2.7182.
// X=2.7182
TEST(Variable , numE_to_varX){
	Variable X("X");
	Number _2_7182(2.7182);
	EXPECT_TRUE(X.match(_2_7182));
}

// ?- X=Y, X=1.
// Y=1
TEST (Variable, varY_to_varX_and_num1_to_varX) {
	Variable X("X");
	Variable Y("Y");
	Number _1(1);
	X.match(Y);
	X.match(_1);
	EXPECT_TRUE(Y.match(_1));
}
  
// ?- X=Y, Y=1.
// X=1
TEST (Variable, varY_to_varX_and_num1_to_varY) {
	Variable X("X");
	Variable Y("Y");
	Number _1(1);
	X.match(Y);
	Y.match(_1);
	EXPECT_TRUE(X.match(_1));
}

// ?- X=X, X=1.
// X=1
TEST (Variable, varX_match_varX_and_num1_to_varX) {
	Variable X("X");
	Number _1(1);
	X.match(X);
	X.match(_1);
	EXPECT_TRUE(X.match(_1));
}

// ?- Y=1, X=Y.
// X=1
TEST (Variable, num1_to_varY_and_varX_match_varY) {
	Variable X("X");
	Variable Y("Y");
	Number _1(1);
	Y.match(_1);
	X.match(Y);
	EXPECT_TRUE(X.match(_1));
}

// ?- X=Y, Y=Z, Z=1
// X=1, Y=1, Z=1
TEST (Variable, num1_to_varZ_to_varY_to_varX) {
	Variable X("X");
	Variable Y("Y");
	Variable Z("Z");
	Number _1(1);
	X.match(Y);
	Y.match(Z);
	Z.match(_1);
	EXPECT_TRUE(X.match(_1));
	EXPECT_TRUE(Y.match(_1));
	EXPECT_TRUE(Z.match(_1));
}

// ?- X=Y, X=Z, Z=1
// X=1, Y=1, Z=1
TEST (Variable, num1_to_varZ_to_varX_and_varY_to_varX) {
	Variable X("X");
	Variable Y("Y");
	Variable Z("Z");
	Number _1(1);
	X.match(Y);
	X.match(Z);
	Z.match(_1);
	EXPECT_TRUE(X.match(_1));
	EXPECT_TRUE(Y.match(_1));
	EXPECT_TRUE(Z.match(_1));
}

// Give there is a Struct s contains Variable X
// And another Variable Y
// When Y matches Struct s
// Then #symbol() of Y should return "Y"
// And #value() of Y should return "s(X)"
TEST (Variable, Struct1) {
	Atom point("point");
	Number _1(1);
	Variable X("X");
	Variable Y("Y");
	vector<Term *> v = { &_1, &X };
	Struct plane( point, v);
	Y.match(plane);
	EXPECT_EQ("Y", Y.symbol());
	EXPECT_EQ("point(1, X)", Y.value());
}

// Give there is a Struct s contains Variable X
// And another Variable Y
// When Y matches Struct s
// And X matches Atom "teddy"
// Then #symbol() of Y should return "Y"
// And #value() of Y should return "s(teddy)"
TEST (Variable, Struct2) {
	Atom point("point");
	Atom teddy("teddy");
	Number _1(1);
	Variable X("X");
	Variable Y("Y");
	vector<Term *> v = { &_1, &X };
	Struct plane(point, v);
	X.match(teddy);
	Y.match(plane);
	EXPECT_EQ("Y", Y.symbol());
	EXPECT_EQ("point(1, teddy)", Y.value());
}

#endif