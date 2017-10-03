#ifndef UTNUMBER_H
#define UTNUMBER_H
#include "number.h"

//test Number.value()

TEST (Number,ctor) {
	Number _25(25);
	ASSERT_EQ("25", _25.value());
}
//test Number.symbol()
TEST (Number, symbol) {
	Number _25(25);
	ASSERT_EQ("25", _25.symbol());
}
//?- 25=25.
//true.
TEST (Number, matchSuccess) {
	Number _25(25);
	Number _25_2(25);
	EXPECT_TRUE(_25.match(_25_2));
}
//?- 25=0.
//false.
TEST (Number, matchFailureDiffValue) {
	Number _25(25);
	Number _0(0);
	EXPECT_FALSE(_25.match(_0));
}
//?- 25=tom.
//false.
TEST (Number, matchFailureDiffConstant) {
	Number _25(25);
	Atom tom("tom");
	EXPECT_FALSE(_25.match(tom));
}
//?- 25=X.
//true.
TEST (Number, matchSuccessToVar) {
	Number _25(25);
	Variable X;
	EXPECT_TRUE(_25.match(X));
}

//?- tom=25.
//false.
TEST (Atom, matchFailureDiffConstant) {
	Number _25(25);
	Atom tom("tom");
	EXPECT_FALSE(tom.match(_25));
}

// ?- tom = X.
// X = tom.
TEST (Atom, matchSuccessToVar) {
	Atom tom("tom");
	Variable X;
	EXPECT_TRUE(tom.match(X));
}

// ?- X=tom, tom=X.
// X = tom.

TEST (Atom, matchSuccessToVarInstantedToDiffConstant) {
	Atom tom("tom");
	Variable X;
	EXPECT_TRUE(X.match(tom));
	EXPECT_TRUE(tom.match(X));
}

// ?- X=jerry, tom=X.
// false.
TEST (Atom, matchFailureToVarInstantedToDiffConstant) {
	Atom tom("tom");
	Atom jerry("jerry");
	Variable X;
	X.match(jerry);
	EXPECT_FALSE(tom.match(X));
}

// ?- X = 5.
// X = 5.
TEST (Var, matchSuccessToNumber) {
	Variable X;
	Number _5(5);
	EXPECT_TRUE(X.match(_5));
}

// ?- X=25, X= 100.
// false.
TEST (Var, matchFailureToTwoDiffNumbers) {
	Variable X;
	Number _25(25);
	Number _100(100);
	X.match(_25);
	EXPECT_FALSE(X.match(_100));
}

// ?- X=tom, X= 25.
// false.
TEST (Var, matchSuccessToAtomThenFailureToNumber) {
	Variable X;
	Atom tom("tom");
	Number _25(25);
	X.match(tom);
	EXPECT_FALSE(X.match(_25));

}
//?- tom=X, 25=X.
//false.
TEST (Var, matchSuccessToAtomThenFailureToNumber2) {
	Variable X;
	Atom tom("tom");
	Number _25(25);
	tom.match(X);
	EXPECT_FALSE(_25.match(X));
}
//?- X=tom, X=tom.
//true.
TEST(Var, reAssignTheSameAtom){
	Variable X;
	Atom tom("tom");
	X.match(tom);
	EXPECT_TRUE(X.match(tom));
}
#endif
