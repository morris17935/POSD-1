#ifndef EXP_H
#define EXP_H
#include "include/Shapes.h"
#include "include/Media.h"
#include "include/Sort.h"
using namespace std;
TEST (Sort, sortByIncreasingPerimeter) {
	std::list<Shape *> test;
	Sort fortest;
	vertex a,b,c;
	a.x = 1;
	a.y = 2;
	b.x = 4;
	b.y = 2;
	c.x = 4;
	c.y = 6;
	Shape *temp1 = new Rectangle(1, 1, 2, 2, "rectangle");
	Shape *temp2 = new Circle(1, 1, 2, "circle");
	Shape *temp3 = new Triangle(a, b, c, "triangle");
	test.push_back(temp1);
	test.push_back(temp2);
	test.push_back(temp3);
	fortest.sortByIncreasingPerimeter(&test);
	std::list<Shape *>::iterator itertest = test.begin();
	ASSERT_EQ(8, (*(*itertest)).perimeter());
	itertest++;
	ASSERT_EQ(12,(*(*itertest)).perimeter());
	itertest++;
	ASSERT_EQ(4* M_PI, (*(*itertest)).perimeter());
}

TEST (Sort, sortByDecreasingPerimeter) {
	std::list<Shape *> test;
	Sort fortest;
	vertex a, b, c;
	a.x = 1;
	a.y = 2;
	b.x = 4;
	b.y = 2;
	c.x = 4;
	c.y = 6;
	Shape *temp1 = new Rectangle(1, 1, 2, 2, "rectangle");
	Shape *temp2 = new Circle(1, 1, 2, "circle");
	Shape *temp3 = new Triangle(a, b, c, "triangle");
	test.push_back(temp1);
	test.push_back(temp2);
	test.push_back(temp3);
	fortest.sortByDecreasingPerimeter(&test);
	std::list<Shape *>::iterator itertest = test.begin();
	ASSERT_EQ(4 * M_PI, (*(*itertest)).perimeter());
	itertest++;
	ASSERT_EQ(12, (*(*itertest)).perimeter());
	itertest++;
	ASSERT_EQ(8, (*(*itertest)).perimeter());
}

TEST (Sort, sortByIncreasingArea) {
	std::list<Shape *> test;
	Sort fortest;
	vertex a, b, c;
	a.x = 1;
	a.y = 2;
	b.x = 4;
	b.y = 2;
	c.x = 4;
	c.y = 6;
	Shape *temp1 = new Rectangle(1, 1, 2, 2, "rectangle");
	Shape *temp2 = new Circle(1, 1, 2, "circle");
	Shape *temp3 = new Triangle(a, b, c, "triangle");
	test.push_back(temp1);
	test.push_back(temp2);
	test.push_back(temp3);
	fortest.sortByIncreasingArea(&test);
	std::list<Shape *>::iterator itertest = test.begin();
	ASSERT_EQ(4, (*(*itertest)).area());
	itertest++;
	ASSERT_EQ(6, (*(*itertest)).area());
	itertest++;
	ASSERT_EQ(4 * M_PI, (*(*itertest)).area());
}

TEST (Sort, sortByDecreasingArea) {
	std::list<Shape *> test;
	Sort fortest;
	vertex a, b, c;
	a.x = 1;
	a.y = 2;
	b.x = 4;
	b.y = 2;
	c.x = 4;
	c.y = 6;
	Shape *temp1 = new Rectangle(1, 1, 2, 2, "rectangle");
	Shape *temp2 = new Circle(1, 1, 2, "circle");
	Shape *temp3 = new Triangle(a, b, c, "triangle");
	test.push_back(temp1);
	test.push_back(temp2);
	test.push_back(temp3);
	fortest.sortByDecreasingArea(&test);
	std::list<Shape *>::iterator itertest = test.begin();
	ASSERT_EQ(4 * M_PI, (*(*itertest)).area());
	itertest++;
	ASSERT_EQ(6, (*(*itertest)).area());
	itertest++;
	ASSERT_EQ(4, (*(*itertest)).area());
}


TEST (Sort, sortByIncreasingCompactness) {
    std::list<Shape *> test;
	Sort fortest;
	vertex a, b, c;
	a.x = 1;
	a.y = 2;
	b.x = 4;
	b.y = 2;
	c.x = 4;
	c.y = 6;
	Shape *temp1 = new Rectangle(1, 1, 3, 4, "rectangle");
	Shape *temp2 = new Circle(1, 1, 2, "circle");
	Shape *temp3 = new Triangle(a, b, c, "triangle");
	test.push_back(temp1);
	test.push_back(temp2);
	test.push_back(temp3);
	fortest.sortByIncreasingArea(&test);
	std::list<Shape *>::iterator itertest = test.begin();
	ASSERT_EQ(0.5, (*(*itertest)).area()/(*(*itertest)).perimeter());
	itertest++;
	ASSERT_NE(12/14, (*(*itertest)).area()/(*(*itertest)).perimeter());
	itertest++;
	ASSERT_EQ((4 * M_PI)/(4 * M_PI), (*(*itertest)).area()/(*(*itertest)).perimeter());
}

#endif
