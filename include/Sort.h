#include <list>
#include "Shapes.h"

class Sort {

public:static void sortByIncreasingPerimeter(std::list<Shape *> * shapeList) {
	std::list<Shape *>::iterator iterbegin = shapeList->begin();
	std::list<Shape *>::iterator itertemp = shapeList->begin();
	std::list<Shape *>::iterator itersmall = shapeList->begin();
	std::list<Shape *>::iterator iterend = shapeList->end();
	while (iterbegin != iterend) {
		itersmall = iterbegin;
		itertemp = iterbegin;
		while (itertemp != iterend) {
			if ((*itersmall)->perimeter() > (*itertemp)->perimeter())
				itersmall = itertemp;
			itertemp++;
		}
		Shape *temp = *iterbegin;
		*iterbegin = *itersmall;
		*itersmall = temp;
		iterbegin++;
	}
}


public:static void sortByDecreasingPerimeter(std::list<Shape *> * shapeList) {
	std::list<Shape *>::iterator iterbegin = shapeList->begin();
	std::list<Shape *>::iterator itertemp = shapeList->begin();
	std::list<Shape *>::iterator itersmall = shapeList->begin();
	std::list<Shape *>::iterator iterend = shapeList->end();
	while (iterbegin != iterend) {
		itersmall = iterbegin;
		itertemp = iterbegin;
		while (itertemp != iterend) {
			if ((*itersmall)->perimeter() < (*itertemp)->perimeter())
				itersmall = itertemp;
			itertemp++;
		}
		Shape *temp = *iterbegin;
		*iterbegin = *itersmall;
		*itersmall = temp;
		iterbegin++;
	}
}

public:static void sortByIncreasingArea(std::list<Shape *> * shapeList) {
	std::list<Shape *>::iterator iterbegin = shapeList->begin();
	std::list<Shape *>::iterator itertemp = shapeList->begin();
	std::list<Shape *>::iterator itersmall = shapeList->begin();
	std::list<Shape *>::iterator iterend = shapeList->end();
	while (iterbegin != iterend) {
		itersmall = iterbegin;
		itertemp = iterbegin;
		while (itertemp != iterend) {
			if ((*itersmall)->area() > (*itertemp)->area())
				itersmall = itertemp;
			itertemp++;
		}
		Shape *temp = *iterbegin;
		*iterbegin = *itersmall;
		*itersmall = temp;
		iterbegin++;
	}
}

public:static void sortByDecreasingArea(std::list<Shape *> * shapeList) {
	std::list<Shape *>::iterator iterbegin = shapeList->begin();
	std::list<Shape *>::iterator itertemp = shapeList->begin();
	std::list<Shape *>::iterator itersmall = shapeList->begin();
	std::list<Shape *>::iterator iterend = shapeList->end();
	while (iterbegin != iterend) {
		itersmall = iterbegin;
		itertemp = iterbegin;
		while (itertemp != iterend) {
			if ((*itersmall)->area() < (*itertemp)->area())
				itersmall = itertemp;
			itertemp++;
		}
		Shape *temp = *iterbegin;
		*iterbegin = *itersmall;
		*itersmall = temp;
		iterbegin++;
	}
}

public:static void sortByIncreasingCompactness(std::list<Shape *> * shapeList) {
    std::list<Shape *>::iterator iterbegin = shapeList->begin();
	std::list<Shape *>::iterator itertemp = shapeList->begin();
	std::list<Shape *>::iterator itersmall = shapeList->begin();
	std::list<Shape *>::iterator iterend = shapeList->end();
	while (iterbegin != iterend) {
		itersmall = iterbegin;
		itertemp = iterbegin;
		while (itertemp != iterend) {
			if (((*itersmall)->area()/(*itersmall)->perimeter()) > ((*itertemp)->area()/(*itertemp)->perimeter()))
				itersmall = itertemp;
			itertemp++;
		}
		Shape *temp = *iterbegin;
		*iterbegin = *itersmall;
		*itersmall = temp;
		iterbegin++;
	}
}

};
