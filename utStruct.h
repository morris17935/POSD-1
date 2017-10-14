#ifndef UTSTRUCT_H
#define UTSTRUCT_H
#include <vector>
#include "atom.h"
#include "struct.h"

TEST(Struct, hobby)
{
	Atom tom("tom");
	Atom chaseMouse("chaseMouse");
	std::vector<Term *> v = { &tom, &chaseMouse };
	Struct hobby(Atom("hobby"), v);
	ASSERT_EQ("hobby", hobby.name().symbol());
	ASSERT_EQ("tom", hobby.args(0)->symbol());
	ASSERT_EQ("chaseMouse", hobby.args(1)->symbol());
}

TEST(Struct, symbol)
{
  Atom tom("tom");
  Atom chaseMouse("chaseMouse");
  std::vector<Term *> v = {&tom, &chaseMouse};
  Struct hobby(Atom("hobby"), v);
  ASSERT_EQ("hobby(tom,chaseMouse)",hobby.symbol());
}

TEST(Struct, match1)
{
  Atom tom("tom");
  Atom chaseMouse("chaseMouse");
  std::vector<Term *> v = {&tom, &chaseMouse};
  Struct hobby(Atom("hobby"), v);
  Struct hobby2(Atom("hobby2"), v);
  EXPECT_FALSE(hobby.match(hobby2));
}

TEST(Struct, match2){
  Atom tom("tom");
  Atom chaseMouse("chaseMouse");
  std::vector<Term *> v = {&tom, &chaseMouse};
  Struct hobby(Atom("hobby"), v);
  std::vector<Term *> v1 = {&tom};
  Struct hobby2(Atom("hobby"), v1);
  EXPECT_FALSE(hobby.match(hobby2));
}

TEST(Struct, match3){
  Atom tom("tom");
  Atom chaseMouse("chaseMouse");
  std::vector<Term *> v = {&tom, &chaseMouse};
  Struct hobby(Atom("hobby"), v);
  std::vector<Term *> v1 = { &chaseMouse,&tom};
  Struct hobby2(Atom("hobby"), v1);
  EXPECT_FALSE(hobby.match(hobby2));
}

TEST(Struct, match4)
{
  Atom tom("tom");
  Atom chaseMouse("chaseMouse");
  std::vector<Term *> v = {&tom, &chaseMouse};
  Struct hobby(Atom("hobby"), v);
  Struct hobby2(Atom("hobby"), v);
  EXPECT_TRUE(hobby.match(hobby2));
}

TEST(Struct, match5)
{
  Atom tom("tom");
  Atom chaseMouse("chaseMouse");
  std::vector<Term *> v = {&tom, &chaseMouse};
  Struct hobby(Atom("hobby"), v);
  EXPECT_FALSE(hobby.match(tom));
}

// When Struct s contains a Variable X
// Then #symbol() should return "s(X)"
// and #value() should also return "s(X)"
TEST(Struct, var)
{
	Atom point("point");
	Number _1(1);
	Variable X("X");
	vector<Term *> v = { &_1, &X };
	Struct plane(point, v);
	EXPECT_EQ("point(1,X)", plane.value());
}

// Given there is Struct s contains a Variable X
// When Variable X matches an Atom "tom"
// Then #symbol() should return "s(X)"
// and #value() should also return "s(tom)"
TEST(Struct, var_match_atom)
{
	Atom point("point");
	Atom tom("tom");
	Number _1(1);
	Variable X("X");
	vector<Term *> v = { &_1, &X };
	Struct plane(point, v);
	X.match(tom);
	EXPECT_EQ("point(1,X)", plane.symbol());
	EXPECT_EQ("point(1,tom)", plane.value());
}

// Given there are Struct s1 and Struct s2
// When Struct s1 contains Struct s2
// And Struct s2 contains a Variable X
// Then #symbol() of s1 should return "s1(s2(X))"
// and #value() of s1 should also return "s1(s2(X))"
TEST(Struct, nested_struct1)
{
	Atom point("point");
	Number _1(1);
	Variable X("X");
	Variable Y("Y");
	vector<Term *> v = { &_1, &X };
	Struct plane(point, v);
	vector<Term *> v2 = { &plane, &Y };
	Struct space(Atom("space"), v2);
	EXPECT_EQ("space(point(1,X),Y)", space.symbol());
	EXPECT_EQ("space(point(1,X),Y)", space.value());
}

// Given there are Struct s1 contains Struct s2
// And Struct s2 contains Variable X
// When Variable X matches an Atom "tom"
// Then #symbol() of s1 should return "s1(s2(X))"
// and #value() of s1 should return "s1(s2(tom))"
TEST(Struct, nested_struct2)
{
	Atom point("point");
	Atom tom("tom");
	Number _1(1);
	Variable X("X");
	Variable Y("Y");
	vector<Term *> v = { &_1, &X };
	Struct plane(point, v);
	vector<Term *> v2 = { &plane, &Y };
	Struct space(Atom("space"), v2);
	X.match(tom);
	EXPECT_EQ("space(point(1,X),Y)", space.symbol());
	EXPECT_EQ("space(point(1,tom),Y)", space.value());
}

// Given there are Struct s1 contains Struct s2
// And Struct s2 contains Variable X
// When Variable X matches an Number pi: 3.14
// Then #symbol() of s1 should return "s1(s2(X))"
// and #value() of s1 should return "s1(s2(3.14))"
TEST(Struct, nested_struct3)
{
	Atom point("point");
	Number _3_14(3.14);
	Number _1(1);
	Variable X("X");
	Variable Y("Y");
	vector<Term *> v = { &_1, &X };
	Struct plane(point, v);
	vector<Term *> v2 = { &plane, &Y };
	Struct space(Atom("space"), v2);
	X.match(_3_14);
	EXPECT_EQ("space(point(1,X),Y)", space.symbol());
	EXPECT_EQ("space(point(1,3.14),Y)", space.value());
}

// Given there are Struct s1 contains Struct s2 and Variable X
// And Struct s2 contains Variable Y
// When Variable X matches Variable Y
// And Variable X matches Atom "kent_beck"
// Then #symbol() of s1 should return "s1(s2(Y), X)"
// and #value() of s1 should return "s1(s2(kent_beck), kent_beck)"
TEST(Struct, nested_struct_and_multiVariable)
{
	Atom point("point");
	Atom kent_beck("kent_beck");
	Number _1(1);
	Variable X("X");
	Variable Y("Y");
	vector<Term *> v = { &_1, &X };
	Struct plane(point, v);
	vector<Term *> v2 = { &plane, &Y };
	Struct space(Atom("space"), v2);
	Y.match(X);
	Y.match(kent_beck);
	EXPECT_EQ("space(point(1,X),Y)", space.symbol());
	EXPECT_EQ("space(point(1,kent_beck),kent_beck)", space.value());
}

#endif

